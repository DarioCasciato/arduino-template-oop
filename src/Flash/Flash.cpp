// =============================================================================
// Utils | FlashStorage
// =============================================================================

#include "Flash.h"
#include "Logging.h"

#define MAGIC_NUMBER 0x1234

namespace Flash
{
    Layout flashLayout; // Definition of the global instance

    // add flash memory definition here
    FlashStorage storage(&flashLayout.memory1[0], sizeof(flashLayout.memory1), sizeof(DataType), MAGIC_NUMBER);
    IDStorage idStorage(&flashLayout.memory2[0], sizeof(flashLayout.memory2), MAGIC_NUMBER);


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