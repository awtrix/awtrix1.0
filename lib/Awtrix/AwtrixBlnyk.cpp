#define BLYNK_PRINT Serial1
#include <AwtrixBlynk.h>
#include <BlynkSimpleEsp8266.h>
#include <DisplayManager.h>
#include <ApplicationManager.h>
#include <Settings.h>


WidgetTerminal terminal(V8);

void ICACHE_FLASH_ATTR sendStates() {
    Blynk.virtualWrite(0, BRIGHTNESS);
    Blynk.virtualWrite(2, BIG_TIME);
    Blynk.virtualWrite(3, SCROLL_SPEED);

    Blynk.virtualWrite(5, PET_MOOD);
    Blynk.virtualWrite(6, SHOW_WEEKDAY);
    Blynk.virtualWrite(9, SLEEP_MODE_ACTIVE);
    Blynk.virtualWrite(11, WEATHER_ACTIVE);
    Blynk.virtualWrite(12, PET_ACTIVE);
    Blynk.virtualWrite(13, GOL_ACTIVE);
    Blynk.virtualWrite(14, YT_ACTIVE);
    Blynk.virtualWrite(15, FB_ACTIVE);
    Blynk.virtualWrite(16, TWITTER_ACTIVE);
    Blynk.virtualWrite(17, FIRE_ACTIVE);
    Blynk.virtualWrite(18, RAINBOW);
    Blynk.virtualWrite(19, DHT_ACTIVE);
}

void AwtrixBlynk::setup() {
    Serial.println(F("Setting up BLYNK"));
    Blynk.config(BLYNK_KEY);
    Blynk.connect(180);
    sendStates();
}

void AwtrixBlynk::loop() {
    Blynk.run();
}

BLYNK_CONNECTED() {
 sendStates();
}


BLYNK_WRITE(V0) // Set Brightness
{
    int Value = param.asInt(); 
    DisplayManager::getInstance().setBrightness(Value);
    AwtrixSettings::getInstance().saveSettings();
}

BLYNK_WRITE(V1) // Change TextColor
{
    TEXT_COLOR_R = param[0].asInt();
    TEXT_COLOR_G = param[1].asInt();
    TEXT_COLOR_B = param[2].asInt();
    DisplayManager::getInstance().setColor({TEXT_COLOR_R,TEXT_COLOR_G,TEXT_COLOR_B});
    AwtrixSettings::getInstance().saveSettings();
}

BLYNK_WRITE(V2) // BIG_TIME
{
     BIG_TIME=param.asInt();
     AwtrixSettings::getInstance().saveSettings();
}

BLYNK_WRITE(V3) // Scrool_Speed
{
    SCROLL_SPEED=param.asInt();
    AwtrixSettings::getInstance().saveSettings();
}

BLYNK_WRITE(V4) // nextApplication
{
     if(param.asInt()==1) ApplicationManager::getInstance().nextApplication() ;
}

BLYNK_WRITE(V5) // PET_MOOD
{
     PET_MOOD=param.asInt();
     AwtrixSettings::getInstance().saveSettings();
}

BLYNK_WRITE(V6) // SHOW_WEEKDAY
{
     SHOW_WEEKDAY=param.asInt();
     AwtrixSettings::getInstance().saveSettings();
}

BLYNK_WRITE(V7) {

   TimeInputParam t(param);

  // Process start time
    SLEEP_START_HR = t.getStartHour();
    SLEEP_START_MIN = t.getStartMinute();
 
    SLEEP_STOP_HR = t.getStopHour();
    SLEEP_STOP_MIN = t.getStopMinute();
    AwtrixSettings::getInstance().saveSettings();
  }


BLYNK_WRITE(V9) // SLEEP_MODE
{
    SLEEP_MODE_ACTIVE=param.asInt();
    if (SLEEP_MODE_ACTIVE==0) SLEEP_MODE=0;
    AwtrixSettings::getInstance().saveSettings();

}


BLYNK_READ(V10) //Display RAM
{
    Blynk.virtualWrite(10, ESP.getFreeHeap());
}



BLYNK_WRITE(V11) 
{
     WEATHER_ACTIVE=param.asInt();
}

BLYNK_WRITE(V12) 
{
     PET_ACTIVE=param.asInt();
}

BLYNK_WRITE(V13) 
{
     GOL_ACTIVE=param.asInt();
}

BLYNK_WRITE(V14) 
{
     YT_ACTIVE=param.asInt();
}

BLYNK_WRITE(V15) 
{
     FB_ACTIVE=param.asInt();
}

BLYNK_WRITE(V16) 
{
     TWITTER_ACTIVE=param.asInt();
}

BLYNK_WRITE(V17) 
{
     FIRE_ACTIVE=param.asInt();
}

BLYNK_WRITE(V19) 
{
     DHT_ACTIVE=param.asInt();
}

BLYNK_WRITE(V20) 
{

     if(param.asInt()==1){
        AwtrixSettings::getInstance().saveSettings();
        ESP.reset();
     }
         
}

BLYNK_WRITE(V18) 
{
     RAINBOW=param.asInt();
    AwtrixSettings::getInstance().saveSettings();

}

