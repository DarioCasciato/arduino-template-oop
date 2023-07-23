// =============================================================================
// Template-Project | Hardware
// =============================================================================

#include <Arduino.h>
#include "hardware.h"
#include "general.h"

namespace Hardware
{


    bool getPort(Port port)
    {
        return digitalRead((uint8_t)port);
    }
} // namespace Hardware