// =============================================================================
// Template-Project | State
// =============================================================================

#include "state.h"
#include "hardware.h"
#include "general.h"
#include "configurations.h"
#include "Timer.h"

Timer counter;

//------------------------------------------------------------------------------

namespace State
{
    States state = States::st_idle;

    void stateDriver()
    {
        switch (State::state)
        {
        case State::st_idle: stateIdle(); break;
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
    void stateIdle()
    {
        if(Hardware::button.getEdgePos())
        {
            Serial.println("Button pressed!");
        }
    }

    void stateError()
    {
        Serial.println("ERROR");
    }
} // namespace State

//------------------------------------------------------------------------------

// Other Functions