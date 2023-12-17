// =============================================================================
// Template-Project | Main
// =============================================================================

#if defined(ESP8266) || defined(ESP32)

#include "espWiFi.h"
#include "Logging.h"


namespace
{
    void printSSIDHex(const char* ssid) {
        for (int i = 0; i < strlen(ssid); i++) {
            printf("%02x", ssid[i]);
        }
        printf("\n");
    }
}


bool Wifi::establish(String ssid, String password)
{
    // Connect to the WiFi network
    WiFi.mode(WIFI_STA);

    Logging::log("Wifi ssid: ");
    printSSIDHex(ssid.c_str());

    Logging::log("Wifi password: ");
    printSSIDHex(password.c_str());

    WiFi.begin(ssid, password);

    for(uint8_t i = 0; i < 10; i++)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            Logging::log("Connected to WiFi!");
            return true;
        }

        delay(1000);
        Logging::log("Connecting to WiFi...");
    }

    // If the connection failed, log an error
    Logging::log("Failed to connect to WiFi!");
    return false;
}

#endif