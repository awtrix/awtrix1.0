# AWTRIX

![AWTRIX Preview](assets/awtrix.jpg?raw=true "AWTRIX")

AWTRIX is a smart WiFi-capable clock based on an ESP8266.
It supports different modes:
- time via NTP server
- current weather via Wonderground API
- Simulation of a virtual "pet" with different emotions
- Game of Life
- Youtube Counter

more functions:
- Control and configuration via Android app (via UDP)
- Changing the text color
- Display of user-defined texts
- Automatic brightness control via LDR

The case is designed in Fusion360 and printed in 3D.
An 8x32 RGB matrix with WS2812b chipset is used as display.
The code is still in the middle of development and due to my beginnings still very unclean. 
If you want to support me with my project, you can do this very gladly, I am always ready to learn further.

## Parts List
- Wemos D1 Mini (ESP-12E)  
  https://www.amazon.de/AZDelivery-D1-Mini-Entwicklungsboard-kompatibel/dp/B01N9RXGHY/ref=sr_1_1?ie=UTF8&qid=1517707188&sr=8-1&keywords=WeMos
- 8x32 WS2812B RGB Matrix  
  https://www.amazon.de/Quimat-Eingebaute-ansteuerbare-LED-Licht-beleuchtung/dp/B077397WNW/ref=sr_1_4?ie=UTF8&qid=1517707250&sr=8-4&keywords=32x8+rgb
- DC socket  
  https://www.amazon.de/gp/product/B000M0MP2E/ref=oh_aui_detailpage_o00_s01?ie=UTF8&th=1
- DC plug  
  https://www.amazon.de/gp/product/B000L0ZOMI/ref=oh_aui_detailpage_o00_s00?ie=UTF8&th=1
- LDR GL5528  
  https://www.amazon.de/Qualit%C3%A4t-GL5516-Lichtabh%C3%A4ngige-Widerstand-Fotowiderstand/dp/B00NXW9WZ6/ref=sr_1_6?ie=UTF8&qid=1517707354&sr=8-6&keywords=ldr
- Piezo Buzzer  
  https://www.amazon.de/Aktiven-Lautsprecher-Buzzer-Drucker-Arduino/dp/B00KBPQMD8/ref=sr_1_17?s=ce-de&ie=UTF8&qid=1517707398&sr=1-17&keywords=buzzer