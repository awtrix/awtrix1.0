#include <YoutubeApp.h>
#include <ESP8266WiFi.h>

const char *channelId = "UCpGLALzRO0uaasWTsm9M99w";
static const uint16_t yt[] {0x0, 0xc986, 0xc986, 0xc986, 0xc986, 0xc986, 0xc986, 0x0, 0xc986, 0xc986, 0xc986, 0xffff, 0xc986, 0xc986, 0xc986, 0xc986, 0xc986, 0xc986, 0xc986, 0xffff, 0xffff, 0xc986, 0xc986, 0xc986, 0xc986, 0xc986, 0xc986, 0xffff, 0xffff, 0xffff, 0xc986, 0xc986, 0xc986, 0xc986, 0xc986, 0xffff, 0xffff, 0xffff, 0xc986, 0xc986, 0xc986, 0xc986, 0xc986, 0xffff, 0xffff, 0xc986, 0xc986, 0xc986, 0xc986, 0xc986, 0xc986, 0xffff, 0xc986, 0xc986, 0xc986, 0xc986, 0x0, 0xc986, 0xc986, 0xc986, 0xc986, 0xc986, 0xc986, 0x0 };

void YoutubeApp::update() {
    while (!client.connect("www.youtube.com", 443)){
    };

    client.print(String("GET /channel/") + String(channelId) + "/about HTTP/1.1\r\n" + "Host:www.youtube.com\r\nConnection: close\r\n\r\n");
    int repeatCounter = 5;

    while (!client.available() && repeatCounter--) {
        delay(100);
    }

    int idxS, idxE, statsFound = 0;
    while (client.connected() && client.available()) {
        String line = client.readStringUntil('\n');
        if (statsFound == 0) {
            statsFound = (line.indexOf("about-stats") > 0);
        } else {
            idxS = line.indexOf("<b>");
            idxE = line.indexOf("</b>");
            val = line.substring(idxS + 3, idxE);
          
            client.stop();
           
            break;
        }
    }
}

void YoutubeApp::render(DisplayManager& display) {
     display.drawApp(yt,val,{0,0},{255, 255, 255},false,true,30,200);
}
