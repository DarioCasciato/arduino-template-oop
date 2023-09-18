// =============================================================================
// Template-Project | Hardware
// =============================================================================

#include <Arduino.h>
#include "hardware.h"
#include "gpioHandler.h"

namespace Hardware
{
    uint8_t buttonState = 0;
    EdgeDetection button(&buttonState);



    void init()
    {
        //pinMode((uint8_t) Port::button, INPUT);
    }

    void updateHardware()
    {
        buttonState = GPIO::getPort(Port::button);
    }
} // namespace Hardware