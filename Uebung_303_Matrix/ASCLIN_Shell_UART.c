/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "ASCLIN_Shell_UART.h"
#include "Ifx_Types.h"
#include "IfxAsclin_Asc.h"
#include "Ifx_Shell.h"
#include "Ifx_Console.h"
#include "IfxPort.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
/* Communication parameters */
#define ISR_PRIORITY_ASCLIN_TX      8                                       /* Priority for interrupt ISR Transmit  */
#define ISR_PRIORITY_ASCLIN_RX      4                                       /* Priority for interrupt ISR Receive   */
#define ISR_PRIORITY_ASCLIN_ER      12                                      /* Priority for interrupt ISR Errors    */
#define ASC_TX_BUFFER_SIZE          256                                     /* Define the TX buffer size in byte    */
#define ASC_RX_BUFFER_SIZE          256                                     /* Define the RX buffer size in byte    */
#define ASC_BAUDRATE                115200                                  /* Define the UART baud rate            */

/* LEDs */
#define LED1                        &MODULE_P00,5                           /* LED1                                 */
#define LED2                        &MODULE_P00,6                           /* LED2                                 */

/* Shell commands and help descriptions */
#define COMMAND_INFO                "info"
#define COMMAND_TOGGLE              "toggle"
#define COMMAND_HELP                "help"
#define COMMAND_INFO_HELP_TEXT      "   : Show the example's info"
#define COMMAND_TOGGLE_HELP_TEXT    " : Command to toggle LEDs" ENDLINE \
                                    "         The correct syntax for this command is" ENDLINE \
                                    "         '" COMMAND_TOGGLE " [0/1/2]'"
#define COMMAND_HELP_HELP_TEXT      "   : Show this help list"

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void initLEDs(void);
void initSerialInterface(void);
void printInfo(IfxStdIf_DPipe *io);
boolean printShellInfo(pchar args, void *data, IfxStdIf_DPipe *io);
boolean toggleLEDsShell(pchar args, void *data, IfxStdIf_DPipe *io);

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
IfxStdIf_DPipe  g_ascStandardInterface;                                     /* Standard interface object            */
IfxAsclin_Asc   g_asclin;                                                   /* ASCLIN module object                 */
Ifx_Shell       g_shellInterface;                                           /* Shell interface object               */

/* The transfer buffers allocate memory for the data itself and for FIFO runtime variables.
 * 8 more bytes have to be added to ensure a proper circular buffer handling independent from
 * the address to which the buffers have been located.
 */
uint8 g_uartTxBuffer[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
uint8 g_uartRxBuffer[ASC_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

/* Array that stores the supported Shell commands */
const Ifx_Shell_Command g_shellCommands[] = {
    {COMMAND_INFO,   COMMAND_INFO_HELP_TEXT,    &g_shellInterface, &printShellInfo     },
    {COMMAND_TOGGLE, COMMAND_TOGGLE_HELP_TEXT,  &g_shellInterface, &toggleLEDsShell    },
    {COMMAND_HELP,   COMMAND_HELP_HELP_TEXT,    &g_shellInterface, &Ifx_Shell_showHelp },
    IFX_SHELL_COMMAND_LIST_END
};

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
/* Macro to define Interrupt Service Routine.
 * This macro makes following definitions:
 * 1) Define linker section as .intvec_tc<vector number>_<interrupt priority>.
 * 2) define compiler specific attribute for the interrupt functions.
 * 3) define the Interrupt service routine as ISR function.
 *
 * IFX_INTERRUPT(isr, vectabNum, priority)
 *  - isr: Name of the ISR function.
 *  - vectabNum: Vector table number.
 *  - priority: Interrupt priority. Refer Usage of Interrupt Macro for more details.
 */
IFX_INTERRUPT(asc0TxISR, 0, ISR_PRIORITY_ASCLIN_TX);

void asc0TxISR(void)
{
    IfxStdIf_DPipe_onTransmit(&g_ascStandardInterface);
}

IFX_INTERRUPT(asc0RxISR, 0, ISR_PRIORITY_ASCLIN_RX);

void asc0RxISR(void)
{
    IfxStdIf_DPipe_onReceive(&g_ascStandardInterface);
}

IFX_INTERRUPT(asc0ErrISR, 0, ISR_PRIORITY_ASCLIN_ER);

void asc0ErrISR(void)
{
    IfxStdIf_DPipe_onError(&g_ascStandardInterface);
}

/* Function to print info in the console */
void printInfo(IfxStdIf_DPipe *io)
{
    IfxStdIf_DPipe_print(io, ENDLINE);
    IfxStdIf_DPipe_print(io, "******************************************************************************"ENDLINE);
    IfxStdIf_DPipe_print(io, "This is an example that shows how to use the Infineon Shell from iLLDs.       "ENDLINE);
    IfxStdIf_DPipe_print(io, "In order to toggle the LEDs enter the command '" COMMAND_TOGGLE "' followed by one of the "ENDLINE);
    IfxStdIf_DPipe_print(io, "following parameters:                                                         "ENDLINE);
    IfxStdIf_DPipe_print(io, "  - '0': turns on all the LEDs on the board                                   "ENDLINE);
    IfxStdIf_DPipe_print(io, "  - '1': toggles the LED1                                                     "ENDLINE);
    IfxStdIf_DPipe_print(io, "  - '2': toggles the LED2                                                     "ENDLINE);
    IfxStdIf_DPipe_print(io, "Any other parameter turns off all the LEDs and reports a Shell command error. "ENDLINE);
    IfxStdIf_DPipe_print(io, "******************************************************************************"ENDLINE);
}

void printMessage(const char *message)
{
    IfxStdIf_DPipe_print(&g_ascStandardInterface, message);
}

void printDouble(double value) {
    IfxStdIf_DPipe_print(&g_ascStandardInterface, "%.2f", value);
}

void printLine(const char *message)
{
    IfxStdIf_DPipe_print(&g_ascStandardInterface, message);
    IfxStdIf_DPipe_print(&g_ascStandardInterface, ENDLINE);
}

/* Function to show information about the example through the shell */
boolean printShellInfo(pchar args, void *data, IfxStdIf_DPipe *io)
{
    printInfo(io);
    return TRUE;
}

/* Function to toggle LEDs */
boolean toggleLEDsShell(pchar args, void *data, IfxStdIf_DPipe *io)
{
    switch(args[0])
    {
        case '0': /* Turn on all LEDs */
            IfxPort_setPinState(LED1, IfxPort_State_low);
            IfxPort_setPinState(LED2, IfxPort_State_low);
            IfxStdIf_DPipe_print(io, "Turned on all LEDs!" ENDLINE ENDLINE);
            break;
        case '1': /* Toggle LED1 */
            IfxPort_setPinState(LED1, IfxPort_State_toggled);
            IfxStdIf_DPipe_print(io, "Toggled LED1!" ENDLINE ENDLINE);
            break;
        case '2': /* Toggle LED2 */
            IfxPort_setPinState(LED2, IfxPort_State_toggled);
            IfxStdIf_DPipe_print(io, "Toggled LED2!" ENDLINE ENDLINE);
            break;
        default: /* Turn off all LEDs */
            IfxPort_setPinState(LED1, IfxPort_State_high);
            IfxPort_setPinState(LED2, IfxPort_State_high);
            IfxStdIf_DPipe_print(io, "Command syntax not correct." ENDLINE \
                    "The correct syntax for this command is" ENDLINE "    '" COMMAND_TOGGLE " [0/1/2]'" ENDLINE \
                    "Turned off all LEDs!" ENDLINE);
            return FALSE; /* Returning false triggers a Shell command error */
    }
    return TRUE;
}

/* Function to initialize GPIO pins for LEDs */
void initLEDs(void)
{
    /* Initialize GPIO pins for LEDs */
    IfxPort_setPinMode(LED1, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinMode(LED2, IfxPort_Mode_outputPushPullGeneral);

    /* Turn off all LEDs */
    IfxPort_setPinState(LED1, IfxPort_State_high);
    IfxPort_setPinState(LED2, IfxPort_State_high);
}

/* Function to initialize ASCLIN module */
void initSerialInterface(void)
{
    IfxAsclin_Asc_Config ascConf;

    /* Set default configurations */
    IfxAsclin_Asc_initModuleConfig(&ascConf, &MODULE_ASCLIN0); /* Initialize the structure with default values      */

    /* Set the desired baud rate */
    ascConf.baudrate.baudrate = ASC_BAUDRATE;                                   /* Set the baud rate in bit/s       */
    ascConf.baudrate.oversampling = IfxAsclin_OversamplingFactor_16;            /* Set the oversampling factor      */

    /* Configure the sampling mode */
    ascConf.bitTiming.medianFilter = IfxAsclin_SamplesPerBit_three;             /* Set the number of samples per bit*/
    ascConf.bitTiming.samplePointPosition = IfxAsclin_SamplePointPosition_8;    /* Set the first sample position    */

    /* ISR priorities and interrupt target */
    ascConf.interrupt.txPriority = ISR_PRIORITY_ASCLIN_TX;  /* Set the interrupt priority for TX events             */
    ascConf.interrupt.rxPriority = ISR_PRIORITY_ASCLIN_RX;  /* Set the interrupt priority for RX events             */
    ascConf.interrupt.erPriority = ISR_PRIORITY_ASCLIN_ER;  /* Set the interrupt priority for Error events          */
    ascConf.interrupt.typeOfService = IfxSrc_Tos_cpu0;

    /* Pin configuration */
    const IfxAsclin_Asc_Pins pins = {
            .cts        = NULL_PTR,                         /* CTS pin not used                                     */
            .ctsMode    = IfxPort_InputMode_pullUp,
            .rx         = &IfxAsclin0_RXA_P14_1_IN,         /* Select the pin for RX connected to the USB port      */
            .rxMode     = IfxPort_InputMode_pullUp,         /* RX pin                                               */
            .rts        = NULL_PTR,                         /* RTS pin not used                                     */
            .rtsMode    = IfxPort_OutputMode_pushPull,
            .tx         = &IfxAsclin0_TX_P14_0_OUT,         /* Select the pin for TX connected to the USB port      */
            .txMode     = IfxPort_OutputMode_pushPull,      /* TX pin                                               */
            .pinDriver  = IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    ascConf.pins = &pins;

    /* FIFO buffers configuration */
    ascConf.txBuffer = g_uartTxBuffer;                      /* Set the transmission buffer                          */
    ascConf.txBufferSize = ASC_TX_BUFFER_SIZE;              /* Set the transmission buffer size                     */
    ascConf.rxBuffer = g_uartRxBuffer;                      /* Set the receiving buffer                             */
    ascConf.rxBufferSize = ASC_RX_BUFFER_SIZE;              /* Set the receiving buffer size                        */

    /* Init ASCLIN module */
    IfxAsclin_Asc_initModule(&g_asclin, &ascConf);          /* Initialize the module with the given configuration   */
}

/* Function to initialize the Shell */
void initShellInterface(void)
{
    /* Initialize the hardware peripherals */
    // initLEDs();
    initSerialInterface();

    /* Initialize the Standard Interface */
    IfxAsclin_Asc_stdIfDPipeInit(&g_ascStandardInterface, &g_asclin);

    /* Initialize the Console */
    // Ifx_Console_init(&g_ascStandardInterface);

    /* Print info to the console */
    // printInfo(&g_ascStandardInterface);
    // Ifx_Console_print(ENDLINE "Enter '" COMMAND_HELP "' to see the available commands" ENDLINE);

    /* Initialize the shell */
    // Ifx_Shell_Config shellConf;
    // Ifx_Shell_initConfig(&shellConf);                       /* Initialize the structure with default values         */

    // shellConf.standardIo = &g_ascStandardInterface;         /* Set a pointer to the standard interface              */
    // shellConf.commandList[0] = &g_shellCommands[0];         /* Set the supported command list                       */

    // Ifx_Shell_init(&g_shellInterface, &shellConf);          /* Initialize the Shell with the given configuration    */
}

/* Function to process the incoming received data */
void runShellInterface(void)
{
    /* Process the received data */
    Ifx_Shell_process(&g_shellInterface);
}
