#include <DHT22App.h>
#include <BMP.h>

#define DHTTYPE DHT11
#define DHTPIN 2
bool TH;;


DHT22App::DHT22App() : dht(DHTPIN, DHTTYPE) {
    dht.begin();
}

void DHT22App::render(DisplayManager& display) {
    if (TH){
        display.drawApp(temp,String(temperature)+ "\xA7",{0,0},{255, 255, 255},true,200);
    }else{
        display.drawApp(hum,String(humidity)+ "%",{0,0},{255, 255, 255},true,200);
    } 
    
}


void DHT22App::enable() {
    int h=(int)dht.readHumidity(false);
    int t=(int)dht.readTemperature(false);
    if (h<100) humidity = h;
    if (t<100) temperature = t;
    TH=!TH;
}
 


