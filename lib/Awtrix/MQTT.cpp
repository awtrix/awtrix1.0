#include <MQTT.h>
#include <DisplayManager.h>

long lastReconnectAttempt = 0;
        WiFiClient espClient;
PubSubClient mqttClient(espClient);

void MQTT::publish(char* topic, String payload) {
  char copy[payload.length()];
  payload.toCharArray(copy, 50 );
    mqttClient.publish(topic, copy);
}


void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print(F("Message arrived ["));
    Serial.print(topic);
    Serial.print(F("] "));
    String Payload;
    for (int i = 0; i < length; i++) {
        Payload += (char)payload[i];
    }
    

    if (topic == "awtrix/com"){
        String comm = Payload.substring(0,Payload.indexOf("%"));
        String payl = Payload.substring(Payload.indexOf("%")+1,Payload.length());
        AwtrixBroker::getInstance().log("done");
        AwtrixBroker::getInstance().doJob(comm,payl); 
    }
    
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
    mqttClient.subscribe("awtrix/com");
}

bool MQTT::reconnect() {
    if (mqttClient.connect("AWTRIX")) {
        mqttClient.subscribe("awtrix/com");
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
