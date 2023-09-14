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
    FlashStorage storage(sizeof(Flash::Structure::memory1), sizeof(DataType), MAGIC_NUMBER);


    // Add initializers here
    void initStorage()
    {
        storage.init();
    }

    void clear()
    {
        storage.clear();
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