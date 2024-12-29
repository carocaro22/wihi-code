/********************************************************************************************************************/
/*  Cpu0_Main.c                                                                                                     */
/*                                                                                                                  */
/*  Modul "Steuergeraete/Software/Vernetzung - Embedded Systems II"                                                 */
/*  Uebung 2-02: Demonstration of a simple non-preemptive scheduler                                                 */
/*                                                                                                                  */
/*  Hochschule Mittweida, INW                                                                                       */
/*  Prof. J. Thomanek                                                                                               */
/*                                                                                                                  */
/********************************************************************************************************************/

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/

// Standard C Libratry
#include <stdbool.h>

// Infineon Low Level Drivers
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "IfxPort.h"

// Project Includes
#include "Scheduler.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Constants Definitions----------------------------------------*/
/*********************************************************************************************************************/

#define PORT_LED_RED     &MODULE_P10,1
#define PORT_LED_YELLOW  &MODULE_P10,5
#define PORT_LED_GREEN   &MODULE_P02,6

/*********************************************************************************************************************/
/*------------------------------------------------------Task Definitions---------------------------------------------*/
/*********************************************************************************************************************/

// Cyclic Task 1 - cycle time 100 ms
// ---------------------------------------------------------
void My100msTask() {
  static bool mode = false;

  // Toogle mode
  mode = !mode;

  if (mode == true)
    IfxPort_setPinHigh(PORT_LED_RED);
  else
    IfxPort_setPinLow(PORT_LED_RED);
}

// Cyclic Task 2 - cycle time 500 ms
// ---------------------------------------------------------
void My500msTask() {
  static bool mode = false;

  // Toogle mode
  mode = !mode;

  if (mode == true)
    IfxPort_setPinHigh(PORT_LED_YELLOW);
  else
    IfxPort_setPinLow(PORT_LED_YELLOW);
}

// Cyclic Task 3 - cycle time 1000 ms
// ---------------------------------------------------------
void My1000msTask() {
  static bool mode = false;

  // Toogle mode
  mode = !mode;

  if (mode == true)
    IfxPort_setPinHigh(PORT_LED_GREEN);
  else
    IfxPort_setPinLow(PORT_LED_GREEN);
}

IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;

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
    IfxPort_setPinModeOutput(PORT_LED_RED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);

    // 2.) Initialize PORT_LED_YELLOW as output
    IfxPort_setPinModeOutput(PORT_LED_YELLOW, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);

    // 3.) Initialize PORT_LED_GREEN as output
    IfxPort_setPinModeOutput(PORT_LED_GREEN, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);

    // 4.) Initialize the scheduler
    SchedInit();

    // 5.) Add the user tasks
    AddTask(TASKTYPE_CYCLIC, (Task_fp)My100msTask, 100);
    AddTask(TASKTYPE_CYCLIC, (Task_fp)My500msTask, 500);
    AddTask(TASKTYPE_CYCLIC, (Task_fp)My1000msTask, 1000);

    /*****************************************************************************************************************/
    /*-------------------------------------------------Main Loop-----------------------------------------------------*/
    /*****************************************************************************************************************/
    while(1)
    {
        // 6.) Run the scheduler
        SchedRun();
    }
}
