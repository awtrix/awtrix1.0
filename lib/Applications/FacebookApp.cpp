#include <FacebookApp.h>
#include <BMP.h>




void FacebookApp::render(DisplayManager& display) {
    // Called in loop when the app is active. Use GFX functions to display your App.
    // see DisplayManager.h for all possible functions.
    // The following function combines all the calls required to display an app.

    display.drawApp(faceb,String(pageLikes),{0,0},{255, 255, 255},true,200);
    //RGBbmp,text to display,{X,Y Textposition},Textcolor, Autoscroll, scrolldelay (lower=faster), Delay for next scroll
}


void FacebookApp::enable() {
    // Is called up once every time the app is started
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
    }

    } 
    // JSON 
    String line = client.readStringUntil('\n'); 
    DynamicJsonBuffer jsonBuffer; 
    JsonObject& root = jsonBuffer.parseObject(line); 
    pageLikes = root[String("fan_count")]; 
    
    
}



