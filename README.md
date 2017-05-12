[![Build Status](https://travis-ci.org/ntalekt/FauxMoESP_WS2812.svg?branch=master)](https://travis-ci.org/ntalekt/FauxMoESP_WS2812)
# FauxMoESP_WS2812FX
Control WS2812 RGB & RGBW pixels from Alexa using a NodeMCU ESP8266.

## Requirements
### Hardware
This code was tested on a HiLetgo NodeMCU ESP8266 board. You need some WS2812B LEDs (e.g. NeoPixel) connected to 5V and GND and a data pin of the ESP8266. I used an [74AHCT125](https://www.adafruit.com/product/1787) level-shifter in my project but I've found that it will do fine without one.<br>
![alt text](https://raw.githubusercontent.com/ntalekt/FauxMoESP_WS2812/master/FauxMoESP_WS2812.png)

### Software
You need to install the following additional libraries to compile the code:<br>
Adafruit_NeoPixel: https://github.com/adafruit/Adafruit_NeoPixel<br>
ESPAsyncTCP: https://github.com/me-no-dev/ESPAsyncTCP<br>
ESPAsyncWebServer: https://github.com/me-no-dev/ESPAsyncWebServer<br>
FauxmoESP: https://bitbucket.org/xoseperez/fauxmoesp<br>
WS2812FX: https://github.com/kitesurfer1404/WS2812FX<br>

## How to use
1. Update the `credentials.h` with your WIFI_SSID & WIFI_PASS<br>
```cpp
#define WIFI_SSID "EnterYourSSID"
#define WIFI_PASS "EnterYourPASS"
```
2. Update the `LED_COUNT` & `LED_PIN` variables.
3. Compile and run on your NodeMCU
4. Execute the Discover Devices option from your Alexa app or tell Echo/Dot to do it.<br>
⋅⋅* You should see several new "WeMo Switch" devices that the fauxmoESP has created.
