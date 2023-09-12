// =============================================================================
// Template-Project | Main
// =============================================================================

#include <Arduino.h>
#include "hardware.h"
#include "EdgeDetection.h"
#include "configurations.h"
#include "state.h"
#include "Flash/Flash.h"
#include "SerialLogin.h"

void refreshData();

//------------------------------------------------------------------------------

void setup()
{
  Serial.begin(9600);

  Flash::init();

#ifdef ESP8266
  WifiSerialLogin::serialWifiLogin();
#endif // ESP8266
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