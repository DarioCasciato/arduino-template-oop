// =============================================================================
// Utils | FlashStorage
// =============================================================================

#ifndef UTILS_FLASH_
#define UTILS_FLASH_

#include "FlashStorage.h"
#include "IDStorage.h"
#include "FlashStructure.h"
#include <EEPROM.h>

namespace Flash
{
    // add flash memory definition here
    // example: extern FlashStorage testMemory;


    /// @brief initializes the flash memory
    void init();

    /// @brief clears all flash storages
    void clear();

} // namespace Flash

#endif // UTILS_FLASH_