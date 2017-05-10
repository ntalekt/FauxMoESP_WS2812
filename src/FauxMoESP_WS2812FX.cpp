#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"
#include <WS2812FX.h>

/**
 * Set your SSID and WIFI password
 */
#include <credentials.h>

#define SERIAL_BAUDRATE 115200

fauxmoESP fauxmo;
/**
 * Define LED pixel count and LED pin
 */
#define LED_COUNT 12
#define LED_PIN 2

/**
 * Parameter 1 = number of pixels in strip
 * Parameter 2 = Arduino pin number (most are valid)
 * Parameter 3 = pixel type flags, add together as needed:
 * NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
 * NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
 * NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
 * NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
 * NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
 */
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

/**
 * LEDs are off by default
 */
volatile boolean neopixel_state = false;

/**
 * Setup WIFI and connect
 */
void wifiSetup() {

        // Set WIFI module to STA mode
        WiFi.mode(WIFI_STA);

        // Connect
        Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
        WiFi.begin(WIFI_SSID, WIFI_PASS);

        // Wait
        while (WiFi.status() != WL_CONNECTED) {
                Serial.print(".");
                delay(100);
        }
        Serial.println();

        // Connected!
        Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}
/**
 * Callback to set state of the lights and set the mode.
 * @param device_id   null
 * @param device_name Name of the Fauxmo device
 * @param state       boolean with true/false depending on whether the device should be on or off.
 */
void callback(uint8_t device_id, const char * device_name, bool state) {
        Serial.printf("[MAIN] %s state: %s\n", device_name, state ? "ON" : "OFF");

        //FX_MODE_RAINBOW_CYCLE 'Alexa, turn rainbow lights on'
        if ( (strcmp(device_name, "rainbow lights") == 0) ) {
                if (state) {
                        neopixel_state = true;
                        ws2812fx.setBrightness(200);
                        ws2812fx.setSpeed(200);
                        ws2812fx.setMode(9);
                } else {
                        neopixel_state = false;
                        ws2812fx.setBrightness(0);
                        ws2812fx.setMode(0);

                }
        }
        //FX_MODE_BREATH 'Alexa, turn breathe lights on'
        if ( (strcmp(device_name, "breathe lights") == 0) ) {
                if (state) {
                        neopixel_state = true;
                        ws2812fx.setBrightness(200);
                        ws2812fx.setSpeed(200);
                        ws2812fx.setMode(2);
                } else {
                        neopixel_state = false;
                        ws2812fx.setBrightness(0);
                        ws2812fx.setMode(0);
                }
        }
        //FX_MODE_STATIC_WHITE 'Alexa, turn white lights on'
        if ( (strcmp(device_name, "white lights") == 0) ) {
                if (state) {
                        neopixel_state = true;
                        ws2812fx.setColor(ws2812fx.Color(0, 0, 0, 200));
                        ws2812fx.setBrightness(200);
                        ws2812fx.setMode(0);
                } else {
                        neopixel_state = false;
                        ws2812fx.setBrightness(0);
                        ws2812fx.setMode(0);
                }
        }
        //FX_MODE_LARSON_SCANNER 'Alexa, turn kitt lights on'
        if ( (strcmp(device_name, "kitt lights") == 0) ) {
                if (state) {
                        neopixel_state = true;
                        ws2812fx.setColor(0xFF0400);
                        ws2812fx.setBrightness(200);
                        ws2812fx.setMode(40);
                } else {
                        neopixel_state = false;
                        ws2812fx.setColor(0x33CCCC);
                        ws2812fx.setBrightness(0);
                        ws2812fx.setMode(0);
                }
        }

        //'Alexa, turn night mode on' to DIM lights
        if ( (strcmp(device_name, "night mode") == 0) ) {
                if (state) {
                        neopixel_state = true;
                        ws2812fx.setBrightness(75);
                } else {
                        neopixel_state = false;
                        ws2812fx.setBrightness(240);
                }
        }
}

void setup() {
        // Init WS2812FX
        ws2812fx.init();
        ws2812fx.setBrightness(0);
        ws2812fx.setMode(0);
        ws2812fx.setColor(0x33CCCC);
        ws2812fx.start();

        // Init serial port and clean garbage
        Serial.begin(SERIAL_BAUDRATE);
        Serial.println();
        Serial.println();
        Serial.println("After connection, ask Alexa/Echo to 'turn rainbow lights on' or 'off'");
        Serial.println("Modes = Rainbow Lights, Breathe Lights, White Lights (RGBW), Kitt Lights, Night Mode");

        // Wifi
        wifiSetup();

        // Fauxmo devices
        fauxmo.addDevice("white lights");
        fauxmo.addDevice("night mode");
        fauxmo.addDevice("kitt lights");
        fauxmo.addDevice("rainbow lights");
        fauxmo.addDevice("breathe lights");
        fauxmo.onMessage(callback);
}

void loop() {
        fauxmo.handle();
        ws2812fx.service();
}
