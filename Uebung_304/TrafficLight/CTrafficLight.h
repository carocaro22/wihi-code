#ifndef CTRAFFICLIGHT_H_
#define CTRAFFICLIGHT_H_

#include "PortPins.h"
// ----------------------------------------------------------------------------
//  D E F I N E S
// ----------------------------------------------------------------------------

// Bit masks for the traffic light
#define LIGHTSTATE_RED_MSK    0x01 // Bit 0: Red
#define LIGHTSTATE_YELLOW_MSK 0x02 // Bit 1: Yellow
#define LIGHTSTATE_GREEN_MSK  0x04 // Bit 2: Green

// ----------------------------------------------------------------------------
//  C L A S S     D E C L R A T I O N
// ----------------------------------------------------------------------------
class CTrafficLight
{
    public:
        // --------------------------------------------------------------
        //  T Y P E  D E F I N I T I O N S
        // --------------------------------------------------------------

        // To specify the different state of the traffic light
        typedef enum
        {
            TL_STATE_OFF = 0x00,
            TL_STATE_RED = LIGHTSTATE_RED_MSK,
            TL_STATE_RED_YELLOW = (LIGHTSTATE_RED_MSK | LIGHTSTATE_YELLOW_MSK),
            TL_STATE_YELLOW = LIGHTSTATE_YELLOW_MSK,
            TL_STATE_GREEN = LIGHTSTATE_GREEN_MSK
        } StateType_t;

        // --------------------------------------------------------------
        //  C o n s t r u c t o r s   D e c l a r a t i o n
        // --------------------------------------------------------------
        CTrafficLight () :
                m_u8Port_Red({&MODULE_P10,5}),
                m_u8Port_Yellow({&MODULE_P02,7}),
                m_u8Port_Green({&MODULE_P02,6})
        {
        }

        CTrafficLight (PortPin ptRed,
        PortPin ptYellow,
        PortPin ptGreen) :
                m_u8Port_Red(ptRed),
                m_u8Port_Yellow(ptYellow),
                m_u8Port_Green(ptGreen)
        {
        }
        // --------------------------------------------------------------
        //  P u b l i c   M e t h o d s   De c l a r a t i o n
        // --------------------------------------------------------------
        // Set the traffic light state
        void SetState (StateType_t state);

    private:
        PortPin m_u8Port_Red;    // Pin number where the red LED is connected
        PortPin m_u8Port_Yellow; // Pin number where the yellow LED is connected
        PortPin m_u8Port_Green;  // Pin number where the green LED is connected
};

#endif /* CTRAFFICCONTROL_H_ */
