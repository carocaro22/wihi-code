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
const float Kelvin_offset = 273.15;

// Voltage supply
const float U_max = 5.0;

// Max value of the ADC
const int Inp_max = 1023;

// Series resistor 10k
const float R_vor = 10000.0;

// B value
const float B_val = 3435;

// resistor value of the thermistor on 25 °C
const float R_therm25 = 10000.0;

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
    initMcmcan();
    // 2.) Initialize ADC Module
    initEVADC();

    /*********************************************************************************************************************/
    /*-------------------------------------------------Main Loop---------------------------------------------------------*/
    /*********************************************************************************************************************/
    while(1)
    {
        // 3.) Calculate temperature in Kelvin of the thermistor
        volatile float T_therm25 = 25 + Kelvin_offset;

        // 4.) Get analog input value on Pin A5
        volatile unsigned int input = readEVADC();

        // 5.) Calculate measured voltage
        volatile float U_inp = input * (U_max/Inp_max);

        // 6.) Calculate resistance based on voltage devider rule
        volatile float R = R_vor / (U_max/U_inp - 1);

        // 7.) Calculate temperature
        volatile float T = 1/((1/B_val) * log(R/R_therm25) + (1/T_therm25)) - Kelvin_offset;

        // 8.) Transmit Can Message
        transmitCanMessage(T, 0x106);

        // 9.) Wait a second
        waitTime(1000);
    }
}

