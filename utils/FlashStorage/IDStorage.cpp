// =============================================================================
// Utils | ID Storage
// =============================================================================

#include "IDStorage.h"
#include "Arduino.h"
#include <EEPROM.h>

#include "FlashStorage.h"


IDStorage::IDStorage(uint16_t storageSize, uint16_t magicNumber)
    : initialized_(false) // Initialize to false
{
    header_.magic = magicNumber;  // Assign the passed magic number
    header_.startAddr_ = Flash::startOffsetAddress_;
    Flash::startOffsetAddress_ += storageSize + sizeof(header_);
    header_.storageSize_ = storageSize + sizeof(header_);
    header_.numMaxEntries_ = 0;
    header_.numEntries_ = 0;
    header_.nextAddr_ = header_.startAddr_ + sizeof(header_);
}

void IDStorage::init()
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

    if(readHeader->magic != header_.magic)
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

void IDStorage::updateHeader()
{
    uint8_t byteData[sizeof(header_)];  // Create a byte array to hold data
    memcpy(byteData, &header_, sizeof(header_));  // Copy data to byte array

    // Write byte array to EEPROM
    for (uint16_t i = 0; i < sizeof(header_); i++)
    {
        EEPROM.write(header_.startAddr_ + i, byteData[i]);
    }
}

void IDStorage::write(uint8_t id, uint8_t* data, uint8_t size)
{

}