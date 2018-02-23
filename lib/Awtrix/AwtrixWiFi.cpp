#include <AwtrixWiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <DisplayManager.h>
const int FW_VERSION = 2;
const char* fwUrlBase = "http://blueforcer.de/awtrix/";
ESP8266HTTPUpdateServer httpUpdater;

void checkForUpdates() {
  String fwURL = String( fwUrlBase );
  String fwVersionURL = fwURL;
  fwVersionURL.concat( "firmware.version" );

  Serial.println( "Checking for firmware updates." );

  Serial.print( "Firmware version URL: " );
  Serial.println( fwVersionURL );

  HTTPClient httpClient;
  httpClient.begin( fwVersionURL );
  int httpCode = httpClient.GET();
  if( httpCode == 200 ) {
    String newFWVersion = httpClient.getString();

    Serial.print( "Current firmware version: " );
    Serial.println( FW_VERSION );
    Serial.print( "Available firmware version: " );
    Serial.println( newFWVersion );

    int newVersion = newFWVersion.toInt();

    if( newVersion > FW_VERSION ) {
      Serial.println( "Preparing to update" );
      DisplayManager::getInstance().drawText("Update...", {0, 5}, {0, 0, 255}, true,true);

      t_httpUpdate_return ret = ESPhttpUpdate.update("http://blueforcer.de/awtrix/firmware.bin");

      switch(ret) {
        case HTTP_UPDATE_FAILED:
          Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
          break;

        case HTTP_UPDATE_NO_UPDATES:
          Serial.println("HTTP_UPDATE_NO_UPDATES");
          break;
      }
    }
    else {
      Serial.println( "Already on latest version" );
    }
  }
  else {
    Serial.print( "Firmware version check failed, got HTTP response code " );
    Serial.println( httpCode );
  }
  httpClient.end();
}


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
     httpUpdater.setup(&webserver);
    webserver.begin();
   

    if (MDNS.begin("AWTRIX")) { 
        Serial.println("mDNS responder started");
        MDNS.addService("http", "tcp", 80);
    } else {
        Serial.println("Error setting up MDNS responder!");
    }
    //checkForUpdates();
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
