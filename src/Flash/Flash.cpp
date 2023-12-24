// =============================================================================
// Utils | FlashStorage
// =============================================================================

#include "Flash.h"
#include "Logging.h"

#define MAGIC_NUMBER 0x0809

namespace Flash
{
    // add flash memory definition here
    // example: FlashStorage testMemory(sizeof(Flash::Structure::memory1), sizeof(DataType), MAGICNUMBER);
    IDStorage credentials(sizeof(Flash::Structure::credentials_m), MAGIC_NUMBER);


    // Add initializers here
    void initStorage()
    {
        credentials.init();
    }

    void clear()
    {
        credentials.clear();
    }

    void init()
    {
    #if defined(ESP32) || defined(ESP8266)
        EEPROM.begin(sizeof(Flash::Structure));
    #else
        EEPROM.begin();
    #endif

        initStorage();

        Logging::log("Flash memory initialized\n");
    }

} // namespace Flash