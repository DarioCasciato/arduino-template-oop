// =============================================================================
// Template-Project | Hardware
// =============================================================================

#ifndef _TEMPLATE_PROJECT_HARDWARE_
#define _TEMPLATE_PROJECT_HARDWARE_

#include "configurations.h"
#include "gpio.h"
#include "LED.h"
#include "EdgeDetection.h"

namespace Hardware
{
    // Port definitions
    enum class Port : uint8_t
    {
        led =       (uint8_t) GPIO::Port::D2,
        button =    (uint8_t) GPIO::Port::D3
    };


    extern LED led;
    extern EdgeDetection button;
    extern uint8_t buttonState;

    /// @brief Initializes hardware
    void init();

    /// @brief Fetches hardware values
    void updateHardware();
} // namespace Hardware


#endif // _TEMPLATE_PROJECT_HARDWARE_