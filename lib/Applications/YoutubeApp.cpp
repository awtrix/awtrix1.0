#include <YoutubeApp.h>
#include <ESP8266WiFi.h>
#include <BMP.h>


void YoutubeApp::render(DisplayManager& display) {
     display.drawApp(yt,String(subscribers),{0,0},{255, 255, 255},true,30,200);
}


void YoutubeApp::enable() {
  WiFiClientSecure client;
  if (!client.connect("www.youtube.com", 443)) {
    Serial.println("connection failed");
    
  }
  String cmd = String("GET /youtube/v3/channels?part=statistics&id=") + channelId + "&key=" + apiKey+ " HTTP/1.1\r\n" +
                "Host: " + host + "\r\nUser-Agent: ESP8266/1.1\r\nConnection: close\r\n\r\n";
  client.print(cmd);

  int repeatCounter = 10;
  while (!client.available() && repeatCounter--) {
    delay(500);
  }
  String line,buf="";
  int startJson=0;
  
  while (client.connected() && client.available()) {
    line = client.readStringUntil('\n');
    if(line[0]=='{') startJson=1;
    if(startJson) 
    {
      for(int i=0;i<line.length();i++)
        if(line[i]=='[' || line[i]==']') line[i]=' ';
      buf+=line+"\n";
    }
  }
  client.stop();

  DynamicJsonBuffer jsonBuf;
  JsonObject &root = jsonBuf.parseObject(buf);
  if (!root.success()) {
    Serial.println("parseObject() failed");
    delay(10);
   
  }
  
  subscribers = root["items"]["statistics"]["subscriberCount"];

}


