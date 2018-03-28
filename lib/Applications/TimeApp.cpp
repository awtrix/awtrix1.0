#include <TimeApp.h>
#include <stdio.h>
unsigned long previousMillis = 0; 
unsigned long interval = 1000; 

 


void TimeApp::render(DisplayManager& display) {

char buff[14];

  sprintf_P(buff, PSTR("%02d:%02d:%02d"), hour(), minute(),second()); 
    if (BIG_TIME){
    display.drawText(buff, {1, 0}, true,false,true);

    }else{
    display.drawText(buff, {3, 0}, true,true,true);
    }
    
    if ((millis() - previousMillis > interval) &  BIG_TIME ) {
        previousMillis = millis(); 
        blink = !blink;
    }

    if (blink & BIG_TIME){
        display.fillRect(14,0,5,6,{0,0,0});
    }
   
    if (SHOW_WEEKDAY){
        long day = now() / 86400L;
        int day_of_the_week = (day+4) % 7;
        display.drawWeekday(day_of_the_week);
    }

  display.show();
}

void TimeApp::enable() {
}


