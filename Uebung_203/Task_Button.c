/********************************************************************************************************************/
/*  App_Led2.c                                                                                                     */
/*                                                                                                                  */
/*  Modul "Steuergeraete/Software/Vernetzung - Embedded Systems II"                                                 */
/*  Uebung 2-03: Demonstration of FreeRTOS                                                                          */
/*                                                                                                                  */
/*  Hochschule Mittweida, INW                                                                                       */
/*  Prof. J. Thomanek                                                                                               */
/*                                                                                                                  */
/********************************************************************************************************************/

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "IfxSrc.h"
#include "IfxScuEru.h"

#include "App_Config.h"
#include "FreeRTOS.h"
#include "task.h"

/*********************************************************************************************************************/
/*-----------------------------------------------------Macros--------------------------------------------------------*/
/*********************************************************************************************************************/
#define ISR_PRIORITY_SCUERU_INT0 (3)                        /* Define the SCU ERU interrupt priority                 */

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
static TaskHandle_t g_AppTaskHandle;                            /* LED2 App task handle                              */
static const IfxScu_Req_In * g_ReqIn = &IfxScu_REQ3C_P02_0_IN;  /* External Request pin: P33.7                       */

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
/* ISR for handling the ERU interrupt */
IFX_INTERRUPT(SCUERU_Int0_Handler, 0, ISR_PRIORITY_SCUERU_INT0)
{
    BaseType_t externalIsrTriggered;

    /* Notify task from ISR */
    vTaskNotifyGiveFromISR(g_AppTaskHandle, &externalIsrTriggered);

    /* Yield if higher priority task is selected */
    portYIELD_FROM_ISR(externalIsrTriggered);
}


/* Initialization function for LED2 app */
static void app_init(void)
{
    IfxScuEru_InputNodePointer triggerSelect    = IfxScuEru_InputNodePointer_0;
    IfxScuEru_OutputChannel outputChannel       = IfxScuEru_OutputChannel_0;
    IfxScuEru_InputChannel inputChannel         = (IfxScuEru_InputChannel)g_ReqIn->channelId;

    /* Enable input mode with pull-down for the REQ_IN pin and configure the ERU input multiplexer */
    IfxScuEru_initReqPin(g_ReqIn, IfxPort_InputMode_pullDown);

    /* Input channel configuration, interrupt triggered on a falling edge */
    IfxScuEru_enableFallingEdgeDetection(inputChannel);

    /* Event Trigger Logic (ETL) configuration... */
    IfxScuEru_enableTriggerPulse(inputChannel);             /* Enable trigger event */
    IfxScuEru_connectTrigger(inputChannel, triggerSelect);  /* Set output channel for trigger event */

    /* Configure output channel in the OutputGating Unit (OGU) */
    IfxScuEru_setInterruptGatingPattern(outputChannel, IfxScuEru_InterruptGatingPattern_alwaysActive);
    /* --- */

    /* Service request configuration */
    /* Get source pointer depending on outputChannel (SRC_SCUERU0 for outputChannel0) */
    volatile Ifx_SRC_SRCR *srcReg = &MODULE_SRC.SCU.SCUERU[(int)outputChannel % 4];
    IfxSrc_init(srcReg, IfxSrc_Tos_cpu0, ISR_PRIORITY_SCUERU_INT0);
    IfxSrc_enable(srcReg);
    /* --- */
}
