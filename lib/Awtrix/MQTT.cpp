#include <MQTT.h>
#include <DisplayManager.h>
#include <Settings.h>

AwtrixSettings& settings1 = AwtrixSettings::getInstance();


void commands(String topic,String payload){
  if (topic=="awtrix/settings/json"){
        settings1.parseSettings(payload);
    }

     if (topic=="text"){
        DisplayManager::getInstance().scrollText(payload);
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
    while (!mqttClient.connected()) {
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
    

}

int MQTT::publish(char* topic, char* payload) {
    mqttClient.publish(topic, payload);
}

/*
void reconnect() {
    // Loop until we're reconnected
    while (!mqttClient.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        // If you do not want to use a username and password, change next line to
        // if (client.connect("ESP8266Client")) {
        //if (mqttClient.connect("AWTRIX", mqttUser, mqttPassword)) {
        //    Serial.println("connected");
        //} else {
            Serial.print("failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        //}
    }
}
*/
