#include <AwtrixWiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>

void AwtrixWiFi::setup() {
    Serial.println("Setup WiFi");
    // matrixText(true, "WiFi", 5, 0, 0, 0, 255);
    WiFiManager wifiManager;
    wifiManager.setTimeout(120);
    wifiManager.autoConnect("AWTRIX");

    address = WiFi.localIP().toString();
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(address);

    if (false) { // SHOW_IP_ON_BOOT
        // matrixBoot(address);
    }
    
    if (MDNS.begin("awtrix")) { 
        Serial.println("mDNS responder started");
        MDNS.addService("http", "tcp", 80);
    } else {
        Serial.println("Error setting up MDNS responder!");
    }
}

void AwtrixWiFi::loop() {
    webserver.handleClient();
}

/*
void wifiReset() {
    Serial.println("Reset");
    WiFi.disconnect();
    delay(500);
    ESP.reset();
    delay(5000);
}

void udpLoop() {
    int size = udp.parsePacket();
    if (size > 0) {
        do
        {
            int length = udp.read(inputBuffer, 512);
            Serial.printf("UDP packet contents: %s\n", inputBuffer);
            if (length == 512) {
                uint16_t *pixels = (uint16_t*) decodeColorData(inputBuffer);
                Serial.printf("Received %s", pixels);
                if (pixels) {
                    matrix.drawRGBBitmap(0, 0, pixels, MATRIX_WIDTH, MATRIX_HEIGHT);
                    matrix.show();
                    free(pixels);
                }
            }
            matrix.show();
        }
        udp.beginPacket(udp.remoteIP(), udp.remotePort());
        udp.write(replyPacket);
        udp.endPacket();
    }
}
*/
