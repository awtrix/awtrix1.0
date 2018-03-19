
#include <AwtrixBlynk.h>
#include <BlynkSimpleEsp8266.h>
#include <DisplayManager.h>
#include "config.h"
#include <ApplicationManager.h>




void sendStates() {
    Blynk.virtualWrite(0, BRIGHTNESS);
    Blynk.virtualWrite(2, BIG_TIME);
    Blynk.virtualWrite(3, SCROLL_SPEED);
}


void AwtrixBlynk::setup() {
    Blynk.config(BLYNK_KEY);
    Blynk.connect(180);
    sendStates();
}

void AwtrixBlynk::loop() {
    Blynk.run();
}

BLYNK_CONNECTED() {
    Blynk.syncAll();
}

BLYNK_WRITE(V0) // Set Brightness
{
    int Value = param.asInt(); // assigning incoming value from pin V1 to a variable
    DisplayManager::getInstance().setBrightness(Value);
    BRIGHTNESS=20;
}

BLYNK_WRITE(V1) // Change TextColor
{
    TEXT_COLOR_R = param[0].asInt();
    TEXT_COLOR_G = param[1].asInt();
    TEXT_COLOR_B = param[2].asInt();
    DisplayManager::getInstance().setColor({TEXT_COLOR_R,TEXT_COLOR_G,TEXT_COLOR_B});
}

BLYNK_WRITE(V2) // BIG_TIME
{
     BIG_TIME=param.asInt();
}

BLYNK_WRITE(V3) // BIG_TIME
{
     SCROLL_SPEED=param.asInt();
}

BLYNK_WRITE(V4) // nextApplication
{
     if(param.asInt()==1) ApplicationManager::getInstance().nextApplication() ;
}

BLYNK_READ(V10) //Display RAM
{
    Blynk.virtualWrite(3, ESP.getFreeHeap());
}

