
#ifndef NTP_H
#define	NTP_H


#include "WiFiUdp.h"
#include <stdint.h>
#include <Time.h>
#include "config.h"


class NTP
{
  public:
    NTP();
	void begin(const char* ntpServerName, int TimeZoneOffset);
    time_t getNtpTime(void);


  private:
	#define LOCALPORT 2390 // local port to listen on for UDP packets
	#define NTP_PACKET_SIZE 48 // NTP time stamp is in the first 48 bytes of the message
	#define seventyYears 2208988800UL // Unix time starts on Jan 1 1970. that's 2208988800 seconds

    void sendNTPpacket(IPAddress &address);
    uint8_t DSToffset(time_t date);

    // A UDP instance to let us send and receive packets over UDP
	uint8_t packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
	const char* _serverName;
	int8_t _timeZoneOffset;
  void setup();
  int adjustDstEurope();
};

#endif	/* NTP_H */
