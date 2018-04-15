#include <TwitterApp.h>
#include <BMP.h>


void TwitterApp::render(DisplayManager& display) {
     display.drawApp(twitter,String(followers),{0,0},{255, 255, 255},true,200);
}

void TwitterApp::enable() {
String payload;
  HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin(String("http://cdn.syndication.twimg.com/widgets/followbutton/info.json?screen_names=")+TWITTER_PROFILE);  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code
      payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
    }
 
    http.end();   //Close connection
    payload.remove(0, 1);
    payload.remove(payload.length() - 1, 1);
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(payload);

      if (root.containsKey("followers_count"))
      {
        followers= root["followers_count"];
    }
    else
    {
      Serial.println("Failed to parse JSON");
    }
jsonBuffer.clear();
}


