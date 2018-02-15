#include <WeatherApp.h>

const unsigned long UpdateThreshold = 10000l;

#define WUNDERGROUND_API_KEY      "b9cd2ae34c2974b6"
#define WUNDERGROUND_LANGUAGE     "DL"
#define WUNDERGROUND_ZMW_CODE     "00000.215.10348"

/*
static unsigned char sun[]={0x24,0x00,0xbd,0x7e,0x7e,0x7e,0x00,0x00};
static unsigned char mask[]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
static unsigned char cloud[]={0x00,0x00,0x00,0x06,0x6f,0xef,0xff,0x7e};
static unsigned char highcloud[]={0x3,0x7,0x7,0x7,0x7,0x3,0x3,0x1};
static unsigned char rain[]={0x80,0x10,0x40,0x0,0x90,0x0,0x28,0x80};
static unsigned char snow[]={0x63,0x55,0x36,0x8,0x36,0x55,0x63,0x0};
*/

void WeatherApp::render(DisplayManager& display) {
    /* TODO: Render 8x8 bitmap
    if (conditions.weatherIcon == "cloudy") {
        matrixBitmap8x8(cloud,255,255,255);
    } else {
        matrixBitmap8x8(sun,255,255,0);
    } */

    display.drawText(conditions.currentTemp + "\xA7", {12, 0}, {255, 255, 255}, false);
}

void WeatherApp::tick(unsigned long delta) {
    elapsed += delta;

    if (elapsed >= UpdateThreshold) {
        wunderground.updateConditions(&conditions, WUNDERGROUND_API_KEY, WUNDERGROUND_LANGUAGE, WUNDERGROUND_ZMW_CODE);
        elapsed = 0;
    }
}
