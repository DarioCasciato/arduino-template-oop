// =============================================================================
// Utils | Wifi Serial-Login
// =============================================================================

#ifdef ESP8266

#ifndef WIFI_SERIAL_LOGIN_
#define WIFI_SERIAL_LOGIN_

#include <ESP8266WiFi.h>
#include "../../src/configurations.h"

namespace WifiSerialLogin
{
    /// @brief logs into a wifi network using the serial monitor
    void serialWifiLogin();

    /// @brief prints a list of nearby networks to the serial monitor
    void scanNearbyNetworks();
} // namespace WifiSerialLogin


#endif  // WIFI_SERIAL_LOGIN_
#endif  // ESP8266