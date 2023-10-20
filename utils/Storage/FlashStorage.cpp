// =============================================================================
// Utils | FlashStorage
// =============================================================================

#include "FlashStorage.h"
#include <Arduino.h>
#include <EEPROM.h>

FlashStorage::FlashStorage(uint16_t storageSize, uint8_t dataSize, uint16_t magicNumber)
    : initialized_(false) // Initialize to false
{
    header_.magic = magicNumber;  // Assign the passed magic number
    header_.startAddr_ = Flash::startOffsetAddress_;
    Flash::startOffsetAddress_ += storageSize + sizeof(header_);
    header_.storageSize_ = storageSize + sizeof(header_);
    header_.dataSize_ = dataSize;
    header_.numMaxEntries_ = storageSize / dataSize;
    header_.numEntries_ = 0;
    header_.nextAddr_ = header_.startAddr_ + sizeof(header_);
}

void FlashStorage::init()
{
    if (initialized_)
    {
        return; // Already initialized, do nothing
    }

    // Read header from EEPROM
    uint8_t byteData[sizeof(header_)];  // Create a byte array to hold data
    for (uint16_t i = 0; i < sizeof(header_); i++)
    {
        byteData[i] = EEPROM.read(header_.startAddr_ + i);
    }

    // Cast the read byte array back to a Header struct for easier comparison
    Header *readHeader = reinterpret_cast<Header*>(byteData);

    // Validate magic number
    if (readHeader->magic != header_.magic || readHeader->dataSize_ != header_.dataSize_)
    {
        // Header is invalid, initialize it
        updateHeader();
    }
    else
    {
        // Header is valid, populate it from EEPROM data
        memcpy(&header_, byteData, sizeof(header_));
    }

    initialized_ = true;  // Mark as initialized
}

void FlashStorage::updateHeader()
{
    uint8_t byteData[sizeof(header_)];  // Create a byte array to hold data
    memcpy(byteData, &header_, sizeof(header_));  // Copy data to byte array

    // Write byte array to EEPROM
    for (uint16_t i = 0; i < sizeof(header_); i++)
    {
        EEPROM.write(header_.startAddr_ + i, byteData[i]);
    }

    #ifdef ESP8266
    EEPROM.commit();
    #endif
}

bool FlashStorage::write(void* data)
{
    if (header_.numEntries_ + 1 <= header_.numMaxEntries_)
    {
        uint8_t byteData[header_.dataSize_];  // Create a byte array to hold data
        memcpy(byteData, data, header_.dataSize_);  // Copy data to byte array

        // Write byte array to EEPROM
        for (uint16_t i = 0; i < header_.dataSize_; i++)
        {
            EEPROM.write(header_.nextAddr_ + i, byteData[i]);
        }

        header_.nextAddr_ += header_.dataSize_;  // Increment the address for next write
        header_.numEntries_++;  // Increment the number of entries

        updateHeader();

        #ifdef ESP8266
        EEPROM.commit();
        #endif
        return true;
    }
    else
    {
        return false;
    }
}


bool FlashStorage::write(uint16_t index, void* data)
{
    if (index < header_.numMaxEntries_)
    {
        uint8_t byteData[header_.dataSize_];  // Create a byte array to hold data
        memcpy(byteData, data, header_.dataSize_);  // Copy data to byte array

        // Calculate the exact EEPROM address to write to
        uint16_t writeAddr = (header_.startAddr_ + sizeof(header_)) + (index * header_.dataSize_);

        // Write byte array to EEPROM
        for (uint16_t i = 0; i < header_.dataSize_; i++)
        {
            EEPROM.write(writeAddr + i, byteData[i]);
        }

        if (writeAddr + header_.dataSize_ > header_.nextAddr_)
        {
            header_.nextAddr_ = writeAddr + header_.dataSize_;
            header_.numEntries_ = (header_.nextAddr_ - header_.startAddr_) / header_.dataSize_;
            updateHeader();
        }

        #ifdef ESP8266
        EEPROM.commit();
        #endif

        return true;
    }
    else
    {
        return false;
    }
}


bool FlashStorage::read(uint16_t index, void* data)
{
    if (index < header_.numEntries_)
    {
        // Account for header size when calculating read address
        uint16_t readAddr = (header_.startAddr_ + sizeof(header_)) + (index * header_.dataSize_);
        uint8_t byteData[header_.dataSize_];  // Create a byte array to hold data


        // Read byte array from EEPROM
        for (uint16_t i = 0; i < header_.dataSize_; i++)
        {
            byteData[i] = EEPROM.read(readAddr + i);
        }

        memcpy(data, byteData, header_.dataSize_);  // Copy data to destination

        return true;
    }
    else
    {
        return false;
    }
}

bool FlashStorage::readLast(void* data)
{
    if (header_.numEntries_ > 0)
    {
        uint16_t readAddr = header_.nextAddr_ - header_.dataSize_;
        uint8_t byteData[header_.dataSize_];  // Create a byte array to hold data

        // Read byte array from EEPROM
        for (uint16_t i = 0; i < header_.dataSize_; i++)
        {
            byteData[i] = EEPROM.read(readAddr + i);
        }

        memcpy(data, byteData, header_.dataSize_);  // Copy data to destination

        return true;
    }
    else
    {
        return false;
    }
}

bool FlashStorage::clear()
{
    for (uint16_t i = sizeof(header_); i < header_.storageSize_; i++)
    {
        EEPROM.write((header_.startAddr_ + sizeof(header_)) + i, 0);
    }

    header_.numEntries_ = 0;
    header_.nextAddr_ = header_.startAddr_ + sizeof(header_);

    updateHeader();

    #ifdef ESP8266
    EEPROM.commit();
    #endif

    return true;
}

