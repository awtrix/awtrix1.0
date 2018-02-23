#include <YoutubeApp.h>
#include <ESP8266WiFi.h>

const char *channelId = "UCpGLALzRO0uaasWTsm9M99w";
static unsigned char play[]={0x00,0x00,0x10,0x18,0x1c,0x18,0x10,0x00}; // Bitmap Playsymbol
static unsigned char rond[]={0x00,0x7e,0xff,0xff,0xff,0xff,0xff,0x7e}; // Bitmap Round Icon

void YoutubeApp::update() {
    if (!client.connect("www.youtube.com", 443)) {
        // ...
    }

    client.print(String("GET /channel/") + String(channelId) + "/about HTTP/1.1\r\n" + "Host:www.youtube.com\r\nConnection: close\r\n\r\n");
    int repeatCounter = 10;

    while (!client.available() && repeatCounter--) {
        Serial.println("Get SubCounter"); delay(300);
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
    display.drawBitmap(rond, {0, 0}, {255, 0, 0}, 8, 8);
    display.drawBitmap(play, {0, 0}, {255, 255, 255}, 8, 8);
    display.drawText(val, {9, 0}, {200, 50, 0}, false, false);
}
