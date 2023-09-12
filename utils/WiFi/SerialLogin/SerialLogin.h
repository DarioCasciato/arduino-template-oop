// =============================================================================
// Utils | Wifi Serial-Login
// =============================================================================

#ifndef WIFI_SERIAL_LOGIN_
#define WIFI_SERIAL_LOGIN_

#ifdef ESP8266

#include <ESP8266WiFi.h>

namespace WifiSerialLogin
{
    /// @brief logs into a wifi network using the serial monitor
    void serialWifiLogin();

    /// @brief prints a list of nearby networks to the serial monitor
    void scanNearbyNetworks();
} // namespace WifiSerialLogin


#endif  // ESP8266
#endif  // WIFI_SERIAL_LOGIN_