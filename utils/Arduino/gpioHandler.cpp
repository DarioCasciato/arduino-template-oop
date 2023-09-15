// =============================================================================
// Utils | GPIO Handler
// =============================================================================

#include "gpioHandler.h"

bool myGPIO::getPort(Hardware::Port port)
{
    return digitalRead((uint8_t)port);
}

uint16_t myGPIO::getAnalogPort(Hardware::Port port)
{
    return analogRead((uint8_t)port);
}

void myGPIO::setPort(Hardware::Port port, bool value)
{
    digitalWrite((uint8_t)port, value);
}

void myGPIO::setAnalogPort(Hardware::Port port, uint8_t value)
{
    analogWrite((uint8_t)port, value);
}