/******************************************************************************
 * Definition of the TrafficControl class to define the state machine         *
 * CTrafficControl.cpp                                                        *
 *                                                                            *
 * Module: "Embedded Systems II" - Uebung 3-05                                *
 *                                                                            *
 * Hochschule Mittweida, INW                                                  *
 * Prof. J. Thomanek                                                          *
 *                                                                            *
 ******************************************************************************/

#include "CTrafficControl.h"
#include "PortPins.h"

// ----------------------------------------------------------------------------
//  L o c a l   D e f i n e s (C o n s t a n t s)
// ----------------------------------------------------------------------------

//  State machine states
// ----------------------------------------------------------------------------

// masks
#define STATE_LEVEL1_MSK 0x0F   // level 1: On/Off-Modus
#define STATE_LEVEL2_MSK 0xFF   // level 2: different lights

// level 1
#define STATE_OP_OFF 0x00       // No-operation (yellow flashing)
#define STATE_OP_ON  0x01       // Normal operation

// level 2
#define STATE_YELLOW_OFF  (STATE_OP_OFF | 0x10)  // Yellow-Flashing Off
#define STATE_YELLOW_ON   (STATE_OP_OFF | 0x20)  // Yellow-Flashing On
#define STATE_TRAFFIC_STOP_A  (STATE_OP_ON | 0x10)
#define STATE_TRAFFIC_STOP_B  (STATE_OP_ON | 0x20)
#define STATE_READY_TO_DRIVE  (STATE_OP_ON | 0x30)
#define STATE_TRAFFIC_GO_MIN  (STATE_OP_ON | 0x40)
#define STATE_TRAFFIC_GO_MAX  (STATE_OP_ON | 0x50)
#define STATE_READY_TO_STOP   (STATE_OP_ON | 0x60)
#define STATE_PEDESTRIAN_WALK (STATE_OP_ON | 0x70)

//  Times in 100 ms
// ----------------------------------------------------------------------------
#define TIME_OP_OFF_YELLOW       5  // 0.5s - time of flashing yellow

// (out of order)
#define TIME_OP_ON_RDY_TO_DRV   10  //   1s - time of red/yellow
#define TIME_OP_ON_RDY_TO_STP   10  //   1s - time of yellow
#define TIME_OP_ON_GO_MIN       40  //  4s - minimum time of green
#define TIME_OP_ON_PEDEST_SAFE  15  // 1.5s - safety time between red and walk
#define TIME_OP_ON_PEDEST_WALK  40  //  4s   - time of pedestrian walking

// ----------------------------------------------------------------------------
//  D e f i n i t i o n   C o n s t r u c t o r s
// ----------------------------------------------------------------------------
CTrafficControl::CTrafficControl () :
        m_u8State(STATE_YELLOW_OFF),
        m_u8Timer(TIME_OP_OFF_YELLOW),
        m_u8Operation(0),
        m_bSigRequest(false)
{
}

CTrafficControl::CTrafficControl (PortPin ptRed,
        PortPin ptYellow,
        PortPin ptGreen,
        PortPin ptStop,
        PortPin ptGo) :
        m_u8State(STATE_YELLOW_OFF),
        m_u8Timer(TIME_OP_OFF_YELLOW),
        m_u8Operation(0),
        m_bSigRequest(false)
{
    m_oPdLght = CPedesLight(ptStop, ptGo);
    m_oTrLght = CTrafficLight(ptRed, ptYellow, ptGreen);
}

// ----------------------------------------------------------------------------
//  D e f i n i t i o n   M e t h o d s
// ----------------------------------------------------------------------------

void CTrafficControl::Process ()
{
    // Check level 1
    // -------------

    // if Operation Mode is ON
    if ((m_u8State & STATE_LEVEL1_MSK) == STATE_OP_ON)
    {
        // Check level 2
        switch (m_u8State & STATE_LEVEL2_MSK)
        {
            case STATE_TRAFFIC_STOP_A :
                if ((m_u8Timer == 0) && (m_u8Operation == 0))
                {
                    m_u8State = STATE_OP_OFF;
                }
                else if (m_u8Timer == 0)
                {
                    m_oPdLght.SetState(CPedesLight::PL_STATE_WALK);
                    m_u8Timer = TIME_OP_ON_PEDEST_WALK;
                    m_u8State = STATE_PEDESTRIAN_WALK;
                }
                else
                {
                    m_u8Timer--;
                }
                break;
            case STATE_TRAFFIC_STOP_B :
                if (m_u8Timer == 0)
                {
                    m_oTrLght.SetState(CTrafficLight::TL_STATE_RED_YELLOW);
                    m_u8Timer = TIME_OP_ON_RDY_TO_DRV;
                    m_u8State = STATE_READY_TO_DRIVE;
                }
                else
                {
                    m_u8Timer--;
                }
                break;
            case STATE_READY_TO_DRIVE :
                if (m_u8Timer == 0)
                {
                    m_oTrLght.SetState(CTrafficLight::TL_STATE_GREEN);
                    m_u8Timer = TIME_OP_ON_GO_MIN;
                    m_u8State = STATE_TRAFFIC_GO_MIN;
                }
                else
                {
                    m_u8Timer--;
                }
                break;
            case STATE_TRAFFIC_GO_MIN :
                if (m_u8Timer == 0)
                {
                    m_u8State = STATE_TRAFFIC_GO_MAX;
                }
                else
                {
                    m_u8Timer--;
                }
                break;
            case STATE_TRAFFIC_GO_MAX :
                if ((m_bSigRequest == true) || (m_u8Operation == 0))
                {
                    m_oTrLght.SetState(CTrafficLight::TL_STATE_YELLOW);
                    m_u8Timer = TIME_OP_ON_RDY_TO_STP;
                    m_u8State = STATE_READY_TO_STOP;
                }
                break;
            case STATE_READY_TO_STOP :
                if (m_u8Timer == 0)
                {
                    m_oTrLght.SetState(CTrafficLight::TL_STATE_RED);
                    m_u8Timer = TIME_OP_ON_PEDEST_SAFE;
                    m_u8State = STATE_TRAFFIC_STOP_A;
                }
                else
                {
                    m_u8Timer--;
                }
                break;
            case STATE_PEDESTRIAN_WALK :
                if (m_u8Timer == 0)
                {
                    m_oPdLght.SetState(CPedesLight::PL_STATE_WAIT);
                    m_bSigRequest = false;
                    m_u8Timer = TIME_OP_ON_PEDEST_SAFE;
                    m_u8State = STATE_TRAFFIC_STOP_B;
                }
                else
                {
                    m_u8Timer--;
                }
                break;
            default :
                break;
        }
    }
    // if Operation Mode is Out-of-order
    else
    {
        // System is switched on
        if (m_u8Operation == 1)
        {
            m_u8State = STATE_OP_ON;
        }
        // check level 2
        else if ((m_u8State & STATE_LEVEL2_MSK) == STATE_YELLOW_ON)
        {
            if (m_u8Timer == 0)
            {
                m_oTrLght.SetState(CTrafficLight::TL_STATE_OFF);
                m_u8Timer = TIME_OP_OFF_YELLOW;
                m_u8State = STATE_YELLOW_OFF;
            }
            else
            {
                m_u8Timer--;
            }
        }
        else
        {
            if (m_u8Timer == 0)
            {
                m_oTrLght.SetState(CTrafficLight::TL_STATE_YELLOW);
                m_u8Timer = TIME_OP_OFF_YELLOW;
                m_u8State = STATE_YELLOW_ON;
            }
            else
            {
                m_u8Timer--;
            }
        }
    }
    // Initial transition - Set internal state
    // Normal operation:
    if (m_u8State == STATE_OP_ON)
    {
        m_oTrLght.SetState(CTrafficLight::TL_STATE_RED);
        m_oPdLght.SetState(CPedesLight::PL_STATE_WAIT);
        m_u8Timer = TIME_OP_ON_PEDEST_SAFE;
        m_u8State = STATE_TRAFFIC_STOP_B;
    }
    // No operation - Blinking Yellow Light
    else if (m_u8State == STATE_OP_OFF)
    {
        m_oTrLght.SetState(CTrafficLight::TL_STATE_OFF);
        m_oPdLght.SetState(CPedesLight::PL_STATE_OFF);
        m_u8Timer = TIME_OP_OFF_YELLOW;
        m_u8State = STATE_YELLOW_OFF;
    }
}
