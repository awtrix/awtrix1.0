#include <AwtrixUDP.h>
char  ReplyBuffer[] = "OK";
String IP_ADRESS;
int localUdpPort = 52829;
char inputBuffer[512];


void AwtrixUDP::setup(){
     Udp.begin(localUdpPort);
}


void AwtrixUDP::loop() {
    int packetSize = Udp.parsePacket();
    if (packetSize) {
     
      Udp.read(inputBuffer, 256);
      Serial.println("Contents:");
      Serial.println(inputBuffer);
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.write("ACK");
      Udp.endPacket();
        if (packetSize > 0)
      {
        inputBuffer[packetSize] = 0;
      }
       String dat;
        String command;
        String payload;
        dat = String(inputBuffer);
        command = dat.substring(0,dat.indexOf("%"));
        payload = dat.substring(dat.indexOf("%")+1,dat.length());
        
        Serial.println("Command: " + command);
        Serial.println("Payload: " +payload);


        if (command == "bri"){
          
         BRIGHTNESS=payload.toInt();
         DisplayManager::getInstance().setBrightness(BRIGHTNESS);
        }

        if (command == "settings"){
          int str_len = payload.length() + 1; 
          char char_array[str_len];
          payload.toCharArray(char_array, str_len);
          //AwtrixSettings::getInstance().parseSettings(char_array);
        }
      
    }
    delay(10);
}