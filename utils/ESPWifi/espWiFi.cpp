// =============================================================================
// Template-Project | Main
// =============================================================================

#ifdef ESP8266

#include "espWiFi.h"

namespace
{
    inline const char* ssid = "SSID-HERE";
    inline const char* password = "PASSWORD-HERE";
}


void Wifi::establish()
{
    WiFi.hostname("NodeMCU | Template-Project");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi!");
}

#endif