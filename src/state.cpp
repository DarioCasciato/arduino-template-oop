// =============================================================================
// Template-Project | State
// =============================================================================

#include "state.h"
#include "hardware.h"
#include "configurations.h"
#include "Timer.h"
#include "Flash/Flash.h"
#include "RollStorage.h"
#include "Logging.h"


bool testInitialization(RollStorage& storage);
bool testWriteAndRead(RollStorage& storage);
bool testWrapAroundWrite(RollStorage& storage);
bool testClear(RollStorage& storage);
bool runAllTests(RollStorage& storage);



//------------------------------------------------------------------------------

namespace State
{
    States state = States::st_testing;

    void stateDriver()
    {
        switch (State::state)
        {
        case State::st_testing: stateTesting(); break;
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
        runAllTests(Flash::testMemory);

        state = States::st_end;
    }

    void stateEnd()
    {
        delay(1000);
    }
} // namespace State

//------------------------------------------------------------------------------

// Other Functions


/// Test functions

bool testInitialization(RollStorage& storage)
{
    if (storage.getNumEntries() == 0)
    {
        Logging::log("Initialization Test Passed: numEntries is 0 as expected.\n");
        return true;
    }
    else
    {
        Logging::log("Initialization Test Failed: numEntries is not 0.\n");
        return false;
    }
}

bool testWriteAndRead(RollStorage& storage)
{
    uint8_t testData[4] = {1, 2, 3, 4};
    storage.write(testData);

    uint8_t readData[4] = {};
    bool success = storage.read(0, readData);

    if (success)
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            if (readData[i] != testData[i])
            {
                Logging::log("Write and Read Test Failed: Data read does not match data written.\n");
                return false;
            }
        }
        Logging::log("Write and Read Test Passed: Data read matches data written.\n");
        return true;
    }
    else
    {
        Logging::log("Write and Read Test Failed: Read operation was not successful.\n");
        return false;
    }
}

bool testWrapAroundWrite(RollStorage& storage)
{
    for (uint8_t i = 0; i < storage.getMaxEntries(); i++)
    {
        uint8_t data[4] = {i, i, i, i};
        storage.write(data);
    }

    uint8_t extraData[4] = {99, 99, 99, 99};
    storage.write(extraData);

    uint8_t readData[4] = {};
    storage.readLast(readData);

    for (uint8_t i = 0; i < 4; i++)
    {
        if (readData[i] != extraData[i])
        {
            Logging::log("Wrap-Around Write Test Failed: Last entry is not as expected after wrap-around.\n");
            return false;
        }
    }
    Logging::log("Wrap-Around Write Test Passed: Last entry is as expected after wrap-around.\n");
    return true;
}

bool testClear(RollStorage& storage)
{
    uint8_t testData[4] = {1, 2, 3, 4};
    storage.write(testData);
    storage.clear();

    if (storage.getNumEntries() == 0)
    {
        uint8_t readData[4] = {};
        bool success = storage.read(0, readData);
        if (!success)
        {
            Logging::log("Clear Test Passed: numEntries is 0, and read operation failed as expected.\n");
            return true;
        }
        else
        {
            Logging::log("Clear Test Failed: Read operation succeeded after clear.\n");
            return false;
        }
    }
    else
    {
        Logging::log("Clear Test Failed: numEntries is not 0 after clear.\n");
        return false;
    }
}

bool runAllTests(RollStorage& storage)
{
    Logging::log("Starting RollStorage Tests...\n");

    if(!testInitialization(storage))
    {
        Logging::log("Initialization Test Failed.\n");
        return false;
    }
    storage.clear();

    if(!testWriteAndRead(storage))
    {
        Logging::log("Write and Read Test Failed.\n");
        return false;
    }
    storage.clear();

    if(!testWrapAroundWrite(storage))
    {
        Logging::log("Wrap-Around Write Test Failed.\n");
        return false;
    }
    storage.clear();

    if(!testClear(storage))
    {
        Logging::log("Clear Test Failed.\n");
        return false;
    }


    Logging::log("All RollStorage Tests Passed.\n");
    return true;
}
