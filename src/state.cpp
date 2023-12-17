// =============================================================================
// Template-Project | State
// =============================================================================

#include "state.h"
#include "hardware.h"
#include "configurations.h"
#include "Timer.h"
#include "Logging.h"
#include "espWiFi.h"
#include "Flash/Flash.h"
#include "Flash/FlashStructure.h"

// create to_underlying macro for enums
#define to_underlying(x) uint8_t(x)

void getWifiCredentials(String& ssid, String& password, String receivedString);
void printSSIDHex(const char* ssid);

//------------------------------------------------------------------------------

namespace State
{
    States state = States::st_startup;

    void stateDriver()
    {
        switch (State::state)
        {
        case State::st_startup: stateStartup(); break;
        case State::st_connecting: stateConnecting(); break;
        case State::st_connected: stateConnected(); break;

        default:    // catch invalid state (implement safety backup)
        goto exception;
            break;
        }

        return;

        exception:
            for(;;) {}
    }

    void stateStartup()
    {
        String ssid;
        String password;

        if(Flash::credentials.read(to_underlying(Flash::ID::SSID), &ssid)
           && Flash::credentials.read(to_underlying(Flash::ID::PASSWORD), &password))
        {
            Logging::log("Found credentials in flash");

            Logging::log("SSID: ");
            printSSIDHex(ssid.c_str());
            Logging::log("Password: ");
            printSSIDHex(password.c_str());

            if(Wifi::establish(ssid, password))
            {
                State::state = State::st_connected;
            }
            else
            {
                State::state = State::st_connecting;
            }
        }
        else
        {
            State::state = State::st_connecting;
        }
    }


    // State implementations
    void stateConnecting()
    {
        // Create two String objects to store the SSID and password
        String ssid;
        String password;

        // If there is data available on the serial port, read it
        if (Hardware::SerialBT.available())
        {
            // Read the entire line from the serial port
            String line = Hardware::SerialBT.readStringUntil('\n');

            // Get the SSID and password from the line
            getWifiCredentials(ssid, password, line);

            printSSIDHex(ssid.c_str());
            printSSIDHex(password.c_str());

            // Try to connect to the WiFi network
            if(Wifi::establish(ssid, password))
            {
                // If the connection was successful, save credentials to flash
                Flash::credentials.write(to_underlying(Flash::ID::SSID), ssid);
                Flash::credentials.write(to_underlying(Flash::ID::PASSWORD), password);

                State::state = State::st_connected;
            }
        }



        delay(10);
    }

    void stateConnected()
    {
        delay(5000);

        if(WiFi.status() == WL_CONNECTED)
            Logging::log("Connection to WiFi still active");
    }
} // namespace State

//------------------------------------------------------------------------------

// Other Functions

void getWifiCredentials(String& ssid, String& password, String receivedString)
{
    // Split the line into two strings at the backslash character
    ssid = receivedString.substring(0, receivedString.indexOf('\\'));
    password = receivedString.substring(receivedString.indexOf('\\') + 1, receivedString.length() - 1);

    Logging::log("SSID: %s", ssid.c_str());
    Logging::log("Password: %s", password.c_str());
}

void printSSIDHex(const char* ssid) {
  for (int i = 0; i < strlen(ssid); i++) {
    printf("%02x", ssid[i]);
  }
  printf("\n");
}