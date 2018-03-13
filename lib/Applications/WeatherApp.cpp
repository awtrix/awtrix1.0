#include <WeatherApp.h>

static const uint16_t sun[]PROGMEM  {0x0, 0x0, 0xffe9, 0x0, 0x0, 0xffe9, 0x0, 0x0, 0xffe9, 0x0, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0x0, 0xffe9, 0x0, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0x0, 0x0, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0x0, 0x0, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0x0, 0x0, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0x0, 0xffe9, 0x0, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0x0, 0xffe9, 0x0, 0x0, 0xffe9, 0x0, 0x0, 0xffe9, 0x0, 0x0 };
static const uint16_t cloudy[]PROGMEM  {0x0, 0x0, 0x0, 0xce79, 0xce79, 0x0, 0x0, 0x0, 0x0, 0x0, 0xce79, 0xce79, 0xce79, 0xce79, 0xce79, 0x0, 0x0, 0xce79, 0xce79, 0xce79, 0xce79, 0xce79, 0xce79, 0xce79, 0x0, 0xce79, 0xce79, 0xce79, 0xce79, 0xce79, 0xce79, 0xce79, 0x0, 0x0, 0xce79, 0xce79, 0xce79, 0xce79, 0xce79, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
static const uint16_t rain[]PROGMEM  {0xce79, 0xce79, 0xce79, 0xce79, 0xce79, 0xce79, 0xce79, 0x0, 0xce79, 0xce79, 0xce79, 0xce79, 0xce79, 0xce79, 0xce79, 0x0, 0x4b39, 0x0, 0xce79, 0xce79, 0xce79, 0xce79, 0x0, 0x4b39, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4b39, 0x0, 0x0, 0x0, 0x4b39, 0x0, 0x4b39, 0x0, 0x0, 0x4b39, 0x0, 0x4b39, 0x0, 0x0, 0x0, 0x0, 0x4b39, 0x0, 0x4b39, 0x0, 0x0, 0x4b39, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4b39, 0x0, 0x0, 0x4b39, 0x0, 0x0, 0x4b39, 0x0 };
static const uint16_t partlycloudy[]PROGMEM  {0x0, 0x0, 0xffe9, 0x0, 0x0, 0xffe9, 0x0, 0x0, 0xffe9, 0x0, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0x0, 0xffe9, 0x0, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0x0, 0x0, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0x0, 0xffe9, 0xffff, 0xffff, 0xffe9, 0xffe9, 0xffff, 0xffff, 0xffe9, 0xffff, 0xffff, 0xffff, 0xffff, 0xffe9, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0 };
static const uint16_t cloud1[]PROGMEM ={0xb0c3, 0xff2c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9e73, 0x4b39, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  };

void WeatherApp::render(DisplayManager& display) {

    if (conditions.weatherIcon == "cloudy") {
         display.drawApp(cloudy, conditions.currentTemp + "\xA7",{0,0},{255, 255, 255},true,50,200);
    } else if (conditions.weatherIcon == "partlycloudy") {
        display.drawApp(partlycloudy, conditions.currentTemp + "\xA7",{0,0},{255, 255, 255},true,50,200);
    } else if (conditions.weatherIcon == "rain") {
        display.drawApp(rain, conditions.currentTemp + "\xA7",{0,0},{255, 255, 255},true,50,200);
    } else if (conditions.weatherIcon == "snow") {
        //display.drawBitmap(snow, {0, 0}, {255, 255, 255}, 8, 8);
    } else if (conditions.weatherIcon == "tstorms") {

    } else {
        display.drawApp(sun, conditions.currentTemp + "\xA7",{0,0},{255, 255, 255},true,40,200);
    } 
}

void WeatherApp::update() {
    wunderground.updateConditions(&conditions, WUNDERGROUND_API_KEY, WUNDERGROUND_LANGUAGE, WUNDERGROUND_ZMW_CODE);
}
