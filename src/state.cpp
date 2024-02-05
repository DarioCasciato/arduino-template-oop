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
    Logging::log("------------\n");
    Logging::log("Starting RollStorage Tests\n");
    Logging::log("------------\n");

    // Test data to write
    Flash::TestData writeData = {0xAA, 0xBB, 0xCCCC, 0xDDDDEEEE};

    // Attempt to write data to storage
    if(storage.write(&writeData)) {
        Logging::log("Test Write: PASS\n");
    } else {
        Logging::log("Test Write: FAIL\n");
    }

    // Read back the data
    Flash::TestData readData;

    if(storage.readLast(&readData)) {
        // Verify the read data
        if(readData.field1 == writeData.field1 &&
           readData.field2 == writeData.field2 &&
           readData.field3 == writeData.field3 &&
           readData.field4 == writeData.field4) {
            Logging::log("Test Read Last: PASS\n");
        } else {
            Logging::log("Test Read Last: FAIL\n");
        }
    } else {
        Logging::log("Test Read Last: FAIL\n");
    }

    // Test reading from a specific index (the most recent entry, index 0)
    if(storage.read(0, &readData)) {
        // Verify the read data
        if(readData.field1 == writeData.field1 &&
           readData.field2 == writeData.field2 &&
           readData.field3 == writeData.field3 &&
           readData.field4 == writeData.field4) {
            Logging::log("Test Read Index 0: PASS\n");
        } else {
            Logging::log("Test Read Index 0: FAIL\n");
        }
    } else {
        Logging::log("Test Read Index 0: FAIL\n");
    }

    // Clear storage and verify
    if(storage.clear()) {
        // Verify clear by checking number of entries
        if(storage.getNumEntries() == 0) {
            Logging::log("Test Clear Storage: PASS\n");
        } else {
            Logging::log("Test Clear Storage: FAIL\n");
        }
    } else {
        Logging::log("Test Clear Storage: FAIL\n");
    }

    Logging::log("------------\n");
    Logging::log("Tests Completed\n");
    Logging::log("------------\n");
}