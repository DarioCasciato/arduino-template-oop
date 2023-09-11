// =============================================================================
// Utils | FlashStorage
// =============================================================================

#include "FlashStorage.h"
#include "FlashStructure.h"
#include <EEPROM.h>

void Flash::init()
{
    // add flash memory definition here
    // example: FlashStorage testMemory(sizeof(Flash::Structure::memory1), sizeof(DataType));



    #ifdef ESP8266
    EEPROM.begin(sizeof(Flash::Structure));
    #else
    EEPROM.begin();
    #endif
}