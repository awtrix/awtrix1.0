#include <WeatherApp.h>
#include <BMP.h>


void WeatherApp::render(DisplayManager& display) {
    if (description == "Clouds") {
         display.drawApp(cloudy, String(temperature) + "\xA7",{0,0},{255, 255, 255},true,200);
    } else if (description == "partlycloudy") {
        display.drawApp(partlycloudy, String(temperature) + "\xA7",{0,0},{255, 255, 255},true,200);
    } else if (description == "rain") {
        display.drawApp(rain, String(temperature) + "\xA7",{0,0},{255, 255, 255},true,200);
    } else if (description == "snow") {
        //display.drawBitmap(snow, {0, 0}, {255, 255, 255}, 8, 8);
    } else if (description == "tstorms") {

    } else {
        display.drawApp(sun, String(temperature) + "\xA7",{0,0},{255, 255, 255},true,200);

    }
    
}

void WeatherApp::enable() {
    StaticJsonBuffer<1200> jsonBuffer;
    HTTPClient http;
    http.begin(String("http://api.openweathermap.org/data/2.5/weather?id=") + OWM_LOCATION +("&appid=")+ OWM_API_KEY +("&units=metric"));
    int httpCode = http.GET();
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        JsonObject& owm_data = jsonBuffer.parseObject(payload);
        if (!owm_data.success()) {
          Serial.println("Parsing failed");
          return;
        }
        String city = owm_data["city"]["name"];
        temperature = owm_data["main"]["temp"];
        humidity = owm_data["main"]["humidity"];
        owm_data["weather"][0]["main"].printTo(description);
        }
    }
    http.end();
  }
