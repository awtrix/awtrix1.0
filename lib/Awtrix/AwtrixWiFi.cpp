#include <AwtrixWiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <DisplayManager.h>
#include "config.h"
#include <FS.h>
#include <Settings.h>
const int FW_VERSION = 7;
const char* fwUrlBase = "http://blueforcer.de/awtrix/";
File fsUploadFile;

ESP8266WebServer server(80);

const char* html1 = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width,initial-scale=1,maximum-scale=1,minimum-scale=1\"/></head><body style=\"background-color:#EEE;font-family:Arial,Tahoma,Verdana;\"><h1>Title</h1>";
String html2 = "";
String req; 


ESP8266HTTPUpdateServer httpUpdater;

void configModeCallback (WiFiManager *myWiFiManager) {
    DisplayManager::getInstance().drawText("AP", {0, 0}, true,false,false);
    DisplayManager::getInstance().show();
}


void checkForUpdates() {
  String fwURL = String( fwUrlBase );
  String fwVersionURL = fwURL;
  fwVersionURL.concat( "firmware.version" );

  Serial.println(F( "Checking for firmware updates." ));

  Serial.print(F("Firmware version URL: " ));
  Serial.println(fwVersionURL);

  HTTPClient httpClient;
  httpClient.begin( fwVersionURL );
  int httpCode = httpClient.GET();
  if( httpCode == 200 ) {
    String newFWVersion = httpClient.getString();

    Serial.print(F("Current firmware version: " ));
    Serial.println(FW_VERSION );
    Serial.print(F("Available firmware version: " ));
    Serial.println(newFWVersion);

    int newVersion = newFWVersion.toInt();

    if( newVersion > FW_VERSION ) {
      Serial.println(F("Preparing to update"));
      DisplayManager::getInstance().drawText("Update...", {0, 0}, true,true,false);
      DisplayManager::getInstance().show();
      t_httpUpdate_return ret = ESPhttpUpdate.update("http://blueforcer.de/awtrix/firmware.bin");

      switch(ret) {
        case HTTP_UPDATE_FAILED:
          Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
          break;

        case HTTP_UPDATE_NO_UPDATES:
          Serial.println(F("HTTP_UPDATE_NO_UPDATES"));
          break;
      }
    }
    else {
      Serial.println(F("Already on latest version" ));
    }
  }
  else {
    Serial.print(F("Firmware version check failed, got HTTP response code " ));
    Serial.println(httpCode);
  }
  httpClient.end();
}



String getContentType(String filename) {
  if (server.hasArg("download")) {
    return "application/octet-stream";
  } else if (filename.endsWith(".htm")) {
    return "text/html";
  } else if (filename.endsWith(".html")) {
    return "text/html";
  } else if (filename.endsWith(".css")) {
    return "text/css";
  } else if (filename.endsWith(".js")) {
    return "application/javascript";
  } else if (filename.endsWith(".png")) {
    return "image/png";
  } else if (filename.endsWith(".gif")) {
    return "image/gif";
  } else if (filename.endsWith(".jpg")) {
    return "image/jpeg";
  } else if (filename.endsWith(".ico")) {
    return "image/x-icon";
  } else if (filename.endsWith(".xml")) {
    return "text/xml";
  } else if (filename.endsWith(".pdf")) {
    return "application/x-pdf";
  } else if (filename.endsWith(".zip")) {
    return "application/x-zip";
  } else if (filename.endsWith(".gz")) {
    return "application/x-gzip";
  }
  return "text/plain";
}

bool handleFileRead(String path) {
  if (path.endsWith("/")) {
    path += "index.htm";
  }
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {
    if (SPIFFS.exists(pathWithGz)) {
      path += ".gz";
    }
    File file = SPIFFS.open(path, "r");
    server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

void handleFileUpload() {
  if (server.uri() != "/edit") {
    return;
  }
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    if (!filename.startsWith("/")) {
      filename = "/" + filename;
    }
    fsUploadFile = SPIFFS.open(filename, "w");
    filename = String();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    //DBG_OUTPUT_PORT.print("handleFileUpload Data: "); DBG_OUTPUT_PORT.println(upload.currentSize);
    if (fsUploadFile) {
      fsUploadFile.write(upload.buf, upload.currentSize);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (fsUploadFile) {
      fsUploadFile.close();
        AwtrixSettings::getInstance().loadSPIFFS();
        server.send(200, "text/plain", "Änderungen gespeichert!");
    }
  }
}

void handleFileDelete() {
  if (server.args() == 0) {
    return server.send(500, "text/plain", "BAD ARGS");
  }
  String path = server.arg(0);
  if (path == "/") {
    return server.send(500, "text/plain", "BAD PATH");
  }
  if (!SPIFFS.exists(path)) {
    return server.send(404, "text/plain", "FileNotFound");
  }
  SPIFFS.remove(path);
  server.send(200, "text/plain", "");
  path = String();
}

void handleFileCreate() {
  if (server.args() == 0) {
    return server.send(500, "text/plain", "BAD ARGS");
  }
  String path = server.arg(0);
  if (path == "/") {
    return server.send(500, "text/plain", "BAD PATH");
  }
  if (SPIFFS.exists(path)) {
    return server.send(500, "text/plain", "FILE EXISTS");
  }
  File file = SPIFFS.open(path, "w");
  if (file) {
    file.close();
  } else {
    return server.send(500, "text/plain", "CREATE FAILED");
  }
  server.send(200, "text/plain", "");
  path = String();

}

void handleFileList() {
  if (!server.hasArg("dir")) {
    server.send(500, "text/plain", "BAD ARGS");
    return;
  }

  String path = server.arg("dir");
  Dir dir = SPIFFS.openDir(path);
  path = String();

  String output = "[";
  while (dir.next()) {
    File entry = dir.openFile("r");
    if (String(entry.name()).substring(1).indexOf("json") > 1){
    if (output != "[") {
      output += ',';
    }
    bool isDir = false;
    
    output += "{\"type\":\"";
    output += (isDir) ? "dir" : "file";
    output += "\",\"name\":\"";
    output += String(entry.name()).substring(1);
    output += "\"}";
    entry.close();
    }
  }

  output += "]";
  server.send(200, "text/json", output);
}

void setupServer(){
        SPIFFS.begin();
  {
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {
      String fileName = dir.fileName();
      size_t fileSize = dir.fileSize();
    }
  }

server.on("/list", HTTP_GET, handleFileList);
  //load editor
  server.on("/edit", HTTP_GET, []() {
    if (!handleFileRead("/edit.htm")) {
      server.send(404, "text/plain", "FileNotFound");
    }
  });
  //create file
  server.on("/edit", HTTP_PUT, handleFileCreate);
  //delete file
  server.on("/edit", HTTP_DELETE, handleFileDelete);
  //first callback is called after the request has ended with all parsed arguments
  //second callback handles file uploads at that location
  server.on("/edit", HTTP_POST, []() {
    server.send(200, "text/plain", "");
  }, handleFileUpload);

  //called when the url is not defined here
  //use it to load content from SPIFFS
  server.onNotFound([]() {
    if (!handleFileRead(server.uri())) {
      server.send(404, "text/plain", "FileNotFound");
    }
  });

  //get heap status, analog input value and all GPIO statuses in one json call
  server.on("/all", HTTP_GET, []() {
    String json = "{";
    json += "\"FreeRAM\":" + String(ESP.getFreeHeap());
    json += ", \"BrighnessSensor\":" + String(analogRead(A0));
    json += "}";
    server.send(200, "text/json", json);
    json = String();
  });

}

void AwtrixWiFi::setup() {
    Serial.println(F("Setup WiFi"));
    WiFiManager wifiManager;
    wifiManager.setTimeout(120);
    wifiManager.setAPCallback(configModeCallback);

    wifiManager.autoConnect("AWTRIX");

    address = WiFi.localIP().toString();
    Serial.println(F("WiFi connected"));
    Serial.print(F("IP address: "));
    Serial.println(address); 

    if (SHOW_IP_ON_BOOT==1)  DisplayManager::getInstance().scrollText(address);
 
    if (MDNS.begin("AWTRIX")) { 
        Serial.println(F("mDNS responder started"));
        MDNS.addService("http", "tcp", 80);
    } else {
        Serial.println(F("Error setting up MDNS responder!"));
    }


    httpUpdater.setup(&server, "awtrix", "admin"); 
    setupServer();
    server.begin();

    if(AUTO_UPDATE) checkForUpdates();


}



void AwtrixWiFi::loop() {
 server.handleClient();
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
