// =============================================================================
// Utils | FlashStorage
// =============================================================================

#include "Flash.h"
#include "Logging.h"

#define MAGIC_NUMBER 0x1234

namespace Flash
{
    // add flash memory definition here
    // example: FlashStorage testMemory(sizeof(Flash::Structure::memory1), sizeof(DataType), MAGICNUMBER);


    // Add initializers here
    void initStorage()
    {
        // example: storage.init();

    }

    void clear()
    {
        // example: storage.clear();

    }

    void init()
    {
    #ifdef ESP8266
        EEPROM.begin(sizeof(Flash::Structure));
    #else
        EEPROM.begin();
    #endif

        initStorage();

        Logging::log("Flash memory initialized\n");
    }

} // namespace Flash