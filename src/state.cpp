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
        case State::st_end: stateEnd(); break;

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

        for (uint16_t i = 0; i < 15; i++)
        {
            writeData = i * 15;
            if(!Flash::testMemory.write(&writeData))
            {
                Logging::log("Error writing data");
            }
            else
            {
                Logging::log("writeData: %d", writeData);
            }
        }
        Logging::log("\n");

        uint16_t readData = 0;

        for (uint16_t i = 0; i < 15; i++)
        {
            if(!Flash::testMemory.read(i, &readData))
            {
                Logging::log("Error reading data");
            }
            else
            {
                Logging::log("readData: index: %d, data: %d", i, readData);
            }
        }

        state = States::st_end;
    }

    void stateEnd()
    {
        delay(1000);
    }
} // namespace State

//------------------------------------------------------------------------------

// Other Functions
