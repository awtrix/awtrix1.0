#include <WeatherApp.h>
#include <BMP.h>


void WeatherApp::render(DisplayManager& display) {

    if (conditions.weatherIcon == "cloudy") {
         display.drawApp(cloudy, conditions.currentTemp + "\xA7",{0,0},{255, 255, 255},true,200);
    } else if (conditions.weatherIcon == "partlycloudy") {
        display.drawApp(partlycloudy, conditions.currentTemp + "\xA7",{0,0},{255, 255, 255},true,200);
    } else if (conditions.weatherIcon == "rain") {
        display.drawApp(rain, conditions.currentTemp + "\xA7",{0,0},{255, 255, 255},true,200);
    } else if (conditions.weatherIcon == "snow") {
        //display.drawBitmap(snow, {0, 0}, {255, 255, 255}, 8, 8);
    } else if (conditions.weatherIcon == "tstorms") {

    } else {
        display.drawApp(sun, conditions.currentTemp + "\xA7",{0,0},{255, 255, 255},true,200);

    }
}

void WeatherApp::enable() {
    wunderground.updateConditions(&conditions, WUNDERGROUND_API_KEY, WUNDERGROUND_LANGUAGE, WUNDERGROUND_ZMW_CODE);
}
