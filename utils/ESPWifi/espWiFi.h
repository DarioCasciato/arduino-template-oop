// =============================================================================
// Template-Project | ESP-WiFi
// =============================================================================

#include <Arduino.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#endif

namespace Wifi
{
    /// @brief Establishes a connection to the Wi-Fi network.
    void establish();
} // namespace WiFi
