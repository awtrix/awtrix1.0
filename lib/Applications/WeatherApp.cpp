#include <WeatherApp.h>
#include <BMP.h>


void WeatherApp::render(DisplayManager& display) {
    
    if (icon == "01") {
         display.drawApp(sun, String(temperature,1) + "\xA7",{0,0},{255, 255, 255},true,200);
    } else if (icon == "02") {
        display.drawApp(partlycloudy, String(temperature,1) + "\xA7",{0,0},{255, 255, 255},true,200);
    } else if (icon == "03") {
        display.drawApp(cloudy, String(temperature,1) + "\xA7",{0,0},{255, 255, 255},true,200);
    } else if (icon == "04") {
         display.drawApp(cloudy, String(temperature,1) + "\xA7",{0,0},{255, 255, 255},true,200);
    } else if (icon == "09") {
         display.drawApp(rain, String(temperature,1) + "\xA7",{0,0},{255, 255, 255},true,200);

    } else if (icon == "10") {
         display.drawApp(rain, String(temperature,1) + "\xA7",{0,0},{255, 255, 255},true,200);

    } else if (icon == "11") {
         display.drawApp(thunder, String(temperature,1) + "\xA7",{0,0},{255, 255, 255},true,200);

    } else if (icon == "13") {
         display.drawApp(snow, String(temperature,1) + "\xA7",{0,0},{255, 255, 255},true,200);

    } else  if (icon == "50"){
         display.drawApp(mist, String(temperature,1) + "\xA7",{0,0},{255, 255, 255},true,200);

     } else {   
        display.drawApp(sun, String(temperature,1) + "\xA7",{0,0},{255, 255, 255},true,200);

    }
    
}

void WeatherApp::enable() {
    Serial.println("WeatherApp started");
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
        temperature = owm_data["main"]["temp"];
        
        icon="";
        owm_data["weather"][0]["icon"].printTo(icon);
        icon.remove(0,1);
        icon.remove(icon.length()-2);

        }
    }
    http.end();
    jsonBuffer.clear();
  }
