#include <BMEApp.h>
#include <BMP.h>
#define ASCII_ESC 27
#define DHTTYPE DHT22
#define DHTPIN 2
bool TH;


BMEApp::BMEApp(){
    Wire.begin(0,2);   
    BMESensor.begin();  
}

void BMEApp::render(DisplayManager& display) {
    if (TH){
        display.drawApp(temp,String(temperature)+ "\xA7",{0,0},{255, 255, 255},true,200);
    }else{
        display.drawApp(hum,String(humidity)+ "%",{0,0},{255, 255, 255},true,200);
    } 
    
}


void BMEApp::enable() {
    Serial.println("BMEApp started");
    BMESensor.refresh();
    sprintf(bufout,"%c[1;0H",ASCII_ESC);
    Serial.print(bufout);
    int h=(int)BMESensor.temperature;
    int t=(int)BMESensor.humidity;
    if (h<100) humidity = h;
    if (t<100) temperature = t;
    TH=!TH;
}
 


