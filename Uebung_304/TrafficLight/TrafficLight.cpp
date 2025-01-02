/******************************************************************************
 * Sketch for Simulation a Trffic Light                                       *
 * TrafficLight.ino                                                           *
 *                                                                            *
 * Module: "Embedded Systems II" - Uebung 3-05                                *
 *                                                                            *
 * Hochschule Mittweida, INW                                                  *
 * Prof. J. Thomanek                                                          *
 *                                                                            *
 ******************************************************************************/

// Include class definition of Traffic Control
#include <TrafficLight/TrafficLight.h>
#include <TrafficLight/CTrafficControl.h>
#include "PortPins.h"

//  Port definitions
// ----------------------------------------------------------------------------

PortPin redLight = {&MODULE_P10,5};
PortPin yellowLight = {&MODULE_P02,7};
PortPin greenLight = {&MODULE_P02,6};
PortPin stopLight = {&MODULE_P10,3};
PortPin goLight = {&MODULE_P10,1};
PortPin button = {&MODULE_P02,0};
PortPin portSwitch = {&MODULE_P15,2};

// ----------------------------------------------------------------------------
//   V A R I A B L E S    D E F I N I T I O N S
// ----------------------------------------------------------------------------

// TrafficControl object
CTrafficControl oTrCntl;

void myISR() {
    oTrCntl.SetRequest();
}

void setup(void)
{
    // Set Port modes
    IfxPort_setPinMode(redLight.port, redLight.pin, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinMode(yellowLight.port, yellowLight.pin, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinMode(greenLight.port, greenLight.pin, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinMode(stopLight.port, stopLight.pin, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinMode(goLight.port, goLight.pin, IfxPort_Mode_outputPushPullGeneral);

    // Configure the switch pin as input with pull-up
    IfxPort_setPinModeInput(portSwitch.port, portSwitch.pin, IfxPort_InputMode_pullUp);

    // Initialize the Traffic control object
    oTrCntl = CTrafficControl(redLight, yellowLight, greenLight,
            stopLight, goLight);
}

//   Cyclic function
// ----------------------------------------------------------------------------
void loop(void)
{
    // First check the operation mode
    // ------------------------------
    if (1) //(digitalRead(PORT_SWITCH) == HIGH)
    {
        // Inform Traffic Control object about Out-Of-Order Mode
        oTrCntl.SetOpMode(0);
    }
    else
    {
        // Inform Traffic Control object about Normal Mode
        oTrCntl.SetOpMode(1);
    }
    // Process State Machine
    oTrCntl.Process();
    waitTime(100);
}
