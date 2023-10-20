// =============================================================================
// Template-Project | Main
// =============================================================================

#include <Arduino.h>
#include "hardware.h"
#include "EdgeDetection.h"
#include "configurations.h"
#include "state.h"
#include "Flash/Flash.h"

#ifdef ESP8266
#include "espWiFi.h"
#endif

void refreshData();

//------------------------------------------------------------------------------

void setup()
{
#ifdef ESP8266
    ESP.wdtEnable(WDTO_1S);
    Serial.begin(115200);
    Wifi::establish();
#else
    Serial.begin(115200);
#endif

    Hardware::SerialBT.begin("ESP32test"); //Bluetooth device name

    //Flash::init();
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