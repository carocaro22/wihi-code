#ifndef CTRAFFICCONTROL_H_
#define CTRAFFICCONTROL_H_

#include "CTrafficLight.h"
#include "CPedesLight.h"
#include "PortPins.h"

// ----------------------------------------------------------------------------
//  C L A S S     D E C L R A T I O N
// ----------------------------------------------------------------------------
class CTrafficControl
{
    public:
        // --------------------------------------------------------------
        //  C o n s t r u c t o r s   D e c l a r a t i o n
        // --------------------------------------------------------------
        CTrafficControl ();
        CTrafficControl (PortPin ptRed, PortPin ptYellow, PortPin ptGreen, PortPin ptStop,
                PortPin ptGo);

        // --------------------------------------------------------------
        //  P u b l i c   M e t h o d s   De c l a r a t i o n
        // --------------------------------------------------------------
        // To process the state machine - must be called cyclically
        // by the application
        void Process ();

        // Set functions
        void SetRequest ()
        {
            m_bSigRequest = true;
        }

        void SetOpMode (unsigned char op)
        {
            m_u8Operation = op;
        }

    private:
        // --------------------------------------------------------------
        //  P r i v a t e   A t t r i b u t e s
        // --------------------------------------------------------------
        unsigned char m_u8State;     // State Machine variable
        unsigned char m_u8Timer;     // Counter variable in 100 ms ticks
        unsigned char m_u8Operation; // Operation Mode: Out-of-order or Normal operation
        bool m_bSigRequest; // Button pressed flag
        CPedesLight m_oPdLght;     // Pedestrian light object
        CTrafficLight m_oTrLght;     // Traffic light object
};

#endif /* CTRAFFICCONTROL_H_ */
