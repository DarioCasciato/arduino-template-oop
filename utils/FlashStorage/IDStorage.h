// =============================================================================
// Utils | ID Storage
// =============================================================================

#ifndef UTILS_ID_STORAGE_
#define UTILS_ID_STORAGE_

#include <stdint.h>


class IDStorage
{
private:
    bool initialized_;  ///< Flag to indicate if the storage area has been initialized

    struct Header
    {
        uint16_t magic;  ///< Magic number to identify the header
        uint16_t storageSize_;  ///< Size of the storage area in flash memory
        uint16_t startAddr_;  ///< Starting address for this instance
        uint16_t numMaxEntries_;  ///< Maximum number of entries that can be stored
        uint16_t numEntries_;  ///< Number of entries currently stored
        uint16_t nextAddr_;  ///< Next available address for writing
    } header_;

    struct entry
    {
        uint8_t id;  ///< ID of the entry
        uint8_t length;  ///< Length of the data
        uint8_t* data;  ///< Data
    };

    /// @brief Update the header in flash memory.
    void updateHeader();

public:
    IDStorage(uint16_t storageSize, uint16_t magicNumber);

    void init();

    bool write(uint8_t id, uint8_t* data, uint8_t size);

    bool read(uint8_t id, uint8_t* destination);

    bool clear();

    /// @brief Get the number of entries currently stored.
    ///
    /// @return Number of entries
    uint16_t getNumEntries() { return header_.numEntries_; }

    /// @brief Get the size of the storage area.
    ///
    /// @return Storage size
    uint16_t getStorageSize() { return header_.storageSize_; }
};


#endif // UTILS_ID_STORAGE_