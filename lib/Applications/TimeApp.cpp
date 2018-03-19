#include <TimeApp.h>


unsigned long previousMillis = 0; 
unsigned long interval = 1000; 

void TimeApp::render(DisplayManager& display) {
    String time = timeClient.getFormattedTime();
    display.drawText(time, {3, 0}, true,!BIG_TIME);

    if ((millis() - previousMillis > interval) & BIG_TIME) {
        previousMillis = millis(); 
        blink = !blink;
    }

    if (blink){
        display.fillRect(14,0,5,8,{0,0,0});
    }

  display.show();
}

void TimeApp::enable() {
    timeClient.updateTime();
}

