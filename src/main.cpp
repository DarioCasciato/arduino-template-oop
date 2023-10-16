// =============================================================================
// Template-Project | Main
// =============================================================================

#include <Arduino.h>
#include "hardware.h"
#include "EdgeDetection.h"
#include "configurations.h"
#include "state.h"
#include "Flash/Flash.h"

#ifdef ESP32
#include "espWiFi.h"
#include <BluetoothSerial.h>
#endif



void refreshData();

//------------------------------------------------------------------------------

void setup()
{
#ifdef ESP32
    // ESP.wdtEnable(WDTO_1S);
    Serial.begin(115200);
    // Wifi::establish();
    Hardware::SerialBT.begin("ESP32test"); //Bluetooth device name

#else
    Serial.begin(9600);
#endif

    // Flash::init();
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