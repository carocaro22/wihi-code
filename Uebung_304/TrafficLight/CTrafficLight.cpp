/******************************************************************************
 * Definition of the CTrafficLight class to abstract the traffic light        *
 * CTrafficLight.cpp                                                          *
 *                                                                            *
 * Module: "Embedded Systems II" - Uebung 3-05                                *
 *                                                                            *
 * Hochschule Mittweida, INW                                                  *
 * Prof. J. Thomanek                                                          *
 *                                                                            *
 ******************************************************************************/

#include "CTrafficLight.h"
#include "IfxPort.h"

// ----------------------------------------------------------------------------
//  D e f i n i t i o n   M e t h o d s
// ----------------------------------------------------------------------------

// Set state of traffic light
void CTrafficLight::SetState(StateType_t state) {
  // Red lamp
  //---------
  if (state & LIGHTSTATE_RED_MSK) {
      IfxPort_setPinHigh(m_u8Port_Red.port, m_u8Port_Red.pin);
  }
  else {
      IfxPort_setPinLow(m_u8Port_Red.port, m_u8Port_Red.pin);
  }
  // Yellow lamp
  //------------
  if (state & LIGHTSTATE_YELLOW_MSK) {
      IfxPort_setPinHigh(m_u8Port_Yellow.port, m_u8Port_Yellow.pin);
  }
  else {
      IfxPort_setPinLow(m_u8Port_Yellow.port, m_u8Port_Yellow.pin);
  }
  // Green lamp
  //-----------
  if (state & LIGHTSTATE_GREEN_MSK) {
      IfxPort_setPinHigh(m_u8Port_Green.port, m_u8Port_Green.pin);
  }
  else {
      IfxPort_setPinLow(m_u8Port_Green.port, m_u8Port_Green.pin);
  }
}
