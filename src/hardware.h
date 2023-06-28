// =============================================================================
// Template-Project | Hardware
// =============================================================================

#ifndef _TEMPLATE_PROJECT_HARDWARE_
#define _TEMPLATE_PROJECT_HARDWARE_

#include "EdgeDetection.h"
#include "configurations.h"

namespace Hardware
{
    // Example entries
    enum class Port : uint8_t
    {
        button = PIN_BUTTON
    };

    extern EdgeDetection button;

    bool getPort(Port port);
} // namespace Hardware


#endif // _TEMPLATE_PROJECT_HARDWARE_