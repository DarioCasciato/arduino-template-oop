// =============================================================================
// Template-Project | Hardware
// =============================================================================

#ifndef _TEMPLATE_PROJECT_HARDWARE_
#define _TEMPLATE_PROJECT_HARDWARE_

#include <Arduino.h>
#include "configurations.h"
#include "gpio.h"

// Include all hardware drivers here as absolute paths
// Example: #include "../utils/LED/LED.h"


namespace Hardware
{
    // Port definitions
    enum class Port : uint8_t
    {
        // Define your ports here
        // Example: LED = (uint8_t)GPIO::Port::D0,
    };


    // Create extern instances of all hardware drivers here
    // Example: extern LED statusLed;

    /// @brief Initializes hardware
    ///
    void init();

    /// @brief Fetches hardware values
    ///
    void updateHardware();
} // namespace Hardware


#endif // _TEMPLATE_PROJECT_HARDWARE_
