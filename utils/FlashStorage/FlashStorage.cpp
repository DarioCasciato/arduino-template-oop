// =============================================================================
// Utils | FlashStorage
// =============================================================================

#include "FlashStorage.h"
#include <Arduino.h>
#include <EEPROM.h>

uint16_t FlashStorage::startOffsetAddress_ = 0;

FlashStorage::FlashStorage(uint16_t storageSize, uint8_t dataSize)
{
    startAddr_ = startOffsetAddress_;
    startOffsetAddress_ += storageSize;
    storageSize_ = storageSize;
    dataSize_ = dataSize;
    numMaxEntries_ = storageSize / dataSize;
    numEntries_ = 0;
    nextAddr_ = startAddr_;
}

bool FlashStorage::write(void* data)
{
    if (numEntries_ + dataSize_ <= numMaxEntries_)
    {
        uint8_t byteData[dataSize_];  // Create a byte array to hold data
        memcpy(byteData, data, dataSize_);  // Copy data to byte array

        // Write byte array to EEPROM
        for (uint16_t i = 0; i < dataSize_; ++i)
        {
            EEPROM.write(nextAddr_ + i, byteData[i]);
        }

        #ifdef ESP8266
        EEPROM.commit();
        #endif

        nextAddr_ += dataSize_;  // Increment the address for next write
        numEntries_++;  // Increment the number of entries
        return true;
    }
    else
    {
        return false;
    }
}


bool FlashStorage::write(uint16_t index, void* data)
{
    if (index < numMaxEntries_)
    {
        uint8_t byteData[dataSize_];  // Create a byte array to hold data
        memcpy(byteData, data, dataSize_);  // Copy data to byte array

        // Calculate the exact EEPROM address to write to
        uint16_t writeAddr = startAddr_ + index * dataSize_;

        // Write byte array to EEPROM
        for (uint16_t i = 0; i < dataSize_; ++i)
        {
            EEPROM.write(writeAddr + i, byteData[i]);
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
    if (index < numEntries_)
    {
        uint16_t readAddr = startAddr_ + index * dataSize_;
        uint8_t byteData[dataSize_];  // Create a byte array to hold data

        // Read byte array from EEPROM
        for (uint16_t i = 0; i < dataSize_; ++i)
        {
            byteData[i] = EEPROM.read(readAddr + i);
        }

        memcpy(data, byteData, dataSize_);  // Copy data to destination

        return true;
    }
    else
    {
        return false;
    }
}

bool FlashStorage::readLast(void* data)
{
    if (numEntries_ > 0)
    {
        uint16_t readAddr = nextAddr_ - dataSize_;
        uint8_t byteData[dataSize_];  // Create a byte array to hold data

        // Read byte array from EEPROM
        for (uint16_t i = 0; i < dataSize_; ++i)
        {
            byteData[i] = EEPROM.read(readAddr + i);
        }

        memcpy(data, byteData, dataSize_);  // Copy data to destination

        return true;
    }
    else
    {
        return false;
    }
}

bool FlashStorage::clear()
{
    for (uint16_t i = 0; i < storageSize_; ++i)
    {
        EEPROM.write(startAddr_ + i, 0);
    }

    #ifdef ESP8266
    EEPROM.commit();
    #endif

    numEntries_ = 0;
    nextAddr_ = startAddr_;

    return true;
}

