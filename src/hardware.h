// =============================================================================
// Template-Project | Hardware
// =============================================================================

#ifndef _TEMPLATE_PROJECT_HARDWARE_
#define _TEMPLATE_PROJECT_HARDWARE_

#include "configurations.h"
#include "gpio.h"
#include <BluetoothSerial.h>


namespace Hardware
{
    // Port definitions
    enum class Port : uint8_t
    {

    };

    extern BluetoothSerial SerialBT;

    /// @brief Initializes hardware
    void init();

    /// @brief Fetches hardware values
    void updateHardware();
} // namespace Hardware


#endif // _TEMPLATE_PROJECT_HARDWARE_