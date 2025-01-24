/*
 * millis.c
 *
 *  Created on: 23 de jan. de 2025
 *      Author: carolina
 */

#include "Millis.h"

#include "IfxStm.h"

// Millis
#define STM                     &MODULE_STM0
#define ISR_PRIORITY_STM        255

static unsigned long currentMillis = 0;
IfxStm_CompareConfig g_STMConf; // STM Configuration Structure
uint32 g_ticksFor1ms; /* Variable to store the number of ticks to wait    */

IFX_INTERRUPT(isrSTM, 0, ISR_PRIORITY_STM);

void isrSTM (void)
{
    IfxStm_increaseCompare(STM, g_STMConf.comparator, g_ticksFor1ms);
    currentMillis++;
}

unsigned long millis()
{
    return currentMillis;
}

void initTimer(void)
{
    g_ticksFor1ms = IfxStm_getTicksFromMilliseconds(STM, 1);

    IfxStm_initCompareConfig(&g_STMConf); // Initialize the configuration structure with default values

    g_STMConf.triggerPriority = ISR_PRIORITY_STM; // Set the priority of the interrupt
    g_STMConf.typeOfService = IfxSrc_Tos_cpu0; // Set the service provider for the interrupts (Cpu0)
    g_STMConf.ticks = g_ticksFor1ms; // Set the number of ticks after which the timer triggers an interrupt for the first time

    IfxStm_initCompare(&MODULE_STM0, &g_STMConf); // Initialize the STM with the user configuration
}
