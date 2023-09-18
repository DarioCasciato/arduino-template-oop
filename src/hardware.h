// =============================================================================
// Template-Project | Hardware
// =============================================================================

#ifndef _TEMPLATE_PROJECT_HARDWARE_
#define _TEMPLATE_PROJECT_HARDWARE_

#include "configurations.h"
#include "gpio.h"
#include "EdgeDetection.h"


namespace Hardware
{
    // Port definitions
    enum class Port : uint8_t
    {
        button = (uint8_t) GPIO::Port::D5
    };

    extern uint8_t buttonState;
    extern EdgeDetection button;


    /// @brief Initializes hardware
    void init();

    /// @brief Fetches hardware values
    void updateHardware();
} // namespace Hardware


#endif // _TEMPLATE_PROJECT_HARDWARE_