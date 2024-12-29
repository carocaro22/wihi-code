#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "App_Config.h"
#include "FreeRTOS.h"
#include "task.h"

IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;

void core0_main(void)
{
    IfxCpu_enableInterrupts();
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);
    
    /* Create LED1 app task */
    xTaskCreate(task_app_led1, "APP LED1", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

    /* Create LED2 app task */
    xTaskCreate(task_app_led2, "APP LED2", configMINIMAL_STACK_SIZE, NULL, 0, NULL);

    /* Start the scheduler */
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
