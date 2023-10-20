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

bool IDStorage::write(uint8_t id, void* data, uint8_t size)
{
    // + 2 for id and length
    if(header_.nextAddr_ + size + 2 > header_.startAddr_ + header_.storageSize_)
    {
        return false; // storage is full
    }

    uint8_t* cData = (uint8_t*)data;

    // check if id already exists
    uint16_t addr = header_.startAddr_ + sizeof(header_);

    for(uint8_t i = 0; i < header_.numEntries_; i++)
    {
        uint8_t readId = EEPROM.read(addr);
        if(readId == id)
        {
            // id already exists, overwrite it
            addr += 2; // skip id and length

            // write to eeprom
            for(uint8_t i = 0; i < EEPROM.read(addr - 1); i++)
            {
                EEPROM.write(addr + i, cData[i]);
            }

            updateHeader();

        #ifdef ESP8266
            EEPROM.commit();
        #endif

            return true;
        }

        addr += 2 + EEPROM.read(addr + 1); // move to next entry (id + size + data length)
    }

    // id does not exist, write it
    EEPROM.write(header_.nextAddr_, id);
    EEPROM.write(header_.nextAddr_ + 1, size);

    // write to eeprom
    for(uint8_t i = 0; i < size; i++)
    {
        EEPROM.write(header_.nextAddr_ + 2 + i, cData[i]);
    }

    header_.numEntries_++;
    header_.nextAddr_ += size + 2;

    updateHeader();

#ifdef ESP8266
    EEPROM.commit();
#endif

    return true;
}

bool IDStorage::write(uint8_t id, String data)
{
    // Convert String length to number of bytes.
    uint8_t size = data.length() + 1;  // +1 for the null terminator

    // + 2 for id and length
    if(header_.nextAddr_ + size + 2 > header_.startAddr_ + header_.storageSize_)
    {
        return false; // storage is full
    }

    // Convert the String to a char array for EEPROM write
    char charBuf[size];
    data.toCharArray(charBuf, size);

    uint8_t* cData = (uint8_t*) charBuf;

    // check if id already exists
    uint16_t addr = header_.startAddr_ + sizeof(header_);

    for(uint8_t i = 0; i < header_.numEntries_; i++)
    {
        uint8_t readId = EEPROM.read(addr);
        if(readId == id)
        {
            // id already exists, overwrite it
            addr += 2; // skip id and length

            // write to eeprom
            for(uint8_t i = 0; i < (EEPROM.read(addr - 1) - 1); i++)
            {
                EEPROM.write(addr + i, cData[i]);
            }

            updateHeader();

        #ifdef ESP8266
            EEPROM.commit();
        #endif

            return true;
        }

        addr += 2 + EEPROM.read(addr + 1); // move to next entry (id + size + data length)
    }

    // id does not exist, write it
    EEPROM.write(header_.nextAddr_, id);
    EEPROM.write(header_.nextAddr_ + 1, size);

    // write to eeprom
    for(uint8_t i = 0; i < size; i++)
    {
        EEPROM.write(header_.nextAddr_ + 2 + i, cData[i]);
    }

    header_.numEntries_++;
    header_.nextAddr_ += size + 2;

    updateHeader();

#ifdef ESP8266
    EEPROM.commit();
#endif

    return true;
}


bool IDStorage::read(uint8_t id, void* data)
{
    uint16_t addr = header_.startAddr_ + sizeof(header_);

    uint8_t* cData = (uint8_t*)data;

    for(uint8_t i = 0; i < header_.numEntries_; i++)
    {
        uint8_t readId = EEPROM.read(addr);
        if(readId == id)
        {
            // id found, read size
            uint8_t size = EEPROM.read(addr + 1);

            // read from eeprom
            for(uint8_t j = 0; j < size; j++)
            {
                cData[j] = EEPROM.read(addr + 2 + j);
            }

            return true;
        }

        addr += EEPROM.read(addr + 1) + 2; // skip id and length

        if(addr >= header_.nextAddr_)
        {
            return false; // id not found
        }
    }

    return false; // id not found
}

bool IDStorage::clear()
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

