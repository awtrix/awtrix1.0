# AWTRIX

### no longer maintained! Have a look for Awtrix 2.0 in my Repos

![AWTRIX Preview](assets/awtrix.jpg?raw=true "AWTRIX")

OFFICIAL DOCUMENTATION:
https://docs.blueforcer.de/#/v1/README



AWTRIX is a smart WiFi-capable clock based on an ESP8266.

- time via NTP server
- current weather via Wonderground API
- Simulation of a virtual "pet" with different emotions 
- Game of Life 
- Youtube Counter
- Facebook Counter
- DHT Senor reading

more functions: 
- Control and configuration via BLYNK
- Display of user-defined texts via MQTT
- Automatic brightness control via LDR
- easy Firmware update via WiFi or Web

The case is designed in Fusion360 and printed in 3D.
You can get the STL-Files from Thingiverse:
https://www.thingiverse.com/thing:2791276

Facebook-Group:
https://www.facebook.com/groups/126493104851075/


## Parts List
https://docs.google.com/document/d/1CAsqT8-JWUTZBSNsxpKQcZtD8DkJ0vUmNQMezy81tLE/edit

## Used Libraries
  Neopixel:https://github.com/adafruit/Adafruit_NeoPixel
  Neomatrix:https://github.com/adafruit/Adafruit_NeoMatrix
  DHT22App:https://platformio.org/lib/show/1671/DHT
  TimeApp & WeatherAPP: https://platformio.org/lib/show/3012/ESP8266%20Weather%20Station
  MQTT: https://platformio.org/lib/show/89/PubSubClient
                        ArduinoCore
                        ESP8266Core
                        ArduinoJson
