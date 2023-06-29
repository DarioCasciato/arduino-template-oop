// =============================================================================
// Template-Project | Main
// =============================================================================

#include <Arduino.h>
#include "hardware.h"
#include "EdgeDetection.h"
#include "general.h"
#include "configurations.h"
#include "state.h"

void refreshData();

//------------------------------------------------------------------------------

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  for (;;)
  {
    refreshData();  // refresh port values

    State::stateDriver();
  }
}

//------------------------------------------------------------------------------

void refreshData()
{
  General::statusButton = Hardware::getPort(Hardware::Port::button);

  EdgeDetection::updateEdges();
}