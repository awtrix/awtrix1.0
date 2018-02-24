#include <WeatherApp.h>

static unsigned char sun[]={0x24,0x18,0xbd,0x7e,0x7e,0xbd,0x18,0x24};
static unsigned char mask[]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
static unsigned char cloud[]={0x00,0x00,0x00,0x06,0x6f,0xef,0xff,0x7e};
static unsigned char highcloud[]={0x3,0x7,0x7,0x7,0x7,0x3,0x3,0x1};
static unsigned char rain[]={0x80,0x10,0x40,0x0,0x90,0x0,0x28,0x80};
static unsigned char snow[]={0x63,0x55,0x36,0x8,0x36,0x55,0x63,0x0};

void WeatherApp::render(DisplayManager& display) {

    if (conditions.weatherIcon == "cloudy") {
        display.drawBitmap(cloud, {0, 0}, {255, 255, 255}, 8, 8);
    } else if (conditions.weatherIcon == "partlycloudy") {
        display.drawBitmap(sun, {0, 0}, {255, 255, 0}, 8, 8);
        display.drawBitmap(cloud, {0, 0}, {255, 255, 255}, 8, 8);
    } else if (conditions.weatherIcon == "rain") {
        display.drawBitmap(rain, {0, 0}, {0, 0, 255}, 8, 8);
    } else if (conditions.weatherIcon == "snow") {
        display.drawBitmap(snow, {0, 0}, {255, 255, 255}, 8, 8);
    } else if (conditions.weatherIcon == "tstorms") {

    } else {
        display.drawBitmap(sun, {0, 0}, {255, 255, 0}, 8, 8);
    } 

    display.drawText(conditions.currentTemp + "\xA7", {9, 0}, {255, 255, 255}, false,false);
}

void WeatherApp::update() {
    wunderground.updateConditions(&conditions, settings.get<String>("wundergroundApiKey"), settings.get<String>("wundergroundLanguage"), settings.get<String>("wundergroundZmwCode"));
}
