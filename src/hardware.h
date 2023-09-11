// =============================================================================
// Template-Project | Hardware
// =============================================================================

#ifndef _TEMPLATE_PROJECT_HARDWARE_
#define _TEMPLATE_PROJECT_HARDWARE_

#include "EdgeDetection.h"
#include "LED.h"
#include "configurations.h"
#include "gpio.h"


namespace Hardware
{
    // Port definitions
    enum class Port : uint8_t
    {
        button      = (uint8_t) GPIO::Port::D2,   // button is connected to D2
        led         = (uint8_t) GPIO::Port::D4    // led is connected to D4
    };


    // hardware value pre-definitions
    extern uint8_t buttonValue;
    extern EdgeDetection button;

    extern LED led;


    /// @brief Initializes hardware
    void init();

    /// @brief Fetches hardware values
    void updateHardware();
} // namespace Hardware


#endif // _TEMPLATE_PROJECT_HARDWARE_