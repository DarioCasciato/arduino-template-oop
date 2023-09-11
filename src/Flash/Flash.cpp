// =============================================================================
// Utils | FlashStorage
// =============================================================================

#include "Flash.h"

#define MAGIC_NUMBER 0x1234

namespace Flash
{
    // add flash memory definition here
    // example: FlashStorage testMemory(sizeof(Flash::Structure::memory1), sizeof(DataType), MAGICNUMBER);
    FlashStorage storage(sizeof(Flash::Structure::memory1), sizeof(int), MAGIC_NUMBER);

    void init()
    {
        #ifdef ESP8266
        EEPROM.begin(sizeof(Flash::Structure));
        #else
        EEPROM.begin();
        #endif
    }

} // namespace Flash