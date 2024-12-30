/**
 * \file IfxGtm_Spe.c
 * \brief GTM  basic functionality
 *
 * \version iLLD_1_0_1_16_0_1
 * \copyright Copyright (c) 2018 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 * Use of this file is subject to the terms of use agreed between (i) you or
 * the company in which ordinary course of business you are acting and (ii)
 * Infineon Technologies AG or its licensees. If and as long as no such terms
 * of use are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 *
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxGtm_Spe.h"

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

void IfxGtm_Spe_disableInterrupt(Ifx_GTM_SPE *spe, IfxGtm_Spe_InterruptSignal interrupt)
{
    uint32 irqen_temp = spe->IRQ.EN.U;
    irqen_temp    = (irqen_temp ^ ((uint32)1 << interrupt));
    spe->IRQ.EN.U = irqen_temp;
}


void IfxGtm_Spe_enableErrorInterrupt(Ifx_GTM_SPE *spe, IfxGtm_Spe_InterruptSignal interrupt, boolean enabled)
{
    uint32 irqen_temp = spe->EIRQ_EN.U;
    irqen_temp     = (irqen_temp | ((uint32)1 << interrupt)) & ((uint32)enabled << interrupt);
    spe->EIRQ_EN.U = irqen_temp;
}


void IfxGtm_Spe_enableInput(Ifx_GTM_SPE *spe, IfxGtm_Spe_InputSignal inputSignal, boolean enabled)
{
    switch (enabled)
    {
    case TRUE:
    {
        spe->CTRL_STAT.U |= ((uint32)enabled << ((uint32)inputSignal + IFX_GTM_SPE_CTRL_STAT_SIE0_OFF));
        break;
    }
    case FALSE:
        spe->CTRL_STAT.U &= ((uint32)enabled << ((uint32)inputSignal + IFX_GTM_SPE_CTRL_STAT_SIE0_OFF));
        break;
    }
}


void IfxGtm_Spe_enableInterrupt(Ifx_GTM_SPE *spe, IfxGtm_Spe_InterruptSignal interrupt)
{
    uint32 irqen_temp = spe->IRQ.EN.U;
    irqen_temp    = (irqen_temp | ((uint32)1 << interrupt));
    spe->IRQ.EN.U = irqen_temp;
}


uint32 IfxGtm_Spe_getFastShutoffLevel(Ifx_GTM_SPE *spe, IfxGtm_Spe_OutChannel channel)
{
    uint32 fsol_temp = (uint32)(spe->CTRL_STAT.B.FSOL);
    fsol_temp = (fsol_temp & (uint32)(1 << (uint32)channel)) >> (uint32)channel;
    return (uint32)fsol_temp;
}


boolean IfxGtm_Spe_getInterruptStatus(Ifx_GTM_SPE *spe, IfxGtm_Spe_InterruptSignal interrupt)
{
    return (((spe->IRQ.NOTIFY.U) >> interrupt) & (uint32)1) == (uint32)1;
}


uint32 IfxGtm_Spe_getRevCompare(Ifx_GTM_SPE *spe)
{
    return (uint32)(spe->REV_CMP.B.REV_CMP);
}


void IfxGtm_Spe_selectTrigger(Ifx_GTM_SPE *spe, IfxGtm_Spe_TriggerSource trigger)
{
    Ifx_GTM_SPE_CTRL_STAT ctrl_stat;
    ctrl_stat.U           = spe->CTRL_STAT.U;

    ctrl_stat.B.TRIG_SEL  = IFXGTM_SPE_GET_TRIGSEL(trigger);
    ctrl_stat.B.ETRIG_SEL = IFXGTM_SPE_GET_ETRIG(trigger);

    spe->CTRL_STAT.U      = ctrl_stat.U;
}


void IfxGtm_Spe_setAllInputPatterns(Ifx_GTM_SPE *spe, IfxGtm_Spe_InputPattern *patPtr)
{
    uint32 spepat_temp = spe->PAT.U;

    spepat_temp = IFXGTM_SPE_GETALLPATTERNS(patPtr);

    spe->PAT.U  = spepat_temp;
}


void IfxGtm_Spe_setInputPattern(Ifx_GTM_SPE *spe, IfxGtm_Spe_InputPattern *patPtr, IfxGtm_Spe_PatternIndex patIndex)
{
    uint32 pattern     = patPtr->U;
    uint32 spepat_temp = spe->PAT.U;

    spepat_temp = IFXGTM_SPE_SETSINGLEPATTERN(spepat_temp, pattern, patIndex);

    spe->PAT.U  = spepat_temp;
}


void IfxGtm_Spe_setInterrupt(Ifx_GTM_SPE *spe, IfxGtm_Spe_InterruptSignal interrupt)
{
    uint32 forceirq_temp = spe->IRQ.FORCINT.U;
    forceirq_temp      = (forceirq_temp | ((uint32)1 << interrupt));
    spe->IRQ.FORCINT.U = forceirq_temp;
}


void IfxGtm_Spe_setOutputPattern(Ifx_GTM_SPE *spe, IfxGtm_Spe_OutputPattern *patPtr, IfxGtm_Spe_PatternIndex patIndex)
{
    spe->OUT_PAT[patIndex].U = patPtr->U;
}


void IfxGtm_Spe_setRevCompare(Ifx_GTM_SPE *spe, uint32 count)
{
    spe->REV_CMP.B.REV_CMP = count;
}
