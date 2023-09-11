// =============================================================================
// Template-Project | Hardware
// =============================================================================

#include <Arduino.h>
#include "hardware.h"
#include "gpioHandler.h"

namespace Hardware
{
    uint8_t buttonValue = false;
    EdgeDetection button(&buttonValue);

    LED led((uint8_t) Port::led);


    void init()
    {
        // initialize hardware
        led.off();
        pinMode((uint8_t) Port::button, INPUT);
    }

    void updateHardware()
    {
        // get newest button value
        buttonValue = GPIO::getPort(Port::button);
    }
} // namespace Hardware