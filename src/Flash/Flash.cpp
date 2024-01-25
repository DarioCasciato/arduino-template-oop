// =============================================================================
// Utils | FlashStorage
// =============================================================================

#include "Flash.h"
#include "Logging.h"

namespace Flash
{
    Layout flashLayout; // Definition of the global instance


    RollStorage testMemory(&flashLayout.memory1[0], sizeof(flashLayout.memory1), sizeof(struct DataType));

    namespace
    {

    void initStorage()
    {
        testMemory.init();
    }

    }

    void clear()
    {
        testMemory.clear();
    }


    void init()
    {
    #ifdef ESP8266
        EEPROM.begin(sizeof(Flash::Layout));
    #else
        EEPROM.begin();
    #endif

        initStorage();

        Logging::log("Flash memory initialized\n");
    }

} // namespace Flash
