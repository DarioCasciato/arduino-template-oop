// =============================================================================
// Shelly1 | API Handler
// =============================================================================

#include "APIHandler.h"
#include "configurations.h"
#include <ArduinoJson.h>
#include "Logging.h"

bool APIHandler::getSwitchState()
{
    WiFiClient client;
    HTTPClient http;

    http.begin(client, shelly_api);
    int httpCode = http.GET();

    if (httpCode > 0)
    {
        String payload = http.getString();
        http.end();  // Close the connection

        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, payload);

        if (error)
        {
            Serial.println("Failed to parse JSON");
            return false;
        }

        bool ison = doc["ison"];  // Extract the 'ison' value
        Logging::log("ison: %d" + ison);
        return ison;
    }
    else
    {
        Serial.println("Error on HTTP request");
        http.end();
        return false;
    }
}

void APIHandler::switchOn()
{
    WiFiClient client;
    HTTPClient http;

    http.begin(client, String(shelly_api) + String(shelly_api_on));
    int httpCode = http.GET();

    if (httpCode > 0)
    {
        String payload = http.getString();
        http.end();  // Close the connection
    }
    else
    {
        Serial.println("Error on HTTP request");
        http.end();
    }
}

void APIHandler::switchOff()
{
    WiFiClient client;
    HTTPClient http;

    http.begin(client, String(shelly_api) + String(shelly_api_off));
    int httpCode = http.GET();

    if (httpCode > 0)
    {
        String payload = http.getString();
        http.end();  // Close the connection
    }
    else
    {
        Serial.println("Error on HTTP request");
        http.end();
    }
}