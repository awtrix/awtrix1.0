#include <AwtrixUDP.h>

char  ReplyBuffer[] = "OK";
String IP_ADRESS;
int localUdpPort = 52829;
char inputBuffer[512];

void AwtrixUDP::setup(){
     Udp.begin(localUdpPort);
}

void AwtrixUDP::sendMSG(String msg){
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Udp.print(msg);
  Udp.endPacket();
}

void AwtrixUDP::loop() {
    int packetSize = Udp.parsePacket();
    if (packetSize) {
      Udp.read(inputBuffer, 512);
      sendMSG("ACK");
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
        DisplayManager::getInstance().setBrightness(payload.toInt());
      }

      if (command== "save"){
          AwtrixSettings::getInstance().saveSettings();
      }

      if (command== "reset"){
          ESP.reset();
      }

      if (command== "mood"){
          PET_MOOD=payload.toInt();
      }

      if (command== "text"){
          DisplayManager::getInstance().scrollText(payload);
      }

      if (command== "next"){
        ApplicationManager::getInstance().nextApplication() ;
      }

     
      if (command == "color"){
        long number = (long) strtol( &payload[1], NULL, 16);
        TEXT_COLOR_R = number >> 16;
        TEXT_COLOR_G = number >> 8 & 0xff;
        TEXT_COLOR_B = number & 0xff;
        DisplayManager::getInstance().setColor({TEXT_COLOR_R,TEXT_COLOR_G,TEXT_COLOR_B});
        }


      if (command == "settings"){
        if (payload=="get"){
           sendMSG(AwtrixSettings::getInstance().loadSettings());
    
          
        }else{
          int str_len = payload.length() + 1; 
          char char_array[str_len];
          payload.toCharArray(char_array, str_len);
          AwtrixSettings::getInstance().parseSettings(char_array);
        }

      }
  sendMSG("ACK");
    }
    delay(10);
}