#include <AwtrixUDP.h>

int localUdpPort = 52829;
char inputBuffer[512];

void ICACHE_FLASH_ATTR AwtrixUDP::setup(){
     Udp.begin(localUdpPort);
     sendMSG("Awtrix Boot");
}

void AwtrixUDP::sendMSG(String msg){

  Udp.beginPacket(Udp.remoteIP(), 52828);
  Udp.print(msg);
  Udp.endPacket();
}

void AwtrixUDP::loop() {
    int packetSize = Udp.parsePacket();
    if (packetSize) {
      Udp.read(inputBuffer, 512);

      if (packetSize > 0)
        {
          inputBuffer[packetSize] = 0;
        }
        String dat;
        dat = String(inputBuffer);
        String command = dat.substring(0,dat.indexOf("%"));
        String payload = dat.substring(dat.indexOf("%")+1,dat.length());
       
        sendMSG(AwtrixBroker::getInstance().doJob(command,payload));

    }
    delay(10);
}