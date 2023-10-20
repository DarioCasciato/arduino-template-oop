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
        uint8_t memory1[0x200]; // 512 bytes
        uint8_t memory2[0x400]; // 1024 bytes
    };
} // namespace Flash

struct DataType
{
    uint8_t test1;
    uint8_t test2;
    uint8_t test3;
    uint8_t test4;
};


#endif // UTILS_FLASH_STRUCTURE_