// =============================================================================
// Utils | FlashStorage
// =============================================================================

#ifndef UTILS_FLASH_STRUCTURE_
#define UTILS_FLASH_STRUCTURE_

#include <stdint.h>

namespace Flash
{
    struct Layout
    {
        uint8_t memory1[0x40]; // 64 bytes
    };

    extern Layout flashLayout; // Declaration of the global instance


    struct DataType
    {
        uint8_t data1;
        uint16_t data2;
        uint32_t data3;
    };
} // namespace Flash


#endif // UTILS_FLASH_STRUCTURE_
