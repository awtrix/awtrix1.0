#include <TimeApp.h>
#include <../Awtrix/config.h>
#include <Time.h>
#define dayOfWeek(_time_)  ((( _time_ / SECS_PER_DAY + 4)  % DAYS_PER_WEEK)+1) // 1 = Sunday


unsigned long previousMillis = 0; 
unsigned long interval = 1000; 


void TimeApp::render(DisplayManager& display) {
    String time = timeClient.getFormattedTime();
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
        display.drawWeekday((((timeClient.getCurrentEpochWithUtcOffset() / 86400 + 4)  % 7)+1));
    }

  display.show();
}

void TimeApp::enable() {
    timeClient.updateTime();
}

