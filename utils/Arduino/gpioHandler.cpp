// =============================================================================
// Utils | GPIO Handler
// =============================================================================

#include "gpioHandler.h"

bool vGPIO::getPort(Hardware::Port port)
{
    return digitalRead((uint8_t)port);
}

uint16_t vGPIO::getAnalogPort(Hardware::Port port)
{
    return analogRead((uint8_t)port);
}

void vGPIO::setPort(Hardware::Port port, bool value)
{
    digitalWrite((uint8_t)port, value);
}

void vGPIO::setAnalogPort(Hardware::Port port, uint8_t value)
{
    analogWrite((uint8_t)port, value);
}