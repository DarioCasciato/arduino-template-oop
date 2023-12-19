// =============================================================================
// Template-Project | State
// =============================================================================

#ifndef _TEMPLATE_PROJECT_STATE_
#define _TEMPLATE_PROJECT_STATE_

#include "hardware.h"

namespace State
{
    enum States : uint8_t
    {
        st_startup,
        st_connecting,
        st_connected
    };

    /// @brief State driver function
    void stateDriver();

    /// @brief Handler for the Startup state
    void stateStartup();

    /// @brief Handler for the Idle state
    void stateConnecting();

    /// @brief Handler for the Error state
    void stateApp();
} // namespace State

#endif // _TEMPLATE_PROJECT_STATE_