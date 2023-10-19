// =============================================================================
// Template-Project | State
// =============================================================================

#include "state.h"
#include "hardware.h"
#include "configurations.h"
#include "Timer.h"
#include "Logging.h"
#include "Flash/Flash.h"

#define ID_DATA1 1
#define ID_DATA2 2
#define ID_DATA3 3



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
            for(;;) {}
    }

    // State implementations
    void stateIdle()
    {
        // First set of data
        uint8_t data1 = 250;
        uint64_t data2 = 0x1122334455667788;
        String data3 = "Test Test123";

        Logging::log("Writing Data Set 1:\n");
        Logging::log("uint8_t: %d\n", data1);
        Logging::log("uint64_t: %llu\n", data2);
        Logging::log("String: %s\n", data3.c_str());

        Flash::testMemory.write(ID_DATA1, &data1, sizeof(data1));
        Flash::testMemory.write(ID_DATA2, &data2, sizeof(data2));
        Flash::testMemory.write(ID_DATA3, data3);

        // Reading back
        uint8_t readData1;
        uint64_t readData2;
        char readData3[50]; // Assuming string won't exceed this size

        Flash::testMemory.read(ID_DATA1, &readData1);
        Flash::testMemory.read(ID_DATA2, &readData2);
        Flash::testMemory.read(ID_DATA3, readData3);

        Logging::log("Reading Data Set 1:\n");
        Logging::log("uint8_t: %d\n", readData1);
        Logging::log("uint64_t: %llu\n", readData2);
        Logging::log("String: %s\n", readData3);

        if (data1 == readData1) {
            Logging::log("Data1 matches after reading back.\n");
        } else {
            Logging::log("Data1 does not match after reading back.\n");
        }

        if (data2 == readData2) {
            Logging::log("Data2 matches after reading back.\n");
        } else {
            Logging::log("Data2 does not match after reading back.\n");
        }

        if (data3 == readData3) {
            Logging::log("Data3 matches after reading back.\n");
        } else {
            Logging::log("Data3 does not match after reading back.\n");
        }

        // Second set of data
        uint8_t data4 = 45;
        uint64_t data5 = 0x8877665544332211;
        String data6 = "fritig again";

        Logging::log("Writing Data Set 2:\n");
        Logging::log("uint8_t: %d\n", data4);
        Logging::log("uint64_t: %llu\n", data5);
        Logging::log("String: %s\n", data6.c_str());

        Flash::testMemory.write(ID_DATA1, &data4, sizeof(data4));
        Flash::testMemory.write(ID_DATA2, &data5, sizeof(data5));
        Flash::testMemory.write(ID_DATA3, data6);

        // Reading back
        uint8_t readData4;
        uint64_t readData5;
        char readData6[50]; // Assuming string won't exceed this size

        Flash::testMemory.read(ID_DATA1, &readData4);
        Flash::testMemory.read(ID_DATA2, &readData5);
        Flash::testMemory.read(ID_DATA3, readData6);

        Logging::log("Reading Data Set 2:\n");
        Logging::log("uint8_t: %d\n", readData4);
        Logging::log("uint64_t: %llu\n", readData5);
        Logging::log("String: %s\n", readData6);

        if (data4 == readData4) {
            Logging::log("Data4 matches after reading back.\n");
        } else {
            Logging::log("Data4 does not match after reading back.\n");
        }

        if (data5 == readData5) {
            Logging::log("Data5 matches after reading back.\n");
        } else {
            Logging::log("Data5 does not match after reading back.\n");
        }

        if (data6 == readData6) {
            Logging::log("Data6 matches after reading back.\n");
        } else {
            Logging::log("Data6 does not match after reading back.\n");
        }



        state = States::st_end;
    }

    void stateEnd()
    {
        delay(5000);
    }
} // namespace State

//------------------------------------------------------------------------------

// Other Functions