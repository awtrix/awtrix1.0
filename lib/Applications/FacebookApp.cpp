#include <FacebookApp.h>
#define target_time 5000

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
    while (!client.connect(host, httpsPort) && (long) (millis() - target_time) < 0){
    };

    client.verify(fingerprint, host);
   
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + 
                "Host: " + host + "\r\n" + 
                "User-Agent: BuildFailureDetectorESP8266\r\n" + 
                "Connection: close\r\n\r\n"); 

    while (client.connected()) { 
    String line = client.readStringUntil('\n'); 
    if (line == "\r") { 

        break; 
    } 
    } 
    // JSON 
    String line2 = client.readStringUntil('\n'); 
    DynamicJsonBuffer jsonBuffer; 
    JsonObject& root = jsonBuffer.parseObject(line2); 
    pageLikes = root[String("fan_count")]; 
    jsonBuffer.clear();
    client.flush();
    client.stopAll();
}


