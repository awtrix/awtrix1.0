#include <Arduino.h>
#include <JsonListener.h>
#include "WundergroundConditions.h"
// Wunderground Settings

WGConditions conditions;
WundergroundConditions wunderground(IS_METRIC);

static unsigned char sun[]={0x24,0x00,0xbd,0x7e,0x7e,0x7e,0x00,0x00};
static unsigned char mask[]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
static unsigned char cloud[]={0x00,0x00,0x00,0x06,0x6f,0xef,0xff,0x7e};
static unsigned char highcloud[]={0x3,0x7,0x7,0x7,0x7,0x3,0x3,0x1};
static unsigned char rain[]={0x80,0x10,0x40,0x0,0x90,0x0,0x28,0x80};
static unsigned char snow[]={0x63,0x55,0x36,0x8,0x36,0x55,0x63,0x0};

void weatherUpdate() {
    wunderground.updateConditions(&conditions, WUNDERGRROUND_API_KEY, WUNDERGRROUND_LANGUAGE, WUNDERGROUND_ZMW_CODE);
}

void showWeather(){
    if (conditions.weatherIcon == "cloudy") {
        matrixBitmap8x8(cloud,255,255,255);
    } else {
        matrixBitmap8x8(sun,255,255,0);
    }

    matrixText(false,conditions.currentTemp+"\xA7",12,0,255,255,255);
}
