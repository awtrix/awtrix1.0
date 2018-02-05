#include <EEPROM.h>
#include <stdint.h>
#include "config.h"

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
  if (ENABLE_HEARTBEAT){setupHeartbeat();};
  prepareUpdates();
  matrixClear();

  //display_panOrBounceBitmap(24);
  play();
  weatherUpdate();
}


//--------------------------------------------------------------------------------
// AWTRIX Loop
//--------------------------------------------------------------------------------

void loop() {
     otaLoop();
     if (!OTA){
     udpLoop();
     tcpLoop();
     if (!GOL & !PET  & !WEATHER & !NOTIFICATION){
     const unsigned long Minutes = 1 * 1 * 1000UL;
     static unsigned long lastSampleTime = 0 - Minutes;  
     unsigned long now = millis();
     if (now - lastSampleTime >= Minutes)
         {
         lastSampleTime += Minutes;
         showTime();
         
         }
                                                }
     if (PET &!GOL & !WEATHER & !NOTIFICATION)vPetLoop();

     if (AUTO_BRIGHTNESS){
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
          previousMillis = currentMillis;
          checkLight();
        }
      }else{
        matrixBrightness(BRIGHTNESS);
      }
    } 
}
void prepareUpdates(){
    setupTimeUpdate();
 
}










