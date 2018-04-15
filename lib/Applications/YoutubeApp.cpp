#include <YoutubeApp.h>
#include <ESP8266WiFi.h>
#include <BMP.h>
const size_t bufferSize = JSON_ARRAY_SIZE(1) + 3 * JSON_OBJECT_SIZE(1) + 100;

void YoutubeApp::render(DisplayManager& display) {
     display.drawApp(yt,String(subscribers),{0,0},{255, 255, 255},true,200);
}

void YoutubeApp::enable() {

WiFiClientSecure client;

  Serial.println(host);
  if (!client.connect(host, 443)) {
    Serial.println("connection failed");
  }

   String cmd = String("GET /youtube/v3/channels?part=statistics&id=") + YT_CHANNEL_ID + "&key=" + YT_API_KEY + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\nUser-Agent: ESP8266/1.1\r\nConnection: close\r\n\r\n";
  client.print(cmd);

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }

  /* Now dealing with the body of the response */
  String response = "";
  while (client.available()) {
    char c = client.read();
    response = response + c;
  }
  client.stop();
  DynamicJsonBuffer jsonBuffer(bufferSize);
  JsonObject& root = jsonBuffer.parseObject(response);
  jsonBuffer.clear();
  if (!root.success()) {
    Serial.println("Failed parsing API response");
  }

 subscribers = root["items"][0]["statistics"]["subscriberCount"];
}


