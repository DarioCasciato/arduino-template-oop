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
#include "MathUtils.h"

void splitWifiCredentials(String& ssid, String& password, String receivedString);

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
        case State::st_connected: stateApp(); break;

        default:    // catch invalid state (implement safety backup)
        goto exception;
            break;
        }

        return;

        exception:
            for(;;) {}
    }

//------------------------------------------------------------------------------
// Connect states

    void stateStartup()
    {
        char ssid[32] = {0};
        char password[64] = {0};

        if(Flash::credentials.read(to_underlying(Flash::ID::SSID), &ssid)
           && Flash::credentials.read(to_underlying(Flash::ID::PASSWORD), &password))
        {
            Logging::log("Found credentials in flash");

            // Create two String objects to store the SSID and password
            String s_ssid(ssid, Flash::credentials.getSize(to_underlying(Flash::ID::SSID)));
            String s_password(password, Flash::credentials.getSize(to_underlying(Flash::ID::PASSWORD)));

            if(Wifi::establish(s_ssid, s_password))
            {
                State::state = State::st_connected;
            }
            else
            {
                Logging::log("Failed to connect to WiFi with stored credentials");
                State::state = State::st_connecting;
            }
        }
        else
        {
            Logging::log("No credentials found in flash");
            State::state = State::st_connecting;
        }
    }


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
            splitWifiCredentials(ssid, password, line);

            // Try to connect to the WiFi network
            if(Wifi::establish(ssid, password))
            {
                // If the connection was successful, save credentials to flash
                Flash::credentials.write(to_underlying(Flash::ID::SSID), (void*)ssid.c_str(), ssid.length());
                Flash::credentials.write(to_underlying(Flash::ID::PASSWORD), (void*)password.c_str(), password.length());

                State::state = State::st_connected;
            }
        }



        delay(10);
    }


//------------------------------------------------------------------------------
// App state

    void stateApp()
    {
        delay(5000);

        if(WiFi.status() == WL_CONNECTED)
            Logging::log("Connection to WiFi still active");
    }


} // namespace State

//------------------------------------------------------------------------------

// Other Functions

void splitWifiCredentials(String& ssid, String& password, String receivedString)
{
    // Split the line into two strings at the backslash character
    ssid = receivedString.substring(0, receivedString.indexOf('\\'));
    password = receivedString.substring(receivedString.indexOf('\\') + 1, receivedString.length() - 1);

    Logging::log("SSID: %s", ssid.c_str());
    Logging::log("Password: %s", password.c_str());
}
