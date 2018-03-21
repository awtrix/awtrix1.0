
#include <AwtrixBlynk.h>
#include <BlynkSimpleEsp8266.h>
#include <DisplayManager.h>
#include <ApplicationManager.h>
#include <Settings.h>

void sendStates() {
    Blynk.virtualWrite(0, BRIGHTNESS);
    Blynk.virtualWrite(2, BIG_TIME);
    Blynk.virtualWrite(3, SCROLL_SPEED);
    Blynk.virtualWrite(5, PET_MOOD);
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



BLYNK_WRITE(V0) // Set Brightness
{
    int Value = param.asInt(); 

    DisplayManager::getInstance().setBrightness(Value);
    BRIGHTNESS=Value;
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

BLYNK_READ(V10) //Display RAM
{
    Blynk.virtualWrite(10, ESP.getFreeHeap());
}

