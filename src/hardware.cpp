// =============================================================================
// Template-Project | Hardware
// =============================================================================

#include <Arduino.h>
#include "hardware.h"
#include "gpioHandler.h"

namespace Hardware
{
    LED led((uint8_t) Port::led, activeLevel::HIGH_ACTIVE);

    uint8_t buttonState;
    EdgeDetection button(&buttonState);


    void init()
    {
        pinMode((uint8_t) Port::led, INPUT);
    }

    void updateHardware()
    {
        buttonState = GPIO::getPort(Port::button);
    }
} // namespace Hardware