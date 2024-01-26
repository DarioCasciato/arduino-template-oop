// =============================================================================
// Template-Project | State
// =============================================================================

#include "state.h"
#include "hardware.h"
#include "configurations.h"
#include "Timer.h"
#include "Flash/Flash.h"
#include "Logging.h"

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
            for(;;) { delay(1000); }
    }


    // State implementations (can also be moved to separate files)
    void stateIdle()
    {
        /// RollStorage Test script with uint16_t data type
        uint16_t writeData = 0;

        for (uint16_t i = 0; i < 10; i++)
        {
            writeData = i;
            Flash::testMemory.write(&writeData);
            Logging::log("writeData: %d", writeData);
        }

        uint16_t readData = 0;

        for (uint16_t i = 0; i < 10; i++)
        {
            Flash::testMemory.read(i, &readData);
            Logging::log("readData: %d", readData);
        }

        state = States::st_error;
    }

    void stateError()
    {
        delay(1000);
    }
} // namespace State

//------------------------------------------------------------------------------

// Other Functions
