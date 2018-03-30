#define BLYNK_PRINT Serial1
#include <AwtrixBlynk.h>
#include <BlynkSimpleEsp8266.h>
#include <DisplayManager.h>
#include <ApplicationManager.h>
#include <Settings.h>


WidgetTerminal terminal(V8);

void sendStates() {
    Blynk.virtualWrite(0, BRIGHTNESS);
    Blynk.virtualWrite(2, BIG_TIME);
    Blynk.virtualWrite(3, SCROLL_SPEED);
    Blynk.virtualWrite(5, PET_MOOD);
    Blynk.virtualWrite(6, SHOW_WEEKDAY);

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
    BRIGHTNESS=Value;
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

BLYNK_WRITE(V6) // PET_MOOD
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

  }


BLYNK_WRITE(V9) // PET_MOOD
{
     SLEEP_MODE=param.asInt();
     
}

BLYNK_READ(V10) //Display RAM
{
    Blynk.virtualWrite(10, ESP.getFreeHeap());
}

