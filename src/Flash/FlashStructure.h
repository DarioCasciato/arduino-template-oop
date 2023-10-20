// =============================================================================
// Utils | FlashStorage
// =============================================================================

#ifndef UTILS_FLASH_STRUCTURE_
#define UTILS_FLASH_STRUCTURE_

#include <stdint.h>

namespace Flash
{
    struct Structure
    {
        uint8_t credentials_m[0x200]; // 512 bytes
    };

    enum class ID : uint8_t
    {
        SSID,
        PASSWORD
    };
} // namespace Flash

#endif // UTILS_FLASH_STRUCTURE_