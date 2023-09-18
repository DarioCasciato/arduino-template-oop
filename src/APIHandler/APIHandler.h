// =============================================================================
// Shelly1 | API Handler
// =============================================================================

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "apiKeys.h"

namespace APIHandler
{
    /// @brief Get the state of the switch
    bool getSwitchState();

    /// @brief Switch the relay on
    void switchOn();

    /// @brief Switch the relay off
    void switchOff();
}