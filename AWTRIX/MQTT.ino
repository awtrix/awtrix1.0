#include <ESP8266WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void reconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
      if (mqttClient.connect("AWTRIX", mqttUser, mqttPassword)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void mqttSetup(){

 while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT...");
    mqttClient.setServer(mqttServer, mqttPort);
    mqttClient.setCallback(callback); 
    if (mqttClient.connect("ESP8266Client", mqttUser, mqttPassword )) {
        Serial.println("MQTT Connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(mqttClient.state());
      delay(2000);
    }  
}
    mqttClient.publish("awtrix", "Hello from AWTRIX");
    mqttClient.subscribe("text");
    mqttClient.subscribe("textcolor");
    mqttClient.subscribe("brightness");
    mqttClient.subscribe("awtrix/screencolor");
}

void callback(char* topic, byte* Payload, unsigned int length) {
 String payload;
 for (int i = 0; i < length; i++) {
   payload += (char)Payload[i];
  }
   if (topic == "awtrix/settings"){
    if (payload=="get"){
      sendMSG(loadConfig());
      Serial.println("Send Config");
    }
    else if(payload=="restore")
    {
      restoreSettings();
    }else{      
    int str_len = payload.length() + 1; 
    char char_array[str_len];
    payload.toCharArray(char_array, str_len);
    parsesettings(char_array);
    Serial.println("new Settings recieved");
  }
  }

   
  if (topic == "awtrix/gol"){
    if (payload == "on"){
      gameOfLifeStart();
   }
   if (payload == "off"){
     gameOfLifeStop();
   }
  }

    if (topic == "awtrix/pet"){
    if (payload == "on"){
      gameOfLifeStop();
      PET=true;
   }
   if (payload == "off"){
     PET=false;
   }
  }

      if (topic == "awtrix/mood"){
    PET_MOOD=payload.toInt();
   }

   if (topic == "awtrix/time"){
   if (payload == "on"){
      TIME=true;
    }
   }

   if (topic == "brightness"){
      BRIGHTNESS= payload.toInt();
   }

  if (topic == "text"){
        NOTIFICATION=true;
    int i;
    i = payload.length()*7;
   
     for ( int x=MATRIX_WIDTH ; x >  -i ; x-- ) {
        matrix.clear();
        matrix.setCursor( x, 0 );
        matrix.print(payload);
        matrix.show();
        delay(30);
    }
        NOTIFICATION=false;
  }

     if (topic == "textcolor"){
    mqttClient.publish("awtrix/textcolor", "ACK");
    long number = (long) strtol( &payload[1], NULL, 16);
    int r = number >> 16;
    int g = number >> 8 & 0xff;
    int b = number & 0xff;
    matrix.setTextColor(matrix.Color(r, g, b));
    matrix.show();
}

   if (topic == "screencolor"){
    long number = (long) strtol( &payload[1], NULL, 16);
    int r = number >> 16;
    int g = number >> 8 & 0xff;
    int b = number & 0xff;
    matrix.fillScreen(matrix.Color(r,g,b));
    matrix.show();
}

}

void MQTTloop() {
   if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();
}
