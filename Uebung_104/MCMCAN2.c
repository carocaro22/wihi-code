/********************************************************************************************************************/
/*  MCMCAN.c                                                                                                        */
/*                                                                                                                  */
/*  Modul "Steuergeraete/Software/Vernetzung - Embedded Systems II"                                                 */
/*  Uebung 1-04: CAN-Nachricht versenden                                                                            */
/*                                                                                                                  */
/*  Hochschule Mittweida, INW                                                                                       */
/*  Prof. J. Thomanek                                                                                               */
/*                                                                                                                  */
/********************************************************************************************************************/

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "MCMCAN2.h"

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
McmcanType                  g_mcmcan;                        /* Global MCMCAN configuration and control structure    */

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
IFX_INTERRUPT(canIsrTxHandler, 0, ISR_PRIORITY_CAN_TX);

typedef struct {
    Ifx_P *port;           // Pointer to the port module
    IfxPort_Pin pinIndex;
    IfxPort_OutputIdx mode;           // Mode of the port
    IfxPort_PadDriver padDriver;      // Pad driver configuration
} PortConfig_t;

PortConfig_t g_stb;

void canIsrTxHandler(void)
{
    IfxCan_Node_clearInterruptFlag(g_mcmcan.canSrcNode.node, IfxCan_Interrupt_transmissionCompleted);
}

void initMCMCAN(void)
{
    // why should I have to disable interrupts?
    //boolean iState = IfxCpu_disableInterrupts();

    // Default config
    IfxCan_Can_initModuleConfig(&g_mcmcan.canConfig, &MODULE_CAN0);
    IfxCan_Can_initModule(&g_mcmcan.canModule, &g_mcmcan.canConfig);
    IfxCan_Can_initNodeConfig(&g_mcmcan.canNodeConfig, &g_mcmcan.canModule);
    // set breakpoint here to see default configs

    g_mcmcan.canNodeConfig.nodeId = IfxCan_NodeId_0;
    g_mcmcan.canNodeConfig.frame.type = IfxCan_FrameType_transmit;

    IfxCan_Can_Pins pins;
    pins.txPin = (&MODULE_P20, 8);
    pins.txPinMode = IfxPort_OutputMode_pushPull;
    pins.padDriver = IfxPort_PadDriver_cmosAutomotiveSpeed2;
    g_mcmcan.canNodeConfig.pins = &pins;
    IfxCan_Can_initNode(&g_mcmcan.canSrcNode, &g_mcmcan.canNodeConfig);

    // Konfiguration des Ports g_stb, um Nachrichten nach aussen versenden zu konnen
//    g_stb.port = &MODULE_P20;
//    g_stb.pinIndex = 8;
//    g_stb.mode = IfxPort_OutputIdx_general;
//    g_stb.padDriver = IfxPort_PadDriver_cmosAutomotiveSpeed1;
//    IfxPort_setPinLow(g_stb.port, g_stb.pinIndex);
//    IfxPort_setPinModeOutput(g_stb.port, g_stb.pinIndex, IfxPort_OutputMode_pushPull, g_stb.mode);
//    IfxPort_setPinPadDriver(g_stb.port, g_stb.pinIndex, g_stb.padDriver);

    //IfxCpu_restoreInterrupts(iState);
}

void transmitCanMessage(unsigned int message, uint32 messageId)
{
    IfxCan_Can_initMessage(&g_mcmcan.txMsg);
    /* CAN Identifier - Use Test place number + 100 hex */
    g_mcmcan.txMsg.messageId = messageId;
    g_mcmcan.txData[0] = message;

    /* Send the CAN message with the previously defined TX message content */
    while( IfxCan_Status_notSentBusy ==
           IfxCan_Can_sendMessage(&g_mcmcan.canSrcNode, &g_mcmcan.txMsg, &g_mcmcan.txData[0]) )
    {
    }
}
