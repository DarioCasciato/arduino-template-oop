// =============================================================================
// Utils | RollStorage
// =============================================================================

#include "RollStorage.h"
#include "../../src/Flash/FlashStructure.h"
#include <Arduino.h>
#include <EEPROM.h>

RollStorage::RollStorage(uint8_t* startAddr, uint16_t storageSize, uint8_t dataSize)
    : initialized_(false)
{
    // Calculate the offset of the start address from the base of the Flash::Layout
    header_.startAddr_ = startAddr - reinterpret_cast<uint8_t*>(&Flash::flashLayout);
    header_.storageSize_ = storageSize;
    header_.dataSize_ = dataSize;
    header_.numMaxEntries_ = (storageSize - sizeof(header_)) / dataSize;
    header_.numEntries_ = 0;
    header_.nextAddr_ = header_.startAddr_ + sizeof(header_);
    header_.magic = magicNumber;
}


void RollStorage::init()
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

void RollStorage::updateHeader()
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

bool RollStorage::write(void* data)
{
    // cast data* to uint8 array
    uint8_t* byteData = reinterpret_cast<uint8_t*>(data);

    // Write byte array to EEPROM
    for (uint16_t i = 0; i < header_.dataSize_; i++)
    {
        EEPROM.write(header_.nextAddr_ + i, byteData[i]);
    }

    header_.nextAddr_ += header_.dataSize_;

    // Wrap around if we reach the end of the storage
    if (header_.nextAddr_ >= header_.startAddr_ + header_.storageSize_)
    {
        header_.nextAddr_ = header_.startAddr_ + sizeof(header_);
    }

    // Increment numEntries_ but don't exceed numMaxEntries_
    if (header_.numEntries_ < header_.numMaxEntries_)
    {
        header_.numEntries_++;
    }

    updateHeader();

    #ifdef ESP8266
    EEPROM.commit();
    #endif
    return true;
}



bool RollStorage::read(uint16_t index, void* data)
{
    if (index >= header_.numEntries_)
    {
        return false; // Index out of range
    }

    uint16_t readAddr = header_.nextAddr_ - ((index + 1) * header_.dataSize_);

    // Wrap around if necessary
    if (readAddr < header_.startAddr_ + sizeof(header_))
    {
        readAddr += header_.storageSize_- sizeof(header_);
    }

    uint8_t byteData[header_.dataSize_];
    for (uint16_t i = 0; i < header_.dataSize_; i++)
    {
        byteData[i] = EEPROM.read(readAddr + i);
    }
    memcpy(data, byteData, header_.dataSize_);
    return true;
}


bool RollStorage::readLast(void* data)
{
    if (header_.numEntries_ == 0)
    {
        return false; // No entries to read
    }

    uint16_t readAddr;
    if (header_.nextAddr_ == header_.startAddr_ + sizeof(header_))
    {
        // Read Entry at the very end of the storage. if next addr is at the start of the storage (i.e. we have wrapped around)
        readAddr = header_.startAddr_ + header_.storageSize_ - header_.dataSize_;
    }
    else
    {
        // Read the entry just before nextAddr_
        readAddr = header_.nextAddr_ - header_.dataSize_;
    }

    uint8_t byteData[header_.dataSize_];
    for (uint16_t i = 0; i < header_.dataSize_; i++)
    {
        byteData[i] = EEPROM.read(readAddr + i);
    }
    memcpy(data, byteData, header_.dataSize_);
    return true;
}


bool RollStorage::clear()
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
