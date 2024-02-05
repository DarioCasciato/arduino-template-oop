// =============================================================================
// Template-Project | State
// =============================================================================

#include "state.h"
#include "hardware.h"
#include "configurations.h"
#include "Timer.h"
#include "Flash.h"
#include "FlashStructure.h"
#include "logging.h"

void testRollStorageOperations(RollStorage& storage);

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
        // Test the roll storage operations
        testRollStorageOperations(Flash::testStorage);

        state = States::st_end;
    }

    void stateEnd()
    {

    }
} // namespace State

//------------------------------------------------------------------------------

// Other Functions


void testRollStorageOperations(RollStorage& storage) {
    Logging::log("------------");
    Logging::log("Starting RollStorage Tests");
    Logging::log("------------");

    storage.clear();

    // Test data to write
    Flash::TestData writeData;

    Logging::log("\nTest 1: Write Data");

    for (uint32_t i = 0; i < 5; i++)
    {
        writeData = {(uint8_t)i, (uint8_t)i, (uint16_t)i*100, i*1000};

        if(!storage.write(&writeData))
        {
            Logging::log("\nFAIL: Write failed");
            return;
        }
    }

    Logging::log("PASS: Write successful");

    Logging::log("\nTest 2: Read Data");

    Flash::TestData readData;

    for (int8_t i = 4; i >= 0; i--)
    {
        if(!storage.read(i, &readData))
        {
            Logging::log("\nFAIL: Read failed");
            return;
        }

        uint8_t expectedValue = 4 - i; // Calculate the expected value based on the index
        if (readData.field1 != expectedValue || readData.field2 != expectedValue || readData.field3 != expectedValue*100 || readData.field4 != expectedValue*1000)
        {
            Logging::log("\nFAIL: Read data mismatch");
        }
        Logging::log("Expected: %d %d %d %d", expectedValue, expectedValue, expectedValue*100, expectedValue*1000);
        Logging::log("Read: %d %d %d %d", readData.field1, readData.field2, readData.field3, readData.field4);
    }

    Logging::log("PASS: Read successful");

    Logging::log("\nTest 3: Read Data (Out of bounds)");

    if(storage.read(5, &readData))
    {
        Logging::log("\nFAIL: Read succeeded");
        return;
    }

    Logging::log("PASS: Read failed");

    Logging::log("\nTest 4: clear");

    if(!storage.clear())
    {
        Logging::log("\nFAIL: Clear failed");
        return;
    }

    Logging::log("PASS: Clear successful");

    Logging::log("\nTest 5: Read Data (After clear)");

    for (uint8_t i = 0; i < 5; i++)
    {
        if(storage.read(i, &readData))
        {
            Logging::log("\nFAIL: Read succeeded");
            return;
        }
    }

    Logging::log("PASS: Read failed");

    Logging::log("\nAll tests passed");
    Logging::log("------------");
}