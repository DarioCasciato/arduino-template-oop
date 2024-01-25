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
        /// RollStorage Test script
        Flash::DataType data = {0x80, 0x7777, 0x12345678};
        // Flash::DataType dataWrite2 = {0x81, 0x8888, 0x87654321};

        Flash::testMemory.write(&data);
        Logging::log("written data: %x, %x, %x\n", data.data1, data.data2, data.data3);

        Flash::DataType data2 = { 0 };

        Flash::testMemory.readLast(&data2);

        Logging::log("read data: %x, %x, %x\n", data2.data1, data2.data2, data2.data3);

        state = States::st_error;
    }

    void stateError()
    {
        delay(1000);
    }
} // namespace State

//------------------------------------------------------------------------------

// Other Functions
