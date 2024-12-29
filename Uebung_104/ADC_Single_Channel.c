/********************************************************************************************************************/
/*  ADC_Single_Channel.c                                                                                            */
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
#include "ADC_Single_Channel.h"
#include "IfxEvadc_Adc.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define GROUPID_0       IfxEvadc_GroupId_0                      /* EVADC group                                       */
#define AN5_CHID        5                                       /* Channel ID for pin AN5                            */

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
 /* EVADC handle */
IfxEvadc_Adc         g_evadc;                                    /* EVADC module handle variable                     */
IfxEvadc_Adc_Group   g_adcGroup;                                 /* EVADC group handle variable                      */
IfxEvadc_Adc_Channel g_adcChannel;                               /* EVADC channel handle variable                    */

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void initEVADCModule(void);                                   /* Function to initialize the EVADC module             */
void initEVADCGroup(void);                                    /* Function to initialize the EVADC group              */
void initEVADCChannels(void);                                 /* Function to initialize the EVADC Channels           */
void fillAndStartQueue(void);                                 /* Function to add the channel to a queue and start it */

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
/* Function to initialize the EVADC with default parameters */
void initEVADC(void)
{
    initEVADCModule();      /* Initialize the EVADC module  */
    initEVADCGroup();       /* Initialize the EVADC group   */
    initEVADCChannels();    /* Initialize the channel       */
    fillAndStartQueue();    /* Fill the queue and start it  */
}

/* Function to initialize the EVADC module with default parameters */
void initEVADCModule(void)
{
    /* Create configuration */
    IfxEvadc_Adc_Config adcConfig;
    IfxEvadc_Adc_initModuleConfig(&adcConfig, &MODULE_EVADC);

    /* Initialize module */
    IfxEvadc_Adc_initModule(&g_evadc, &adcConfig);
}

/* Function to initialize the EVADC group with default parameters */
void initEVADCGroup(void)
{
    /* Create and initialize group configuration with default values */
    IfxEvadc_Adc_GroupConfig adcGroupConfig;
    IfxEvadc_Adc_initGroupConfig(&adcGroupConfig, &g_evadc);

    /* Setting user configuration using group 0 */
    adcGroupConfig.groupId = GROUPID_0;
    adcGroupConfig.master = GROUPID_0;

    /* Enable queued source */
    adcGroupConfig.arbiter.requestSlotQueue0Enabled = TRUE;

    /* Enable all gates in "always" mode (no edge detection) */
    adcGroupConfig.queueRequest[0].triggerConfig.gatingMode = IfxEvadc_GatingMode_always;

    /* Initialize the group */
    IfxEvadc_Adc_initGroup(&g_adcGroup, &adcGroupConfig);
}

/* Function to initialize the EVADC channel */
void initEVADCChannels(void)
{
    /* Create channel configuration */
    IfxEvadc_Adc_ChannelConfig adcChannelConfig;

    /* Initialize the configuration with default values */
    IfxEvadc_Adc_initChannelConfig(&adcChannelConfig, &g_adcGroup);

    /* Select the channel ID and the respective result register */
    adcChannelConfig.channelId = (IfxEvadc_ChannelId)(AN5_CHID);
    adcChannelConfig.resultRegister = (IfxEvadc_ChannelResult)(AN5_CHID);

    /* Initialize the channel */
    IfxEvadc_Adc_initChannel(&g_adcChannel, &adcChannelConfig);
}

/* Function to add the channel to a queue */
void fillAndStartQueue(void)
{
    /* Add channel to queue with refill option enabled */
    IfxEvadc_Adc_addToQueue(&g_adcChannel, IfxEvadc_RequestSource_queue0, IFXEVADC_QUEUE_REFILL);

    /* Start the queue */
    IfxEvadc_Adc_startQueue(&g_adcGroup, IfxEvadc_RequestSource_queue0);
}

/* Function to read the EVADC used channel */
unsigned int readEVADC(void)
{
    Ifx_EVADC_G_RES result;

    /* Wait for valid result */
    do
    {
        result = IfxEvadc_Adc_getResult(&g_adcChannel); /* Read the result of the channel */
    } while(!result.B.VF);

    return result.B.RESULT;
}
