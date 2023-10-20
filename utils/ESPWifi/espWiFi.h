// =============================================================================
// Template-Project | ESP-WiFi
// =============================================================================

#include <Arduino.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#endif
#ifdef ESP32
#include <WiFi.h>
#endif

namespace Wifi
{
    /// @brief Establishes a connection to the Wi-Fi network.
    /// @param ssid The SSID of the Wi-Fi network.
    /// @param password The password of the Wi-Fi network.
    /// @return True if the connection was successful, false otherwise.
    bool establish(String ssid, String password);
} // namespace WiFi
