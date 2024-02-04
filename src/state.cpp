// =============================================================================
// Template-Project | State
// =============================================================================

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
        uint8_t id = 0x01;
        uint32_t data = 0x12345678;

        Logging::log("test 1: write 0x%x to id 0x%x", data, id);

        Logging::log("Written data: 0x%x", data);
        Flash::idTest.write(id, data);


        uint32_t readData = 0;
        Flash::idTest.read(id, &readData);

        Logging::log("Read data: 0x%x\n\n", readData);

        Logging::log("test 2: write smaller to id 0x%x", id);

        uint16_t data2 = 0x1234;
        Logging::log("Written data: 0x%x", data2);
        Flash::idTest.write(id, data2);

        uint16_t readData2 = 0;
        Flash::idTest.read(id, &readData2);

        Logging::log("Read data: 0x%x\n\n", readData2);

        state = States::st_end;
    }

    void stateEnd()
    {
        delay(1000);
    }
} // namespace State

//------------------------------------------------------------------------------

// Other Functions
