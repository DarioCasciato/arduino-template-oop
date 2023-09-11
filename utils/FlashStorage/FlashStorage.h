// =============================================================================
// Utils | FlashStorage
// =============================================================================

#ifndef UTILS_FLASH_STORAGE_
#define UTILS_FLASH_STORAGE_

#include <stdint.h>

namespace Flash
{
    void init();
} // namespace Flash


/// @class FlashStorage
/// @brief Class for handling storage in flash memory.
class FlashStorage
{
private:
    static uint16_t startOffsetAddress_;  ///< Static variable to hold the initial offset address for all instances
    uint16_t storageSize_;  ///< Size of the storage area in flash memory
    uint16_t startAddr_;  ///< Starting address for this instance
    uint8_t dataSize_;  ///< Size of individual data entries
    uint16_t numMaxEntries_;  ///< Maximum number of entries that can be stored
    uint16_t numEntries_;  ///< Number of entries currently stored
    uint16_t nextAddr_;  ///< Next available address for writing

public:
    /// @brief Constructor for the FlashStorage class.
    ///
    /// @param storageSize Size of the storage area in flash memory
    /// @param dataSize Size of individual data entries
    FlashStorage(uint16_t storageSize, uint8_t dataSize);

    /// @brief Write data to the next available address.
    ///
    /// @param data Pointer to the data to be written
    /// @return True if the write was successful, false otherwise
    bool write(void* data);

    /// @brief Write data to a specific index.
    ///
    /// @param index Index at which the data should be written
    /// @param data Pointer to the data to be written
    /// @return True if the write was successful, false otherwise
    bool write(uint16_t index, void* data);

    /// @brief Read data from a specific index.
    ///
    /// @param index Index from which the data should be read
    /// @param data Pointer to store the read data
    /// @return True if the read was successful, false otherwise
    bool read(uint16_t index, void* data);

    /// @brief Read the last written data.
    ///
    /// @param data Pointer to store the read data
    /// @return True if the read was successful, false otherwise
    bool readLast(void* data);

    /// @brief Clear all data in the storage area.
    ///
    /// @return True if the clear operation was successful, false otherwise
    bool clear();

    /// @brief Get the number of entries currently stored.
    ///
    /// @return Number of entries
    uint16_t getNumEntries() { return numEntries_; }

    /// @brief Get the size of the storage area.
    ///
    /// @return Storage size
    uint16_t getStorageSize() { return storageSize_; }

    /// @brief Get the size of individual data entries.
    ///
    /// @return Data size
    uint16_t getDataSize() { return dataSize_; }
};


#endif // UTILS_FLASH_STORAGE_
