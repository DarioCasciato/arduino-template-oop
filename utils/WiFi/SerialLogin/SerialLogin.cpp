// =============================================================================
// Utils | Wifi Serial-Login
// =============================================================================

#ifdef ESP8266

#include "SerialLogin.h"
#include "configurations.h"

void WifiSerialLogin::scanNearbyNetworks()
{
    WiFi.mode(WIFI_STA);  // Set WiFi mode to station (client)
    WiFi.disconnect();    // Disconnect from any previously connected WiFi
    delay(100);

    Serial.println("Scanning for nearby Wi-Fi networks...");

    uint8_t n = WiFi.scanNetworks();  // Start network scan and get the number of networks found

    if (n == 0)
    {
        Serial.println("No networks found.");
    }
    else
    {
        Serial.print(n);
        Serial.println(" networks found.");

        for (int i = 0; i < n; ++i)
        {
        // Print SSID and signal strength for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.println(" dBm)");
            delay(10);
        }
    }
}

void WifiSerialLogin::serialWifiLogin()
{
    while (WiFi.status() != WL_CONNECTED)
    {
        // If ssid and password from configurations.h are not empty, use them
        if (String(ssid).length() > 0 && String(password).length() > 0)
        {
            Serial.println("Using stored WiFi credentials.");
            WiFi.begin(ssid, password);
        }
        else
        {
            // Otherwise, request new credentials
            scanNearbyNetworks();

            Serial.println("Enter your WiFi credentials.");

            // Get SSID
            Serial.print("SSID: ");
            while (Serial.available() == 0)
            {
                delay(100);
            }
            String ssid_buffer = Serial.readStringUntil('\n');
            char tempSsid[ssid_buffer.length() + 1];
            ssid_buffer.toCharArray(tempSsid, ssid_buffer.length() + 1);

            // Get Password
            Serial.print("Password: ");
            while (Serial.available() == 0)
            {
                delay(100);
            }
            String password_buffer = Serial.readStringUntil('\n');
            char tempPassword[password_buffer.length() + 1];
            password_buffer.toCharArray(tempPassword, password_buffer.length() + 1);

            // Store them in your global ssid and password variables
            strcpy(ssid, tempSsid);
            strcpy(password, tempPassword);

            WiFi.begin(ssid, password);
        }

        // Wait for connection
        for(uint8_t i = 0; i < 10; i++)
        {
            delay(500);
            Serial.print(".");
            if(WiFi.status() == WL_CONNECTED)
                break;
        }

        if(WiFi.status() == WL_CONNECTED)
        {
            Serial.println();
            Serial.println("WiFi connected.");
            return;
        }
        else
        {
            Serial.println();
            Serial.println("Connection failed.");
            Serial.println();
        }
    }
}

#endif  // ESP8266