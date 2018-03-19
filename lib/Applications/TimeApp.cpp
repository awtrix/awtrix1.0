#include <TimeApp.h>


unsigned long previousMillis = 0; 
unsigned long interval = 1000; 

void TimeApp::render(DisplayManager& display) {
    String time = timeClient.getFormattedTime();
    if (BIG_TIME==1){
    display.drawText(time, {1, 0}, true,false);

    }else{
    display.drawText(time, {3, 0}, true,true);
    }
    

    if ((millis() - previousMillis > interval) & BIG_TIME==1) {
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

