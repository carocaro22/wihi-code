/********************************************************************************************************************/
/*  Cpu0_Main.c                                                                                                     */
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
//#include "IfxCpu.h"
//#include "IfxScuWdt.h"
#include "IfxScuEru.h"
#include "IfxSrc.h"

#include "App_Config.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Constants Definitions----------------------------------------*/
/*********************************************************************************************************************/

#define PORT_LED_RED     &MODULE_P10,1
#define PORT_LED_YELLOW  &MODULE_P10,5
#define PORT_LED_GREEN   &MODULE_P02,6

// Button pressed flag
boolean bSigRequest = FALSE;

// Queue handle
QueueHandle_t hQueue;

// External request pin
static const IfxScu_Req_In *g_ReqIn = &IfxScu_REQ3C_P02_0_IN; /* External Request pin: P33.7                       */

/*********************************************************************************************************************/
/*---------------------------------------------Interrupt Service Routine---------------------------------------------*/
/*********************************************************************************************************************/

/* ISR for handling the ERU interrupt */
IFX_INTERRUPT(SCUERU_Int0_Handler, 0, 255)
{
    //BaseType_t externalIsrTriggered;

    /* Notify task from ISR */
    bSigRequest = TRUE;

    /* Yield if higher priority task is selected */
    //portYIELD_FROM_ISR(externalIsrTriggered);
}

/*********************************************************************************************************************/
/*------------------------------------------------------Task Definitions---------------------------------------------*/
/*********************************************************************************************************************/

void task_app_led_red (void *arg)
{
    while (1)
    {
        /* Toggle red LED state */
        IfxPort_setPinState(PORT_LED_RED, IfxPort_State_toggled);

        /* Delay 100ms */
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void task_app_led_yellow (void *arg)
{
    while (1)
    {
        /* Toggle yellow LED state */
        IfxPort_setPinState(PORT_LED_YELLOW, IfxPort_State_toggled);

        /* Delay 500ms */
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void task_app_led_green (void *arg)
{
    while (1)
    {
        /* Toggle green LED state */
        IfxPort_setPinState(PORT_LED_GREEN, IfxPort_State_toggled);

        /* Delay 1000ms */
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void task_app_button (void *arg)
{
    uint16_t data = 500;
    for (;;)
    {
        if (bSigRequest == TRUE)
        {
            xQueueSend(hQueue, &data, 0);
            if (data == 500)
                data = 100;
            else
                data = 500;
            bSigRequest = TRUE;
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

/*********************************************************************************************************************/
/*-------------------------------------------------Main Function-----------------------------------------------------*/
/*********************************************************************************************************************/

IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;

void core0_main (void)
{
    IfxCpu_enableInterrupts();
    
    /*****************************************************************************************************************/
    /*-------------------------------------------------Modules Initialization----------------------------------------*/
    /*****************************************************************************************************************/

    // 1.) Initialize PORT_LED_RED as output
    IfxPort_setPinMode(PORT_LED_RED, IfxPort_Mode_outputPushPullGeneral);

    // 2.) Initialize PORT_LED_YELLOW as output
    IfxPort_setPinMode(PORT_LED_YELLOW, IfxPort_Mode_outputPushPullGeneral);

    // 3.) Initialize PORT_LED_GREEN as output
    IfxPort_setPinMode(PORT_LED_GREEN, IfxPort_Mode_outputPushPullGeneral);

    // 5.) Initialize PORT_BUTTON
    IfxScuEru_InputNodePointer triggerSelect = IfxScuEru_InputNodePointer_0;
    IfxScuEru_OutputChannel outputChannel = IfxScuEru_OutputChannel_0;
    IfxScuEru_InputChannel inputChannel = (IfxScuEru_InputChannel) g_ReqIn->channelId;

    /* Enable input mode with pull-down for the REQ_IN pin and configure the ERU input multiplexer */
    IfxScuEru_initReqPin(g_ReqIn, IfxPort_InputMode_pullDown);

    /* Input channel configuration, interrupt triggered on a falling edge */
    IfxScuEru_enableFallingEdgeDetection(inputChannel);

    /* Event Trigger Logic (ETL) configuration... */
    IfxScuEru_enableTriggerPulse(inputChannel); /* Enable trigger event */
    IfxScuEru_connectTrigger(inputChannel, triggerSelect); /* Set output channel for trigger event */

    /* Configure output channel in the OutputGating Unit (OGU) */
    IfxScuEru_setInterruptGatingPattern(outputChannel, IfxScuEru_InterruptGatingPattern_alwaysActive);
    /* --- */

    /* Service request configuration */
    /* Get source pointer depending on outputChannel (SRC_SCUERU0 for outputChannel0) */
    volatile Ifx_SRC_SRCR *srcReg = &MODULE_SRC.SCU.SCUERU[(int) outputChannel % 4];
    IfxSrc_init(srcReg, IfxSrc_Tos_cpu0, 255);
    IfxSrc_enable(srcReg);

    // 6.) Create the tasks
    xTaskCreate(task_app_led_red, "APP LED RED", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
    xTaskCreate(task_app_led_yellow, "APP LED YELLOW", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
    xTaskCreate(task_app_led_green, "APP LED GREEN", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
    xTaskCreate(task_app_button, "Button control", 128, NULL, 1, NULL);

    // 7.) Start the scheduler
    vTaskStartScheduler();
    
    while (1)
    {
    }
}

/* Required FreeRTOS callback, called in case of a stack overflow.
 * For the sake of simplicity, this function will loop indefinitely
 * and the root cause can be confirmed by using a debugger
 */
void vApplicationStackOverflowHook (TaskHandle_t xTask, char *pcTaskName)
{
    while (1)
    {
        __nop();
    }
}
