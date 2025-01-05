/********************************************************************************************************************/
/*  Cpu0_Main.c                                                                                                     */
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

// Standard C Library
#include <math.h>

// Infineon Low level Drivers
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "IfxStm.h"

// Project Includes
#include "MCMCAN.h"
#include "ADC_Single_Channel.h"
#include "Bsp.h"

IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;

/*********************************************************************************************************************/
/*-------------------------------------------------Constant Definitions----------------------------------------------*/
/*********************************************************************************************************************/

// Kelvin offset


// Voltage supply


// Max value of the ADC


// Series resistor 10k


// B value


// resistor value of the thermistor on 25 °C


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
    
    /*********************************************************************************************************************/
    /*-------------------------------------------------Modules Initialization--------------------------------------------*/
    /*********************************************************************************************************************/
    // 1.) Initialisaze the MCMCAN module


    // 2.) Initialize EVADC Module


    /*********************************************************************************************************************/
    /*-------------------------------------------------Main Loop---------------------------------------------------------*/
    /*********************************************************************************************************************/
    while(1)
    {
        // 1.) Calculate temperature in Kelvin of the thermistor


        // 2.) Get analog input value on Pin A5


        // 3.) Calculate measured voltage


        // 4.) Calculate resistance based on voltage devider rule


        // 5.) Calculate temperature


        // 6.) Transmit Can Message - Use Test place number + 100 hex for the CAN-Identifier


        // 7.) Wait a second

    }
}

