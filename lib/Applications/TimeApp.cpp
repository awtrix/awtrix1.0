#include <TimeApp.h>

unsigned long previousMillis = 0; 
unsigned long interval = 1000; 

void TimeApp::render(DisplayManager& display) {
    String time = timeClient.getTime();
    if (BIG_TIME==1){
    display.drawText(time, {1, 0}, true,false,true);

    }else{
    display.drawText(time, {3, 0}, true,true,true);
    }
    
    if ((millis() - previousMillis > interval)& BIG_TIME ) {
        previousMillis = millis(); 
        blink = !blink;
    }

    if (blink & BIG_TIME){
        display.fillRect(14,0,5,6,{0,0,0});
    }
   
    if (SHOW_WEEKDAY){
        display.drawWeekday(timeClient.getWeekday());
        
    }

  display.show();
}

void TimeApp::enable() {

    timeClient.updateTime();


}


