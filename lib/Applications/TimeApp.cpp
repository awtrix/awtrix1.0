#include <TimeApp.h>

unsigned long previousMillis = 0; 
unsigned long interval = 1000; 

void TimeApp::render(DisplayManager& display) {
    String time = timeClient.getFormattedTime();
    display.drawText(time, {3, 0}, {152, 0, 255}, true,true);

    if (millis() - previousMillis > interval) {
        previousMillis = millis(); 
        //blink = !blink;
    }

    if (blink){
        display.fillRect(14,0,5,8,{0,0,0});
    }

  display.show();
}

void TimeApp::enable() {
    timeClient.updateTime();
}

