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

void runTests();
void testWriteReadNewID();
void testOverwriteSameLength();
void testOverwriteLongerValue();
void testOverwriteShorterValue();
void testClearStorage();
void testModifyMiddleValue();
void testOverwriteMiddleIDLongerValue();
void testOverwriteMiddleIDShorterValue();

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
        runTests();
        state = States::st_end;
    }

    void stateEnd()
    {
        delay(1000);
    }
} // namespace State

//------------------------------------------------------------------------------

// Other Functions

void runTests()
{
    // Separator
    Logging::log("\n---------- IDStorage Test Suite ----------");

    // Test 1: Writing and Reading a New ID
    testWriteReadNewID();

    // Test 2: Overwriting Existing ID with Same Length Value
    testOverwriteSameLength();

    // Test 3: Overwriting Existing ID with Longer Value
    testOverwriteLongerValue();

    // Test 4: Overwriting Existing ID with Shorter Value
    testOverwriteShorterValue();

    // Test 5: Clearing the Storage
    testClearStorage();

    // Test 6: Modify Middle Value Without Affecting Adjacent IDs
    testModifyMiddleValue();

    // Test 7: Overwrite Middle ID with Longer Value
    testOverwriteMiddleIDLongerValue();

    // Test 8: Overwrite Middle ID with Shorter Value
    testOverwriteMiddleIDShorterValue();

    // End of tests
    Logging::log("---------- End of Test Suite ----------");
}

void testWriteReadNewID()
{
    Logging::log("Test 1: Writing/Reading a New ID");
    Flash::idTest.clear();
    uint8_t id = 0x01;
    uint32_t data = 305423736;

    if (Flash::idTest.write(id, data))
    {
        Logging::log("PASS: Write new data");
        Logging::log("written data: %lu", data);
    }
    else
    {
        Logging::log("FAIL: Write new data");
        return;
    }

    uint32_t readData = 0;
    if (Flash::idTest.read(id, &readData) && readData == data)
    {
        Logging::log("PASS: Read matches written data");
    }
    else
    {
        Logging::log("FAIL: Read does not match written data");
    }
    Logging::log("read data: %lu", readData);
    Logging::log("----------");
}

void testOverwriteSameLength()
{
    Logging::log("Test 2: Overwriting with Same Length Value");
    Flash::idTest.clear();
    uint8_t id = 0x02;
    uint32_t initialData = 123456789;
    Flash::idTest.write(id, initialData);
    Logging::log("initial data: %lu", initialData);

    uint32_t newData = 987654321; // Same size as initialData
    Flash::idTest.write(id, newData);
    Logging::log("new data: %lu", newData);

    uint32_t readData = 0;
    Flash::idTest.read(id, &readData);
    Logging::log("read data: %lu", readData);
    if (readData == newData)
    {
        Logging::log("PASS: Overwrite with same length data");
    }
    else
    {
        Logging::log("FAIL: Overwrite with same length data");
    }
    Logging::log("----------");
}

void testOverwriteLongerValue()
{
    Logging::log("Test 3: Overwriting with Longer Value");
    Flash::idTest.clear();
    uint8_t id = 0x03;
    uint16_t initialData = 12345; // Shorter data
    Flash::idTest.write(id, initialData);
    Logging::log("initial data: %u", initialData);

    uint32_t newData = 1234567890; // Longer data
    Flash::idTest.write(id, newData);
    Logging::log("new data: %u", newData);

    uint32_t readData = 0;
    Flash::idTest.read(id, &readData);
    Logging::log("read data: %u", readData);
    if (readData == newData)
    {
        Logging::log("PASS: Overwrite with longer data");
    }
    else
    {
        Logging::log("FAIL: Overwrite with longer data");
    }
    Logging::log("----------");
}

void testOverwriteShorterValue()
{
    Logging::log("Test 4: Overwriting with Shorter Value");
    Flash::idTest.clear();
    uint8_t id = 0x04;
    uint32_t initialData = 123456789; // Longer data
    Flash::idTest.write(id, initialData);
    Logging::log("initial data: %u", initialData);

    uint16_t newData = 54321; // Shorter data
    Flash::idTest.write(id, newData);
    Logging::log("new data: %u", newData);

    uint16_t readData = 0;
    Flash::idTest.read(id, &readData);
    Logging::log("read data: %u", readData);
    if (readData == newData)
    {
        Logging::log("PASS: Overwrite with shorter data");
    }
    else
    {
        Logging::log("FAIL: Overwrite with shorter data");
    }
    Logging::log("----------");
}

void testClearStorage()
{
    Logging::log("Test 5: Clearing the Storage");
    Flash::idTest.clear();
    if (Flash::idTest.getNumEntries() == 0)
    {
        Logging::log("PASS: Storage cleared successfully");
    }
    else
    {
        Logging::log("FAIL: Storage not cleared");
    }
    Logging::log("----------");
}

void testModifyMiddleValue()
{
    Logging::log("Test 6: Modify Middle Value Without Affecting Adjacent IDs");
    Flash::idTest.clear();

    // Writing initial values for IDs 1, 2, and 3
    uint8_t id1 = 0x01, id2 = 0x02, id3 = 0x03;
    uint32_t data1 = 111111, data2 = 222222, data3 = 333333;
    Flash::idTest.write(id1, data1);
    Flash::idTest.write(id2, data2);
    Flash::idTest.write(id3, data3);

    // Modifying the value of ID 2
    uint32_t newData2 = 999999;
    Flash::idTest.write(id2, newData2);

    // Reading back all values
    uint32_t readData1 = 0, readData2 = 0, readData3 = 0;
    Flash::idTest.read(id1, &readData1);
    Flash::idTest.read(id2, &readData2);
    Flash::idTest.read(id3, &readData3);

    // Validating the modification and integrity of adjacent data
    bool pass = readData1 == data1 && readData2 == newData2 && readData3 == data3;
    if (pass)
    {
        Logging::log("PASS: Middle value modified correctly without affecting adjacent IDs");
    }
    else
    {
        Logging::log("FAIL: Middle value modification affected adjacent IDs");
    }
    Logging::log("----------");
}

void testOverwriteMiddleIDLongerValue()
{
    Logging::log("Test 7: Overwrite Middle ID with Longer Value");
    Flash::idTest.clear();

    // Setup: Writing three contiguous IDs
    uint8_t id1 = 0x04, id2 = 0x05, id3 = 0x06;
    uint16_t data1 = 4444, data3 = 6666;
    uint32_t data2 = 55555555; // Initially larger data for the middle ID
    Flash::idTest.write(id1, data1);
    Flash::idTest.write(id2, data2);
    Flash::idTest.write(id3, data3);

    // Action: Overwriting the middle ID with even larger data
    uint64_t newData2 = 0xFFFFFFFFFFFFFFFF; // Larger data
    Flash::idTest.write(id2, newData2);

    // Validation
    uint16_t readData1 = 0, readData3 = 0;
    uint64_t readData2 = 0;
    Flash::idTest.read(id1, &readData1);
    Flash::idTest.read(id2, &readData2);
    Flash::idTest.read(id3, &readData3);

    if (readData1 == data1 && readData2 == newData2 && readData3 == data3)
    {
        Logging::log("PASS: Middle ID overwritten with longer data without affecting adjacent IDs");
    }
    else
    {
        Logging::log("FAIL: Overwriting middle ID with longer data affected adjacent IDs");
    }
    Logging::log("----------");
}

void testOverwriteMiddleIDShorterValue()
{
    Logging::log("Test 8: Overwrite Middle ID with Shorter Value");
    Flash::idTest.clear();

    // Setup: Initial data setup with three IDs
    uint8_t id1 = 0x07, id2 = 0x08, id3 = 0x09;
    uint32_t data1 = 77777777, data2 = 88888888, data3 = 99999999;
    Flash::idTest.write(id1, data1);
    Flash::idTest.write(id2, data2);
    Flash::idTest.write(id3, data3);

    // Action: Overwriting the middle ID with shorter data
    uint16_t newData2 = 8888;
    Flash::idTest.write(id2, newData2);

    // Validation
    uint32_t readData1 = 0, readData3 = 0;
    uint16_t readData2 = 0;
    Flash::idTest.read(id1, &readData1);
    Flash::idTest.read(id2, &readData2);
    Flash::idTest.read(id3, &readData3);

    if (readData1 == data1 && readData2 == newData2 && readData3 == data3)
    {
        Logging::log("PASS: Middle ID overwritten with shorter data without affecting adjacent IDs");
    }
    else
    {
        Logging::log("FAIL: Overwriting middle ID with shorter data affected adjacent IDs");
    }
    Logging::log("----------");
}
