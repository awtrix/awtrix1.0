#include <FacebookApp.h>


static const uint16_t faceb[] {0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0xffff, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0xffff, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0xffff, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0xffff, 0xffff, 0xffff, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0xffff, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0xffff, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0x3ad3, 0xffff, 0x3ad3, 0x3ad3, 0x3ad3 };

//8x8 RGB Bitmap. Use AWTRIX BMPdrawer to easily create a bitmap (https://github.com/Blueforcer/AWTRIX/tree/master/BMPdrawer)


void FacebookApp::render(DisplayManager& display) {
    // Called in loop when the app is active. Use GFX functions to display your App.
    // see DisplayManager.h for all possible functions.
    // The following function combines all the calls required to display an app.

    display.drawApp(faceb,String(pageLikes),{0,0},{255, 255, 255},true,30,200);
    //RGBbmp,text to display,{X,Y Textposition},Textcolor, Autoscroll, scrolldelay (lower=faster), Delay for next scroll
}


void FacebookApp::enable() {
    // Is called up once every time the app is started
}


void FacebookApp::update() {
    // Is called after "UpdateThreshold". Here you can fetch your nessesary data
    while (!client.connect(host, httpsPort)){
    };

    if (client.verify(fingerprint, host)) { 
    Serial.println("certificate matches"); 
    } else { 
    Serial.println("certificate doesn't match"); 
    } 
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + 
                "Host: " + host + "\r\n" + 
                "User-Agent: BuildFailureDetectorESP8266\r\n" + 
                "Connection: close\r\n\r\n"); 
    Serial.println("request sent"); 
    while (client.connected()) { 
    String line = client.readStringUntil('\n'); 
    if (line == "\r") { 
        Serial.println("headers received"); 
        break; 
    } 
    } 
    // JSON 
    String line = client.readStringUntil('\n'); 
    DynamicJsonBuffer jsonBuffer; 
    JsonObject& root = jsonBuffer.parseObject(line); 
    pageLikes = root[String("fan_count")]; 
 
}
