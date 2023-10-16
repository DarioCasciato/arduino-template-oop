// =============================================================================
// Utils | ID Storage
// =============================================================================

#ifndef UTILS_ID_STORAGE_
#define UTILS_ID_STORAGE_

#include <stdint.h>
#include <Arduino.h>

/// @class IDStorage
/// @brief Class for handling ID-based storage in flash memory.
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

    /// @brief Update the header in flash memory.
    void updateHeader();

public:
    /// @brief Constructor for the IDStorage class.
    ///
    /// @param storageSize Size of the storage area in flash memory
    /// @param magicNumber Magic number to identify the header
    IDStorage(uint16_t storageSize, uint16_t magicNumber);

    /// @brief Initialize the storage area.
    void init();

    /// @brief Write data associated with a specific ID.
    ///
    /// @param id ID to which the data should be associated
    /// @param data Pointer to the data to be written
    /// @param size Size of the data to be written
    /// @return True if the write was successful, false otherwise
    bool write(uint8_t id, void* data, uint8_t size);

    /// @brief Write data associated with a specific ID. (overload)
    ///
    /// @param id ID to which the data should be associated
    /// @param str String to be written
    /// @return True if the write was successful, false otherwise
    bool write(uint8_t id, String data);

    /// @brief Read data associated with a specific ID.
    ///
    /// @param id ID from which the data should be read
    /// @param destination Pointer to store the read data
    /// @return True if the read was successful, false otherwise
    bool read(uint8_t id, void* destination);

    /// @brief Clear all data in the storage area.
    ///
    /// @return True if the clear operation was successful, false otherwise
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
