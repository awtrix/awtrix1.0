#include <TimeApp.h>
#include <../Awtrix/config.h>



unsigned long previousMillis = 0; 
unsigned long interval = 1000; 

void TimeApp::render(DisplayManager& display) {
    String time = timeClient.getFormattedTime();
    if (BIG_TIME==1){
    display.drawText(time, {1, 0}, true,false);

    }else{
    display.drawText(time, {3, 0}, true,true);
    }

    if ((millis() - previousMillis > interval)& BIG_TIME ) {
        previousMillis = millis(); 
        blink = !blink;
    }

    if (blink & BIG_TIME){
        display.fillRect(14,0,5,6,{0,0,0});
    }

    if (SHOW_WEEKDAY){
        long day = timeClient.getCurrentEpochWithUtcOffset() / 86400L;
        int day_of_the_week = (day+4) % 7;
        display.drawWeekday(day_of_the_week);
    }

  display.show();
}

void TimeApp::enable() {
    timeClient.updateTime();
}

