#include "Ifx_Types.h"
#include "IfxSrc.h"
#include "IfxScuEru.h"
#include <IfxPort.h>

/********************************************************************************************************************/
/*-----------------------------------------------------Macros-------------------------------------------------------*/
/********************************************************************************************************************/

#define ISR_PRIORITY_SCUERU_INT0   40                       /* Define the SCU ERU interrupt priority                */
#define REQ_IN                     &IfxScu_REQ3C_P02_0_IN   /* External request pin                                 */
#define TRIGGER_PIN                &MODULE_P02, 0           /* Pin that is toggled by pressing the board's button   */

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
typedef struct
{
    IfxScu_Req_In *reqPin;                      /* External request pin                                             */
    IfxScuEru_InputChannel inputChannel;        /* Input channel EICRm depending on input pin                       */
    IfxScuEru_InputNodePointer triggerSelect;   /* Input node pointer                                               */
    IfxScuEru_OutputChannel outputChannel;      /* Output channel                                                   */
    volatile Ifx_SRC_SRCR *src;                 /* Service request register                                         */
} ERUconfig;

ERUconfig g_ERUconfig;

/* Global function pointer to store the ISR function */
static void (*g_isrFunction)(void) = NULL;

void SCUERU_Int0_Handler(void);

IFX_INTERRUPT(SCUERU_Int0_Handler, 0, ISR_PRIORITY_SCUERU_INT0);

/* Interrupt Service Routine */
void SCUERU_Int0_Handler(void (*isr)(void))
{
    if (g_isrFunction != NULL)
    {
        /* Call the function stored in the global function pointer */
        g_isrFunction();
    }
}

void initERU(void (*isr)(void))
{
    /* Store the passed ISR function in the global function pointer */
    g_isrFunction = isr;

    /* Initialize pins which are used to trigger and visualize the interrupt and set the default states */
    IfxPort_setPinMode(TRIGGER_PIN, IfxPort_Mode_inputPullUp);              /* Initialize TRIGGER_PIN port pin  */

    /* Trigger pin */
    g_ERUconfig.reqPin = REQ_IN; /* Select external request pin */

    /* Initialize this pin with pull-down enabled
     * This function will also configure the input multiplexers of the ERU (Register EXISx)
     */
    IfxScuEru_initReqPin(g_ERUconfig.reqPin, IfxPort_InputMode_pullDown);

    /* Determine input channel depending on input pin */
    g_ERUconfig.inputChannel = (IfxScuEru_InputChannel) g_ERUconfig.reqPin->channelId;

    /* Input channel configuration */
    // IfxScuEru_enableRisingEdgeDetection(g_ERUconfig.inputChannel);          /* Interrupt triggers on rising edge (Register RENx) and  */
    IfxScuEru_enableFallingEdgeDetection(g_ERUconfig.inputChannel);         /* on falling edge (Register FENx)  */

    /* Signal destination */
    g_ERUconfig.outputChannel = IfxScuEru_OutputChannel_0;                  /* OGU channel 0                    */
    /* Event from input ETL0 triggers output OGU0 (signal TRx0) */
    g_ERUconfig.triggerSelect = IfxScuEru_InputNodePointer_0;

    /* Connecting Matrix, Event Trigger Logic ETL block */
    /* Enable generation of trigger event (Register EIENx) */
    IfxScuEru_enableTriggerPulse(g_ERUconfig.inputChannel);
    /* Determination of output channel for trigger event (Register INPx) */
    IfxScuEru_connectTrigger(g_ERUconfig.inputChannel, g_ERUconfig.triggerSelect);

    /* Configure Output channels, OutputGating Unit OGU (Register IGPy) */
    IfxScuEru_setInterruptGatingPattern(g_ERUconfig.outputChannel, IfxScuEru_InterruptGatingPattern_alwaysActive);

    /* Service request configuration */
    /* Get source pointer depending on outputChannel (SRC_SCUERU0 for outputChannel0) */
    g_ERUconfig.src = &MODULE_SRC.SCU.SCUERU[(int) g_ERUconfig.outputChannel % 4];
    IfxSrc_init(g_ERUconfig.src, IfxSrc_Tos_cpu0, ISR_PRIORITY_SCUERU_INT0);
    IfxSrc_enable(g_ERUconfig.src);
}
