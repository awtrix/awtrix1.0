#include <TimeApp.h>
unsigned long previousMillis = 0; 
unsigned long interval = 1000; 
bool TD = 1;


time_t NTPgetTime()
{
    return NTPclient.getNtpTime();
}

void TimeApp::render(DisplayManager& display) {

    if (TD || SLEEP_MODE){
        char t[14];
        sprintf_P(t, PSTR("%02d:%02d:%02d"), hour(), minute(),second());
        if ( timeStatus()){
            display.drawText(t, {1, 0}, true,!BIG_TIME,true);
                    if ((millis() - previousMillis > interval) &  BIG_TIME ) {
        previousMillis = millis(); 
        blink = !blink;
    }
        }else{
            display.drawText("SYNCING", {2, 0}, true,true,true);
            }
        


    if (blink & BIG_TIME ){
        display.fillRect(14,0,5,6,{0,0,0});
    }
   
 
    }else{
        char  d[14];
        sprintf_P(d, PSTR("%02d. %s"), day(), monname[month()-1]); 
         if (timeStatus()){
              display.drawText(d , {4, 0}, true,true,true);
        }else{
            display.drawText("SYNCING", {2, 0}, true,true,true);
            }
      
        }
    
   if (SHOW_WEEKDAY && !SLEEP_MODE){
        long day = now() / 86400L;
        int day_of_the_week = (day+3) % 7;
        display.drawWeekday(day_of_the_week);
    }

  display.show();
 if (RAINBOW) ++loopCounter;
}

void TimeApp::enable() {
    //setSyncProvider(getExternalTime(NTPgetTime));
  setTime(NTPclient.getNtpTime());
    Serial.println("TimeApp started");
    loopCounter=0;
    TD=!TD;
}


