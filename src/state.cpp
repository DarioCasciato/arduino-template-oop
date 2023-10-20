// =============================================================================
// Template-Project | State
// =============================================================================

#include "state.h"
#include "hardware.h"
#include "configurations.h"
#include "Timer.h"
#include "Logging.h"

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
        // Create two character pointers to store the SSID and password
        char* ssid = nullptr;
        char* password = nullptr;

        // If there is data available on the serial port, read it
        if (Hardware::SerialBT.available())
        {
            // Read the entire line from the serial port
            String line = Hardware::SerialBT.readStringUntil('\n');

            // Split the line into two strings at the backslash character
            String ssidString = line.substring(0, line.indexOf('\\'));
            String passwordString = line.substring(line.indexOf('\\') + 1, line.length());

            // Allocate memory for the SSID and password strings
            ssid = new char[ssidString.length() + 1];
            password = new char[passwordString.length() + 1];

            // Copy the SSID and password strings to the allocated memory
            strcpy(ssid, ssidString.c_str());
            strcpy(password, passwordString.c_str());

            Logging::log("SSID: %s", ssid);
            Logging::log("Password: %s", password);
        }

        // Once the SSID and password have been read, delay for 10ms
        delay(10);
    }

    void stateError()
    {

    }
} // namespace State

//------------------------------------------------------------------------------

// Other Functions