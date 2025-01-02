/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include <CLed.h>

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
CLed::CLed(Ifx_P *port, uint8 pinIndex, bool isLowLevelActive = true)
{
    this->port = port;
    this->pinIndex = pinIndex;
    this->isLowLevelActive = isLowLevelActive;

    /* Switch OFF the LED */
    IfxPort_setPinState(this->port, this->pinIndex, (isLowLevelActive) ? IfxPort_State_high : IfxPort_State_low);

    /* Initialization of the LED */
    IfxPort_setPinModeOutput(this->port, this->pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
}

CLed::~CLed()
{
    /* Switch OFF the LED */
    IfxPort_setPinState(this->port, this->pinIndex, IfxPort_State_low);

    /* De-initialization of the LED */
    IfxPort_setPinMode(this->port, this->pinIndex, IfxPort_Mode_inputNoPullDevice);
}

void CLed::TurnOn(void)
{
    /* Switch ON the LED */
    IfxPort_setPinState(this->port, this->pinIndex, (this->isLowLevelActive) ? IfxPort_State_low : IfxPort_State_high);
}

void CLed::TurnOff(void)
{
    /* Switch OFF the LED */
    IfxPort_setPinState(this->port, this->pinIndex, (this->isLowLevelActive) ? IfxPort_State_high : IfxPort_State_low);
}

void CLed::Toggle(void)
{
    /* Toggle the LED */
    IfxPort_togglePin(this->port, this->pinIndex);
}

bool CLed::IsOn(void)
{
    // Read the current pin state
    bool state = IfxPort_getPinState(this->port, this->pinIndex);

    // Return true if the LED is ON based on the active level
    return (this->isLowLevelActive) ? (state == IfxPort_State_low) : (state == IfxPort_State_high);
}
