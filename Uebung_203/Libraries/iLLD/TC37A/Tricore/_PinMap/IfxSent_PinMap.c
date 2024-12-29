/**
 * \file IfxSent_PinMap.c
 * \brief SENT I/O map
 * \ingroup IfxLld_Sent
 *
 * \version iLLD_1_0_1_16_0_1
 * \copyright Copyright (c) 2017 Infineon Technologies AG. All rights reserved.
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
 */

#include "IfxSent_PinMap.h"

IfxSent_Sent_In IfxSent_SENT0A_P40_0_IN = {&MODULE_SENT, IfxSent_ChannelId_0, {&MODULE_P40, 0}, Ifx_RxSel_a};
IfxSent_Sent_In IfxSent_SENT0B_P00_1_IN = {&MODULE_SENT, IfxSent_ChannelId_0, {&MODULE_P00, 1}, Ifx_RxSel_b};
IfxSent_Sent_In IfxSent_SENT0C_P02_8_IN = {&MODULE_SENT, IfxSent_ChannelId_0, {&MODULE_P02, 8}, Ifx_RxSel_c};
IfxSent_Sent_In IfxSent_SENT10A_P40_10_IN = {&MODULE_SENT, IfxSent_ChannelId_10, {&MODULE_P40,10}, Ifx_RxSel_a};
IfxSent_Sent_In IfxSent_SENT10B_P00_11_IN = {&MODULE_SENT, IfxSent_ChannelId_10, {&MODULE_P00,11}, Ifx_RxSel_b};
IfxSent_Sent_In IfxSent_SENT10C_P32_5_IN = {&MODULE_SENT, IfxSent_ChannelId_10, {&MODULE_P32, 5}, Ifx_RxSel_c};
IfxSent_Sent_In IfxSent_SENT10D_P15_2_IN = {&MODULE_SENT, IfxSent_ChannelId_10, {&MODULE_P15, 2}, Ifx_RxSel_d};
IfxSent_Sent_In IfxSent_SENT11A_P40_11_IN = {&MODULE_SENT, IfxSent_ChannelId_11, {&MODULE_P40,11}, Ifx_RxSel_a};
IfxSent_Sent_In IfxSent_SENT11B_P00_12_IN = {&MODULE_SENT, IfxSent_ChannelId_11, {&MODULE_P00,12}, Ifx_RxSel_b};
IfxSent_Sent_In IfxSent_SENT11C_P32_6_IN = {&MODULE_SENT, IfxSent_ChannelId_11, {&MODULE_P32, 6}, Ifx_RxSel_c};
IfxSent_Sent_In IfxSent_SENT11D_P15_4_IN = {&MODULE_SENT, IfxSent_ChannelId_11, {&MODULE_P15, 4}, Ifx_RxSel_d};
IfxSent_Sent_In IfxSent_SENT12A_P40_12_IN = {&MODULE_SENT, IfxSent_ChannelId_12, {&MODULE_P40,12}, Ifx_RxSel_a};
IfxSent_Sent_In IfxSent_SENT12B_P02_4_IN = {&MODULE_SENT, IfxSent_ChannelId_12, {&MODULE_P02, 4}, Ifx_RxSel_b};
IfxSent_Sent_In IfxSent_SENT12C_P32_7_IN = {&MODULE_SENT, IfxSent_ChannelId_12, {&MODULE_P32, 7}, Ifx_RxSel_c};
IfxSent_Sent_In IfxSent_SENT13A_P40_13_IN = {&MODULE_SENT, IfxSent_ChannelId_13, {&MODULE_P40,13}, Ifx_RxSel_a};
IfxSent_Sent_In IfxSent_SENT13B_P02_3_IN = {&MODULE_SENT, IfxSent_ChannelId_13, {&MODULE_P02, 3}, Ifx_RxSel_b};
IfxSent_Sent_In IfxSent_SENT13C_P33_0_IN = {&MODULE_SENT, IfxSent_ChannelId_13, {&MODULE_P33, 0}, Ifx_RxSel_c};
IfxSent_Sent_In IfxSent_SENT14A_P40_14_IN = {&MODULE_SENT, IfxSent_ChannelId_14, {&MODULE_P40,14}, Ifx_RxSel_a};
IfxSent_Sent_In IfxSent_SENT14B_P02_2_IN = {&MODULE_SENT, IfxSent_ChannelId_14, {&MODULE_P02, 2}, Ifx_RxSel_b};
IfxSent_Sent_In IfxSent_SENT14C_P33_7_IN = {&MODULE_SENT, IfxSent_ChannelId_14, {&MODULE_P33, 7}, Ifx_RxSel_c};
IfxSent_Sent_In IfxSent_SENT1A_P40_1_IN = {&MODULE_SENT, IfxSent_ChannelId_1, {&MODULE_P40, 1}, Ifx_RxSel_a};
IfxSent_Sent_In IfxSent_SENT1B_P00_2_IN = {&MODULE_SENT, IfxSent_ChannelId_1, {&MODULE_P00, 2}, Ifx_RxSel_b};
IfxSent_Sent_In IfxSent_SENT1C_P02_7_IN = {&MODULE_SENT, IfxSent_ChannelId_1, {&MODULE_P02, 7}, Ifx_RxSel_c};
IfxSent_Sent_In IfxSent_SENT2A_P40_2_IN = {&MODULE_SENT, IfxSent_ChannelId_2, {&MODULE_P40, 2}, Ifx_RxSel_a};
IfxSent_Sent_In IfxSent_SENT2B_P00_3_IN = {&MODULE_SENT, IfxSent_ChannelId_2, {&MODULE_P00, 3}, Ifx_RxSel_b};
IfxSent_Sent_In IfxSent_SENT2C_P02_6_IN = {&MODULE_SENT, IfxSent_ChannelId_2, {&MODULE_P02, 6}, Ifx_RxSel_c};
IfxSent_Sent_In IfxSent_SENT3A_P40_3_IN = {&MODULE_SENT, IfxSent_ChannelId_3, {&MODULE_P40, 3}, Ifx_RxSel_a};
IfxSent_Sent_In IfxSent_SENT3B_P00_4_IN = {&MODULE_SENT, IfxSent_ChannelId_3, {&MODULE_P00, 4}, Ifx_RxSel_b};
IfxSent_Sent_In IfxSent_SENT3C_P02_5_IN = {&MODULE_SENT, IfxSent_ChannelId_3, {&MODULE_P02, 5}, Ifx_RxSel_c};
IfxSent_Sent_In IfxSent_SENT4A_P40_4_IN = {&MODULE_SENT, IfxSent_ChannelId_4, {&MODULE_P40, 4}, Ifx_RxSel_a};
IfxSent_Sent_In IfxSent_SENT4B_P00_5_IN = {&MODULE_SENT, IfxSent_ChannelId_4, {&MODULE_P00, 5}, Ifx_RxSel_b};
IfxSent_Sent_In IfxSent_SENT4C_P33_6_IN = {&MODULE_SENT, IfxSent_ChannelId_4, {&MODULE_P33, 6}, Ifx_RxSel_c};
IfxSent_Sent_In IfxSent_SENT5A_P40_5_IN = {&MODULE_SENT, IfxSent_ChannelId_5, {&MODULE_P40, 5}, Ifx_RxSel_a};
IfxSent_Sent_In IfxSent_SENT5B_P00_6_IN = {&MODULE_SENT, IfxSent_ChannelId_5, {&MODULE_P00, 6}, Ifx_RxSel_b};
IfxSent_Sent_In IfxSent_SENT5C_P33_5_IN = {&MODULE_SENT, IfxSent_ChannelId_5, {&MODULE_P33, 5}, Ifx_RxSel_c};
IfxSent_Sent_In IfxSent_SENT6A_P40_6_IN = {&MODULE_SENT, IfxSent_ChannelId_6, {&MODULE_P40, 6}, Ifx_RxSel_a};
IfxSent_Sent_In IfxSent_SENT6B_P00_7_IN = {&MODULE_SENT, IfxSent_ChannelId_6, {&MODULE_P00, 7}, Ifx_RxSel_b};
IfxSent_Sent_In IfxSent_SENT6C_P33_4_IN = {&MODULE_SENT, IfxSent_ChannelId_6, {&MODULE_P33, 4}, Ifx_RxSel_c};
IfxSent_Sent_In IfxSent_SENT7A_P40_7_IN = {&MODULE_SENT, IfxSent_ChannelId_7, {&MODULE_P40, 7}, Ifx_RxSel_a};
IfxSent_Sent_In IfxSent_SENT7B_P00_8_IN = {&MODULE_SENT, IfxSent_ChannelId_7, {&MODULE_P00, 8}, Ifx_RxSel_b};
IfxSent_Sent_In IfxSent_SENT7C_P33_3_IN = {&MODULE_SENT, IfxSent_ChannelId_7, {&MODULE_P33, 3}, Ifx_RxSel_c};
IfxSent_Sent_In IfxSent_SENT8A_P40_8_IN = {&MODULE_SENT, IfxSent_ChannelId_8, {&MODULE_P40, 8}, Ifx_RxSel_a};
IfxSent_Sent_In IfxSent_SENT8B_P00_9_IN = {&MODULE_SENT, IfxSent_ChannelId_8, {&MODULE_P00, 9}, Ifx_RxSel_b};
IfxSent_Sent_In IfxSent_SENT8C_P33_2_IN = {&MODULE_SENT, IfxSent_ChannelId_8, {&MODULE_P33, 2}, Ifx_RxSel_c};
IfxSent_Sent_In IfxSent_SENT9A_P40_9_IN = {&MODULE_SENT, IfxSent_ChannelId_9, {&MODULE_P40, 9}, Ifx_RxSel_a};
IfxSent_Sent_In IfxSent_SENT9B_P00_10_IN = {&MODULE_SENT, IfxSent_ChannelId_9, {&MODULE_P00,10}, Ifx_RxSel_b};
IfxSent_Sent_In IfxSent_SENT9C_P33_1_IN = {&MODULE_SENT, IfxSent_ChannelId_9, {&MODULE_P33, 1}, Ifx_RxSel_c};
IfxSent_Spc_Out IfxSent_SPC0_P00_1_OUT = {&MODULE_SENT, IfxSent_ChannelId_0, {&MODULE_P00, 1}, IfxPort_OutputIdx_alt6};
IfxSent_Spc_Out IfxSent_SPC1_P02_7_OUT = {&MODULE_SENT, IfxSent_ChannelId_1, {&MODULE_P02, 7}, IfxPort_OutputIdx_alt6};
IfxSent_Spc_Out IfxSent_SPC2_P00_3_OUT = {&MODULE_SENT, IfxSent_ChannelId_2, {&MODULE_P00, 3}, IfxPort_OutputIdx_alt6};
IfxSent_Spc_Out IfxSent_SPC3_P00_4_OUT = {&MODULE_SENT, IfxSent_ChannelId_3, {&MODULE_P00, 4}, IfxPort_OutputIdx_alt6};
IfxSent_Spc_Out IfxSent_SPC4_P00_5_OUT = {&MODULE_SENT, IfxSent_ChannelId_4, {&MODULE_P00, 5}, IfxPort_OutputIdx_alt6};
IfxSent_Spc_Out IfxSent_SPC5_P00_6_OUT = {&MODULE_SENT, IfxSent_ChannelId_5, {&MODULE_P00, 6}, IfxPort_OutputIdx_alt6};
IfxSent_Spc_Out IfxSent_SPC6_P00_7_OUT = {&MODULE_SENT, IfxSent_ChannelId_6, {&MODULE_P00, 7}, IfxPort_OutputIdx_alt6};
IfxSent_Spc_Out IfxSent_SPC7_P00_8_OUT = {&MODULE_SENT, IfxSent_ChannelId_7, {&MODULE_P00, 8}, IfxPort_OutputIdx_alt6};
IfxSent_Spc_Out IfxSent_SPC8_P00_9_OUT = {&MODULE_SENT, IfxSent_ChannelId_8, {&MODULE_P00, 9}, IfxPort_OutputIdx_alt6};
IfxSent_Spc_Out IfxSent_SPC9_P00_10_OUT = {&MODULE_SENT, IfxSent_ChannelId_9, {&MODULE_P00,10}, IfxPort_OutputIdx_alt6};


const IfxSent_Sent_In *IfxSent_Sent_In_pinTable[IFXSENT_PINMAP_NUM_MODULES][IFXSENT_PINMAP_NUM_CHANNELS][IFXSENT_PINMAP_SENT_IN_NUM_ITEMS] = {
    {
        {
            &IfxSent_SENT0A_P40_0_IN,
            &IfxSent_SENT0B_P00_1_IN,
            &IfxSent_SENT0C_P02_8_IN,
            NULL_PTR
        },
        {
            &IfxSent_SENT1A_P40_1_IN,
            &IfxSent_SENT1B_P00_2_IN,
            &IfxSent_SENT1C_P02_7_IN,
            NULL_PTR
        },
        {
            &IfxSent_SENT2A_P40_2_IN,
            &IfxSent_SENT2B_P00_3_IN,
            &IfxSent_SENT2C_P02_6_IN,
            NULL_PTR
        },
        {
            &IfxSent_SENT3A_P40_3_IN,
            &IfxSent_SENT3B_P00_4_IN,
            &IfxSent_SENT3C_P02_5_IN,
            NULL_PTR
        },
        {
            &IfxSent_SENT4A_P40_4_IN,
            &IfxSent_SENT4B_P00_5_IN,
            &IfxSent_SENT4C_P33_6_IN,
            NULL_PTR
        },
        {
            &IfxSent_SENT5A_P40_5_IN,
            &IfxSent_SENT5B_P00_6_IN,
            &IfxSent_SENT5C_P33_5_IN,
            NULL_PTR
        },
        {
            &IfxSent_SENT6A_P40_6_IN,
            &IfxSent_SENT6B_P00_7_IN,
            &IfxSent_SENT6C_P33_4_IN,
            NULL_PTR
        },
        {
            &IfxSent_SENT7A_P40_7_IN,
            &IfxSent_SENT7B_P00_8_IN,
            &IfxSent_SENT7C_P33_3_IN,
            NULL_PTR
        },
        {
            &IfxSent_SENT8A_P40_8_IN,
            &IfxSent_SENT8B_P00_9_IN,
            &IfxSent_SENT8C_P33_2_IN,
            NULL_PTR
        },
        {
            &IfxSent_SENT9A_P40_9_IN,
            &IfxSent_SENT9B_P00_10_IN,
            &IfxSent_SENT9C_P33_1_IN,
            NULL_PTR
        },
        {
            &IfxSent_SENT10A_P40_10_IN,
            &IfxSent_SENT10B_P00_11_IN,
            &IfxSent_SENT10C_P32_5_IN,
            &IfxSent_SENT10D_P15_2_IN
        },
        {
            &IfxSent_SENT11A_P40_11_IN,
            &IfxSent_SENT11B_P00_12_IN,
            &IfxSent_SENT11C_P32_6_IN,
            &IfxSent_SENT11D_P15_4_IN
        },
        {
            &IfxSent_SENT12A_P40_12_IN,
            &IfxSent_SENT12B_P02_4_IN,
            &IfxSent_SENT12C_P32_7_IN,
            NULL_PTR
        },
        {
            &IfxSent_SENT13A_P40_13_IN,
            &IfxSent_SENT13B_P02_3_IN,
            &IfxSent_SENT13C_P33_0_IN,
            NULL_PTR
        },
        {
            &IfxSent_SENT14A_P40_14_IN,
            &IfxSent_SENT14B_P02_2_IN,
            &IfxSent_SENT14C_P33_7_IN,
            NULL_PTR
        }
    }
};

const IfxSent_Spc_Out *IfxSent_Spc_Out_pinTable[IFXSENT_PINMAP_NUM_MODULES][IFXSENT_PINMAP_NUM_CHANNELS][IFXSENT_PINMAP_SPC_OUT_NUM_ITEMS] = {
    {
        {
            &IfxSent_SPC0_P00_1_OUT
        },
        {
            &IfxSent_SPC1_P02_7_OUT
        },
        {
            &IfxSent_SPC2_P00_3_OUT
        },
        {
            &IfxSent_SPC3_P00_4_OUT
        },
        {
            &IfxSent_SPC4_P00_5_OUT
        },
        {
            &IfxSent_SPC5_P00_6_OUT
        },
        {
            &IfxSent_SPC6_P00_7_OUT
        },
        {
            &IfxSent_SPC7_P00_8_OUT
        },
        {
            &IfxSent_SPC8_P00_9_OUT
        },
        {
            &IfxSent_SPC9_P00_10_OUT
        },
        {
            NULL_PTR
        },
        {
            NULL_PTR
        },
        {
            NULL_PTR
        },
        {
            NULL_PTR
        },
        {
            NULL_PTR
        }
    }
};
