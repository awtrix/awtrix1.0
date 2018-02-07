#include <EEPROM.h>
#include <stdint.h>
#include "config.h"
#include "Ticker.h"

void doUpdates();
void checkLight();
void sTime();


//--------------------------------------------------------------------------------
// Process Variables
//--------------------------------------------------------------------------------
bool GOL;
bool NOTIFICATION;
bool TIME;
bool WEATHER;
bool PET;
bool OTA;
int  PET_MOOD = 1;
unsigned long previousMillis = 0;
const long interval = 1000; 

Ticker updateData(doUpdates, 10000,0, MILLIS);
Ticker autoBrightness(checkLight, 2000,0, MILLIS);
Ticker Time(sTime, 2000,0, MILLIS);

//--------------------------------------------------------------------------------
// Programm Setup
//--------------------------------------------------------------------------------

void setup() {
  Serial.begin(115200);
  loadConfig();
  otaSetup();
  pinMode(BUTTTON_RESET_CONFIG, INPUT);
  matrixSetup();
  wifiSetup();
  soundSetup();
  Serial.println("Awtrix successfully started");
  matrixClear();
  mqttSetup();
  doUpdates();
  updateData.start();
  autoBrightness.start();
  Time.start();
}


//--------------------------------------------------------------------------------
// AWTRIX Loop
void loop() {
     otaLoop();
     if (!OTA){
     udpLoop();
     tcpLoop();
     MQTTloop();
     updateData.update();
     autoBrightness.update();
     Time.update();
    } 
}

void doUpdates(){
    timeUpdate();
    getYTSubs(YTchannel);
    weatherUpdate();
}


void sTime(){
 showTime(); 
}








