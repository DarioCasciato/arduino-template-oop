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
    Logging::log("\n----------- Initialization Test -----------");
    if (storage.getNumEntries() == 0)
    {
        Logging::log("PASSED: numEntries is 0 as expected.");
        return true;
    }
    else
    {
        Logging::log("numEntries: %d", storage.getNumEntries());
        Logging::log("FAILED: numEntries is not 0.");
        return false;
    }
}

bool testWriteAndRead(RollStorage& storage)
{
    Logging::log("\n----------- Write and Read Test -----------");
    uint8_t testData[4] = {1, 2, 3, 4};
    storage.write(testData);

    uint8_t readData[4] = {};
    bool success = storage.read(0, readData);

    if (success)
    {
        for (uint8_t i = 0; i < 10; i++)
        {
            if (readData[i] != testData[i])
            {
                Logging::log("Write Data: %x, Read Data: %x", testData, readData);
                Logging::log("FAILED: Data read does not match data written.");
                return false;
            }
        }
        Logging::log("PASSED: Data read matches data written.");
        return true;
    }
    else
    {
        Logging::log("FAILED: Read operation was not successful.");
        return false;
    }
}

bool testWrapAroundWrite(RollStorage& storage)
{
    Logging::log("\n----------- Wrap-Around Write Test -----------");
    for (uint8_t i = 0; i < storage.getMaxEntries(); i++)
    {
        uint8_t data[4] = {i, i, i, i};
        storage.write(data);
    }

    uint8_t extraData[4] = {99, 99, 99, 99};
    storage.write(extraData);

    uint8_t readData[4] = {};
    storage.read(0, readData);

    for (uint8_t i = 0; i < 10; i++)
    {
        if (readData[i] != extraData[i])
        {
            uint32_t writeData = *(uint32_t*)extraData;
            uint32_t readData = *(uint32_t*)readData;

            Logging::log("Write Data: %x, Read Data: %x", writeData, readData);
            Logging::log("FAILED: Last entry is not as expected after wrap-around.");
            return false;
        }
    }
    Logging::log("PASSED: Last entry is as expected after wrap-around.");
    return true;
}

bool testClear(RollStorage& storage)
{
    Logging::log("\n----------- Clear Test -----------");
    uint8_t testData[4] = {1, 2, 3, 4};
    storage.write(testData);
    storage.clear();

    if (storage.getNumEntries() == 0)
    {
        uint8_t readData[4] = {};
        bool success = storage.read(0, readData);
        if (!success)
        {
            Logging::log("PASSED: numEntries is 0, and read operation failed as expected.");
            return true;
        }
        else
        {
            Logging::log("FAILED: Read operation succeeded after clear.");
            return false;
        }
    }
    else
    {
        Logging::log("numEntries: %d", storage.getNumEntries());
        Logging::log("FAILED: numEntries is not 0 after clear.");
        return false;
    }
}

bool runAllTests(RollStorage& storage)
{
    Logging::log("Starting RollStorage Tests...\n");
    storage.clear();

    if(!testInitialization(storage))
    {
        Logging::log("\n\nFAILED: Initialization Test Failed.\n");
        return false;
    }
    storage.clear();

    if(!testWriteAndRead(storage))
    {
        Logging::log("\n\nFAILED: Write and Read Test Failed.\n");
        return false;
    }
    storage.clear();

    if(!testWrapAroundWrite(storage))
    {
        Logging::log("\n\nFAILED: Wrap-Around Write Test Failed.\n");
        return false;
    }
    storage.clear();

    if(!testClear(storage))
    {
        Logging::log("\n\nFAILED: Clear Test Failed.\n");
        return false;
    }


    Logging::log("\n\nAll RollStorage Tests Passed!!!");
    return true;
}
