#include <MQTT.h>
#include <DisplayManager.h>
#include <Settings.h>

AwtrixSettings& settings1 = AwtrixSettings::getInstance();
#define target_time 5000

void commands(String topic,String payload){
  if (topic=="awtrix/settings/json"){
        settings1.parseSettings(payload);
    }

     if (topic=="awtrix/text"){
        DisplayManager::getInstance().scrollText(payload);
    }

    if (topic=="awtrix/app"){

        //DisplayManager::getInstance().drawApp(twitter,payload,{0,0},{255, 255, 255},true,200);;
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print(F("Message arrived ["));
    Serial.print(topic);
    Serial.print(F("] "));
    String Payload;
    for (int i = 0; i < length; i++) {
        Payload += (char)payload[i];
    }
    commands(topic,Payload);
}




void MQTT::setup() {
    if (MQTT_SERVER=="") return;
    while (!mqttClient.connected())  {
        Serial.println(F("Connecting to MQTT..."));
        mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
        mqttClient.setCallback(callback);

        if (mqttClient.connect("AWTRIX", MQTT_USERNAME, MQTT_PASSWORD)) {
            Serial.println(F("MQTT Connected"));
        } else {
            Serial.print(F("failed with state "));
            Serial.print(mqttClient.state());
            delay(300);
        }
    }

    mqttClient.publish("awtrix/message", "Hello from AWTRIX");
    mqttClient.subscribe("awtrix/text");
    mqttClient.subscribe("awtrix/settings");
    mqttClient.subscribe("awtrix/settings/json");
}

void MQTT::reconnect() {
    // Loop until we're reconnected
    while (!mqttClient.connected())  {
      Serial.println(F("Connecting to MQTT..."));
        mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
        mqttClient.setCallback(callback);

        if (mqttClient.connect("AWTRIX", MQTT_USERNAME, MQTT_PASSWORD)) {
            Serial.println(F("MQTT Connected"));
        } else {
            Serial.print(F("failed with state "));
            Serial.print(mqttClient.state());
            delay(100);
        }
    }

    mqttClient.publish("awtrix/message", "Hello from AWTRIX");
    mqttClient.subscribe("awtrix/text");
    mqttClient.subscribe("awtrix/settings");
    mqttClient.subscribe("awtrix/settings/json");
    }


void MQTT::loop() {

    mqttClient.loop();

}

int MQTT::publish(char* topic, char* payload) {
    mqttClient.publish(topic, payload);
}




