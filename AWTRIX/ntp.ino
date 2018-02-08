#include "TimeClient.h"
TimeClient timeClient(UTC_OFFSET);
String ntp;
 
void timeUpdate(){
   timeClient.updateTime();
   ntp=timeClient.getFormattedTime();
}

void setupTimeUpdate(){
  timeUpdate();
  showTime();
}

void showTime(){
  matrixText(true,ntp,1,0,255,255,255);
}


