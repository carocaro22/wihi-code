#ifndef PORTPINS_H_
#define PORTPINS_H_

#include "IfxPort_PinMap.h"

struct PortPin {
    Ifx_P *port; // Pointer to represent the port (e.g., &MODULE_P00)
    unsigned char pin; // Pin number (e.g., 5)
};

#endif /* PORTPINS_H_ */
