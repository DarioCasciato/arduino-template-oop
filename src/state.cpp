// =============================================================================
// Template-Project | State
// =============================================================================

#include "state.h"
#include "hardware.h"
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
        // Turn on the LED
        Hardware::led.on();

        // If the button is pressed, go to the error state
        if(Hardware::button.getEdgePos())
        {
            state = States::st_error;
        }
    }

    void stateError()
    {
        // set the led to off
        Hardware::led.off();

        // if the button is pressed
        if(Hardware::button.getEdgePos())
        {
            // go to the idle state
            state = States::st_idle;
        }
    }
} // namespace State

//------------------------------------------------------------------------------

// Other Functions