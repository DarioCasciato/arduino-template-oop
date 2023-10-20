// =============================================================================
// Template-Project | State
// =============================================================================

#include "state.h"
#include "hardware.h"
#include "configurations.h"
#include "Timer.h"
#include "Logging.h"
#include "espWiFi.h"

void getWifiCredentials(String& ssid, String& password, String receivedString);

//------------------------------------------------------------------------------

namespace State
{
    States state = States::st_idle;

    void stateDriver()
    {
        switch (State::state)
        {
        case State::st_idle: stateIdle(); break;
        case State::st_error: stateError(); break;

        default:    // catch invalid state (implement safety backup)
        goto exception;
            break;
        }

        return;

        exception:
            for(;;) {}
    }

    // State implementations
    void stateIdle()
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

            // Try to connect to the WiFi network
            if(Wifi::establish(ssid, password))
            {

            }
        }



        delay(10);
    }

    void stateError()
    {

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