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
  Serial.begin(9600);

  Flash::init();
}

void loop()
{
  for (;;)
  {
    refreshData();  // refresh port values

    State::stateDriver(); // drive state machine
  }
}

//------------------------------------------------------------------------------

void refreshData()
{

  Hardware::updateHardware();
  EdgeDetection::updateEdges();
}