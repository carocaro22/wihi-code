/********************************************************************************************************************/
/*  CLed.h                                                                                                          */
/*                                                                                                                  */
/*  Modul "Steuergeraete/Software/Vernetzung - Embedded Systems II"                                                 */
/*  Uebung 3-03: C++-Programmierung–Klassendeﬁnition                                                                */
/*                                                                                                                  */
/*  Hochschule Mittweida, INW                                                                                       */
/*  Prof. J. Thomanek                                                                                               */
/*                                                                                                                  */
/********************************************************************************************************************/

#ifndef LED_H_
#define LED_H_

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "Ifx_Types.h"
#include "IfxPort.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Classes------------------------------------------------------*/
/*********************************************************************************************************************/
class CLed
{
    private:

        Ifx_P *port;                                                /* Variable to store the port of the LED        */
        uint8 pinIndex;                                             /* Variable to store the pin number of the LED  */
        bool isLowLevelActive;                                      /* Variable to store the type of the LED        */

    public:

        CLed(Ifx_P *port, uint8 pinIndex, bool isLowLevelActive);   /* Constructor                                  */
        ~CLed();                                                    /* Destructor                                   */

        void TurnOn(void);                                          /* Function to turn on the LED                  */
        void TurnOff(void);                                         /* Function to turn off the LED                 */
        void Toggle(void);                                          /* Function to toggle the LED                   */
        bool IsOn(void);                                            /* Function to check if LED is on               */
};

#endif /* LED_H_ */
