#include <FacebookApp.h>
#include <BMP.h>

void FacebookApp::render(DisplayManager& display) {
     display.drawApp(faceb,String(pageLikes),{0,0},{255, 255, 255},true,200);
}


void FacebookApp::enable() {
    WiFiClientSecure client;
     while (!client.connect(host, httpsPort)) {
    };

    client.verify(FINGERPRINT, host);
   
    client.print(String("GET ") + FB_API_URL + " HTTP/1.1\r\n" + 
                "Host: " + host + "\r\n" + 
                "User-Agent: BuildFailureDetectorESP8266\r\n" + 
                "Connection: close\r\n\r\n"); 

    while (client.connected()) { 
    String line = client.readStringUntil('\n'); 
    if (line == "\r") { 
        break; 
    }} 
    // JSON 
    String line = client.readStringUntil('\n'); 
    DynamicJsonBuffer jsonBuffer; 
    JsonObject& root = jsonBuffer.parseObject(line); 
    pageLikes = root[String("fan_count")]; 
    jsonBuffer.clear();
    client.stopAll();
    root.end();
}



