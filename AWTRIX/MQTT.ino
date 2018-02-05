#include <ESP8266WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void reconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
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
    mqttClient.publish("awtrix/text", "Hello from ESP8266");
    mqttClient.subscribe("awtrix/text");
}

void callback(char* topic, byte* payload, unsigned int length) {
 Serial.print("Message arrived [");
 Serial.print(topic);
 Serial.print("] ");
  String Payload;
  for (int i = 0; i < length; i++) {
    Payload += (char)payload[i];
    
  }

  Serial.println(Payload);
}

void MQTTloop() {
  mqttClient.loop();
}
