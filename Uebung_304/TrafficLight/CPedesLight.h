#ifndef CPEDESLIGHT_H_
#define CPEDESLIGHT_H_

#include "PortPins.h"
// ----------------------------------------------------------------------------
//  D E F I N E S
// ----------------------------------------------------------------------------

// Bit masks for the pedestrian light
#define LIGHTSTATE_STOP_MSK   0x01 // Bit 0: Stop - do not walk
#define LIGHTSTATE_GO_MSK     0x02 // Bit 1: Go - can walk

// ----------------------------------------------------------------------------
//  C L A S S     D E C L R A T I O N
// ----------------------------------------------------------------------------
class CPedesLight {
public:
    // --------------------------------------------------------------
    //  T Y P E  D E F I N I T I O N S
    // --------------------------------------------------------------

    // To specify the different state of the traffic light
    typedef enum {
      PL_STATE_OFF  = 0x00,
      PL_STATE_WAIT = LIGHTSTATE_STOP_MSK,
      PL_STATE_WALK = LIGHTSTATE_GO_MSK
    }StateType_t;

    // --------------------------------------------------------------
    //  C o n s t r u c t o r s   D e c l a r a t i o n
    // --------------------------------------------------------------
    CPedesLight() : m_u8Port_Stop({&MODULE_P10,3}),
                    m_u8Port_Go({&MODULE_P10,1}) {}

    CPedesLight(PortPin ptStop,
                PortPin ptGo) : m_u8Port_Stop(ptStop),
                                      m_u8Port_Go(ptGo) {}

    // --------------------------------------------------------------
    //  P u b l i c   M e t h o d s   De c l a r a t i o n
    // --------------------------------------------------------------

    // Set the traffic light state
    void SetState(StateType_t state);

private:
    PortPin m_u8Port_Stop; // Pin number where the red LED is connected
    PortPin m_u8Port_Go;   // Pin number where the green LED is connected
};

#endif /* CPEDESLIGHT_H_ */
