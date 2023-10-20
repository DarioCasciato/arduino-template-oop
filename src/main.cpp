// =============================================================================
// Template-Project | Main
// =============================================================================

#include <Arduino.h>
#include "hardware.h"
#include "EdgeDetection.h"
#include "configurations.h"
#include "state.h"
#include "Flash/Flash.h"


void refreshData();

//------------------------------------------------------------------------------

void setup()
{
    Serial.begin(115200);

    Hardware::SerialBT.begin("ESP32test"); //Bluetooth device name

    Flash::init();
}

void loop()
{
    for (;;)
    {
        refreshData();

        State::stateDriver();
    }
}

//------------------------------------------------------------------------------

void refreshData()
{

    Hardware::updateHardware();
    EdgeDetection::updateEdges();
}