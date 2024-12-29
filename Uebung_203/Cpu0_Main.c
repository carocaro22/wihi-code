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
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "App_Config.h"
#include "FreeRTOS.h"
#include "task.h"

IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;

/*********************************************************************************************************************/
/*------------------------------------------------------Constants Definitions----------------------------------------*/
/*********************************************************************************************************************/

#define PORT_LED_RED     &MODULE_P10,1
#define PORT_LED_YELLOW  &MODULE_P10,5
#define PORT_LED_GREEN   &MODULE_P02,6

/*********************************************************************************************************************/
/*------------------------------------------------------Task Definitions---------------------------------------------*/
/*********************************************************************************************************************/

void task_app_led_red(void *arg)
{
    while (1)
    {
        /* Toggle red LED state */
        IfxPort_setPinState(PORT_LED_RED, IfxPort_State_toggled);

        /* Delay 100ms */
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void task_app_led_yellow(void *arg)
{
    while (1)
    {
        /* Toggle yellow LED state */
        IfxPort_setPinState(PORT_LED_YELLOW, IfxPort_State_toggled);

        /* Delay 500ms */
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void task_app_led_green(void *arg)
{
    while (1)
    {
        /* Toggle green LED state */
        IfxPort_setPinState(PORT_LED_GREEN, IfxPort_State_toggled);

        /* Delay 1000ms */
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/*********************************************************************************************************************/
/*-------------------------------------------------Main Function-----------------------------------------------------*/
/*********************************************************************************************************************/
void core0_main(void)
{
    IfxCpu_enableInterrupts();
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);
    
    /*****************************************************************************************************************/
    /*-------------------------------------------------Modules Initialization----------------------------------------*/
    /*****************************************************************************************************************/

    // 1.) Initialize PORT_LED_RED as output
    IfxPort_setPinMode(PORT_LED_RED, IfxPort_Mode_outputPushPullGeneral);

    // 2.) Initialize PORT_LED_YELLOW as output
    IfxPort_setPinMode(PORT_LED_YELLOW, IfxPort_Mode_outputPushPullGeneral);

    // 3.) Initialize PORT_LED_GREEN as output
    IfxPort_setPinMode(PORT_LED_GREEN, IfxPort_Mode_outputPushPullGeneral);

    // 4.) Create the tasks
    xTaskCreate(task_app_led_red, "APP LED RED", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
    xTaskCreate(task_app_led_yellow, "APP LED YELLOW", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
    xTaskCreate(task_app_led_green, "APP LED GREEN", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

    // 5.) Start the scheduler
    vTaskStartScheduler();
    
    while (1)
    {
    }
}

/* Required FreeRTOS callback, called in case of a stack overflow.
 * For the sake of simplicity, this function will loop indefinitely
 * and the root cause can be confirmed by using a debugger
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    while (1)
    {
        __nop();
    }
}
