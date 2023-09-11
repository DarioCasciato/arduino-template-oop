// =============================================================================
// Utils | FlashStorage
// =============================================================================

#include "FlashStorage.h"
#include "FlashStructure.h"
#include <EEPROM.h>

#define MAGIC_NUMBER 0x1234

void Flash::init()
{
    // add flash memory definition here
    // example: FlashStorage testMemory(sizeof(Flash::Structure::memory1), sizeof(DataType), MAGICNUMBER);



    #ifdef ESP8266
    EEPROM.begin(sizeof(Flash::Structure));
    #else
    EEPROM.begin();
    #endif
}