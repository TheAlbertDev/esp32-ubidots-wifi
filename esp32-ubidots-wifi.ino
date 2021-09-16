/*
Copyright (c) 2021 Albert Álvarez Carulla.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Developed and maintained by Albert Álvarez-Carulla

Albert Álvarez-Carulla @thealbertdev at github: https://github.com/thealbertdev

*/

#include <UbidotsEsp32Mqtt.h>
#include "private_data.h"

#define LED_PIN 2
#define ADC_PIN 34

const int PUBLISH_FREQUENCY = 1000;

Ubidots ubidots(UBIDOTS_TOKEN);
uint16_t adcValue = 0;
uint32_t timer;

void handleMessage(char *topic, byte *payload, unsigned int length)
{
    char ledValue = (char)payload[0];

    if (ledValue == '1')
    {
        digitalWrite(LED_PIN, HIGH);
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
    }
}

void setup()
{

    Serial.begin(115200);
    Serial.println();
    Serial.println("Device initialization...");

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    pinMode(ADC_PIN, INPUT);

    ubidots.connectToWifi(WIFI_SSID, WIFI_PASSWORD);
    ubidots.setCallback(handleMessage);
    ubidots.setup();
    ubidots.reconnect();
    ubidots.subscribeLastValue("esp32-01", "led-status");

    timer = millis();
}

void loop()
{

    if (!ubidots.connected())
    {
        ubidots.reconnect();
        ubidots.subscribeLastValue("esp32-01", "led-status");
        return;
    }

    if (abs(millis() - timer) > PUBLISH_FREQUENCY)
    {
        adcValue = analogRead(ADC_PIN);
        ubidots.add("temperature", (float)adcValue);
        ubidots.publish("esp32-01");
        timer = millis();
    }

    ubidots.loop();
}