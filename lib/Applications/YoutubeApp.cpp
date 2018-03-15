#include <YoutubeApp.h>
#include <ESP8266WiFi.h>
#define target_time 5000

static const uint16_t yt[] {0x0, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0x0, 0xf800, 0xf800, 0xf800, 0xffff, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xffff, 0xffff, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xffff, 0xffff, 0xffff, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xffff, 0xffff, 0xffff, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xffff, 0xffff, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xffff, 0xf800, 0xf800, 0xf800, 0xf800, 0x0, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0xf800, 0x0 };

void YoutubeApp::update() {
    while (!client1.connect("www.youtube.com", 443)&& (long) (millis() - target_time) < 0){
    };

    client1.print(String("GET /channel/") + channelId + "/about HTTP/1.1\r\n" + "Host:www.youtube.com\r\nConnection: close\r\n\r\n");
    int repeatCounter = 5;


    int idxS, idxE, statsFound = 0;
    while (client1.connected() && client1.available()) {
        String line = client1.readStringUntil('\n');

            idxS = line.indexOf("<b>");
            idxE = line.indexOf("</b>");
            val = line.substring(idxS + 3, idxE);
            line="";
            client1.flush();
            client1.stopAll();
           
            break;
        
    }
}

void YoutubeApp::render(DisplayManager& display) {
     display.drawApp(yt,val,{0,0},{255, 255, 255},true,30,200);
}
