#include <AwtrixWiFi.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h> 

AwtrixWiFi::AwtrixWiFi() : webserver(80) {
    // ...
}

void AwtrixWiFi::setup() {
    Serial.println("Setup WiFi");
    // matrixText(true, "WiFi", 5, 0, 0, 0, 255);
    WiFiManager wifiManager;
    wifiManager.setTimeout(120);
    wifiManager.autoConnect("AWTRIX");

    Serial.println("WiFi connected");
    Serial.println("IP address: ");

    address = WiFi.localIP().toString();
    Serial.println(address);
    udp.begin(52829);   // TODO: Define this somewhere else

    if (!MDNS.begin("awtrix")) { 
        Serial.println("Error setting up MDNS responder!");
    }

    Serial.println("mDNS responder started");
    if (false) { // SHOW_IP_ON_BOOT
        // matrixBoot(address);
    }
        
    MDNS.addService("http", "tcp", 80);
}

void AwtrixWiFi::loop() {
    udpLoop();
    tcpLoop();
}

void AwtrixWiFi::udpLoop() {
    int packetSize = udp.parsePacket();
    char inputBuffer[512];

    if (packetSize) {
        udp.read(inputBuffer, 255);
        Serial.println("Contents:");
        Serial.println(inputBuffer);

        if (packetSize > 0) {
            inputBuffer[packetSize] = 0;
        }

        // doJob(inputBuffer);
    }
}

void AwtrixWiFi::tcpLoop() {
    webserver.handleClient();
}



void wifiReset() {
    Serial.println("Reset");
    WiFi.disconnect();
    delay(500);
    ESP.reset();
    delay(5000);
}

void sendMSG(String msg) {
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
