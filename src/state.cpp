// =============================================================================
// Template-Project | State
// =============================================================================

#include "state.h"
#include "hardware.h"
#include "configurations.h"
#include "Timer.h"
#include "APIHandler/APIHandler.h"
#include "Logging.h"

//------------------------------------------------------------------------------

namespace State
{
    States state = States::st_app;

    void stateDriver()
    {
        switch (State::state)
        {
        case State::st_app: stateApp(); break;
        case State::st_error: stateError(); break;

        default:    // catch invalid state (implement safety backup)
        goto exception;
            break;
        }

        return;

        exception:
            for(;;) {}
    }

    // State implementations
    void stateApp()
    {
        if(Hardware::button.getEdgePos())
        {
            Logging::log("\nButton pressed");

            if(APIHandler::getSwitchState())
            {
                Logging::log("Switching off");
                APIHandler::switchOff();
            }
            else
            {
                Logging::log("Switching on");
                APIHandler::switchOn();
            }
        }

        delay(10);
    }

    void stateError()
    {

    }
} // namespace State

//------------------------------------------------------------------------------

// Other Functions