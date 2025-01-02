/******************************************************************************
 * Definition of the CPedesLight class to abstract the pedestrian light       *
 * CPedesLight.cpp                                                            *
 *                                                                            *
 * Module: "Embedded Systems II" - Uebung 3-05                                *
 *                                                                            *
 * Hochschule Mittweida, INW                                                  *
 * Prof. J. Thomanek                                                          *
 *                                                                            *
 ******************************************************************************/
#include "CPedesLight.h"

// ----------------------------------------------------------------------------
//  D e f i n i t i o n   M e t h o d s
// ----------------------------------------------------------------------------

// Set state of pedestrian light
void CPedesLight::SetState(StateType_t state) {

    // Stop lamp
    if (state & LIGHTSTATE_STOP_MSK) {
        IfxPort_setPinHigh(m_u8Port_Stop.port, m_u8Port_Stop.pin);
    }
    else {
        IfxPort_setPinLow(m_u8Port_Stop.port, m_u8Port_Stop.pin);
    }

    // Walk lamp
    if (state & LIGHTSTATE_GO_MSK) {
        IfxPort_setPinHigh(m_u8Port_Go.port, m_u8Port_Go.pin);
    }
    else {
        IfxPort_setPinLow(m_u8Port_Go.port, m_u8Port_Go.pin);
    }
}
