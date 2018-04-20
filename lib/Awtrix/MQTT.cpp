#include <MQTT.h>
#include <DisplayManager.h>

long lastReconnectAttempt = 0;

void commands(String topic,String payload){
     if (topic=="awtrix/text"){
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

    mqttClient.publish("awtrix", "Hello from AWTRIX");
    mqttClient.subscribe("awtrix/text");
    mqttClient.subscribe("awtrix/settings");
    mqttClient.subscribe("awtrix/settings/json");
}

bool MQTT::reconnect() {
    if (mqttClient.connect("AWTRIX")) {
        mqttClient.publish("awtrix", "Hello from AWTRIX");
        mqttClient.subscribe("awtrix/text");
        mqttClient.subscribe("awtrix/settings");
        mqttClient.subscribe("awtrix/settings/json");
    }
    return mqttClient.connected();
}

void MQTT::loop() 
{
  if (!mqttClient.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    mqttClient.loop();
  }
}

int MQTT::publish(char* topic, char* payload) {
    mqttClient.publish(topic, payload);
}
