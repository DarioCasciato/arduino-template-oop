// =============================================================================
// Template-Project | State
// =============================================================================

#include <inttypes.h>
#include "state.h"
#include "hardware.h"
#include "configurations.h"
#include "Timer.h"
#include "Flash.h"
#include "Logging.h"

//------------------------------------------------------------------------------

namespace State
{
    States state = States::st_idle;

    void stateDriver()
    {
        switch (State::state)
        {
        case State::st_idle: stateTesting(); break;
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
    void stateTesting()
    {
        Flash::idTest.clear();
        uint8_t id = 0x01;
        uint32_t data = 305423736;

        Logging::log("test 1: write %" PRIu32 "to id 0x%d", data, id);

        Flash::idTest.write(id, data);
        Logging::log("Written data: %" PRIu32, data);


        uint32_t readData = 0;
        Flash::idTest.read(id, &readData);

        Logging::log("Read data: %" PRIu32 "\n\n", readData);

        Logging::log("test 2: write smaller to id 0x%x", id);

        uint16_t data2 = 34438;
        Logging::log("Written data: %u", data2);
        Flash::idTest.write(id, data2);

        uint16_t readData2 = 0;
        Flash::idTest.read(id, &readData2);

        Logging::log("Read data: %u", readData2);

        state = States::st_end;
    }

    void stateEnd()
    {
        delay(1000);
    }
} // namespace State

//------------------------------------------------------------------------------

// Other Functions
