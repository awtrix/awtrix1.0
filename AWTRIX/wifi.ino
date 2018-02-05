#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <EEPROM.h>
#include <DNSServer.h>            //Local DNS Server used for redirecting all rs to the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <ESP8266mDNS.h> 

#define MAX_SRV_CLIENTS 3
ESP8266WebServer  server (80);
WiFiClient client;
WiFiUDP Udp;
String IP_ADRESS;

int localUdpPort = 52829;  // local port to listen on
char inputBuffer[512];     // buffer for incoming packets


void wifiSetup() {
    Serial.println("Setup WiFi");
    matrixText(true,"WiFi",5,0,0,0,255);
    WiFiManager wifiManager;
    wifiManager.setTimeout(120);
    wifiManager.autoConnect("AWTRIX");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    IP_ADRESS = WiFi.localIP().toString();
    Serial.println(IP_ADRESS);
    Udp.begin(localUdpPort);
    if (!MDNS.begin("awtrix")) { 
      Serial.println("Error setting up MDNS responder!");
    }
    Serial.println("mDNS responder started");
    if (SHOW_IP_ON_BOOT) {matrixBoot(IP_ADRESS);};
    MDNS.addService("http", "tcp", 80);
    server.begin();
      server.on("/config/set", HTTP_POST, [](){
    StaticJsonBuffer<200> newBuffer;
    JsonObject& newjson = newBuffer.parseObject(server.arg("plain"));

  });
 }

 
void wifiReset() {
    Serial.println("Reset");
    WiFi.disconnect();
    delay(500);
    ESP.reset();
    delay(5000);
}

void udpLoop() {
    int packetSize = Udp.parsePacket();
    if (packetSize) {
     
      Udp.read(inputBuffer, 256);
      Serial.println("Contents:");
      Serial.println(inputBuffer);
      
        if (packetSize > 0)
      {
        inputBuffer[packetSize] = 0;
      }
      doJob(inputBuffer);
    }
    delay(10);
}

void tcpLoop(){
  server.handleClient();
  }


void sendMSG(String msg){

  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Udp.print(msg);
  Udp.endPacket();
}


//LOOP FOR LIVE DRAWING VIA UDP
//void udpLoop() {
//   int size = Udp.parsePacket();
//  if (size > 0) {
//    do
//      {
//        int length = Udp.read(inputBuffer, 512);
//        Serial.printf("UDP packet contents: %s\n", inputBuffer);
//        if (length == 512) {
//          uint16_t *pixels = (uint16_t*) decodeColorData(inputBuffer);
//          Serial.printf("Received %s", pixels);
//          if (pixels) {
//            matrix.drawRGBBitmap(0, 0, pixels, MATRIX_WIDTH, MATRIX_HEIGHT);
//            matrix.show();
//            free(pixels);
//          }
//        }
//        matrix.show();
//      }
//    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
//    Udp.write(replyPacket);
//    Udp.endPacket();
//  }
//}





