
#include "ESP8266WiFi.h"
#include "Arduino.h"
#include "NTP.h"
#include <TimeLib.h>

 WiFiUDP UDP;

long startsecondswd;            // weekday start time in seconds
long stopsecondswd;             // weekday stop  time in seconds
long nowseconds;  

NTP::NTP(void)
{
}

void NTP::begin(const char* ntpServerName, int TimeZoneOffset)
{
	_serverName = ntpServerName;
	_timeZoneOffset = TimeZoneOffset;
	UDP.begin(LOCALPORT);	
}

time_t NTP::getNtpTime(void)
{
  while (UDP.parsePacket() > 0) ; 
  IPAddress timeServerIP;
  WiFi.hostByName(_serverName, timeServerIP); 
  sendNTPpacket(timeServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = UDP.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      UDP.read(packetBuffer, NTP_PACKET_SIZE); 
      time_t secsSince1900;
      secsSince1900 =  (time_t)packetBuffer[40] << 24;
      secsSince1900 |= (time_t)packetBuffer[41] << 16;
      secsSince1900 |= (time_t)packetBuffer[42] << 8;
      secsSince1900 |= (time_t)packetBuffer[43];
      time_t secsSince1970 = secsSince1900 - 2208988800UL;
      int8_t totalOffset = (int8_t)(_timeZoneOffset + DSToffset(secsSince1970));
      UDP.stop();
      return secsSince1970 + (time_t)(totalOffset * SECS_PER_HOUR) ;
    }
    yield();
  }
  return 0; 
}

void NTP::sendNTPpacket(IPAddress &address)
{
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  UDP.beginPacket(address, 123); 
  UDP.write(packetBuffer, NTP_PACKET_SIZE);
  UDP.endPacket();
}

uint8_t NTP::DSToffset(time_t date)
{
  tmElements_t tm;
  tm.Month = 3; //MARCH
  tm.Year = year(date) - 1970;
  tm.Day = 7; //March 7th
  tm.Hour = 2; //2AM
  time_t beginDST = nextSunday( makeTime(tm) );
  tm.Month = 10; //October
  tm.Day = 31; //last day of October;
  time_t endDST = nextSunday( makeTime(tm) );
  return (((date >= beginDST) && (date < endDST))? 1: 0);
}

void NTP::checkSleepMode(){
  uint32_t nowseconds, startsecondswd,stopsecondswd;
      nowseconds = ((hour() * 3600) + (minute() * 60) + second());
      startsecondswd = (SLEEP_START_HR * 3600) + (SLEEP_START_MIN * 60);
      stopsecondswd = (SLEEP_STOP_HR * 3600) + (SLEEP_STOP_MIN * 60);


      if(nowseconds >= startsecondswd && nowseconds <= stopsecondswd){
         SLEEP_MODE=1;
      }
      else if (nowseconds>=stopsecondswd-24*3600)
      {
        SLEEP_MODE=0;
      }
}
