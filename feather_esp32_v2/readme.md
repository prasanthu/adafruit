## Adafruit ESP32 Feather V2

### Install Circuit Python
Follow instruction here: https://learn.adafruit.com/adafruit-esp32-feather-v2/circuitpython
- Download Circuit Python : https://circuitpython.org/board/adafruit_feather_esp32_v2/
- Flash this Circuit python image with : https://adafruit.github.io/Adafruit_WebSerial_ESPTool/

### Arduino IDE
prerequisites for Mac: 
- Latest Arduino IDE
- Install CP2104 / CP2102N USB Driver
- Install CH9102 / CH34X USB Driver
- Allow board manager URL for espressif in IDE
- Install the board esp32 in IDE

Now you are ready to follow the example (BLINK) [./Blink.ino]
Port: /dev/cu.wchusbserial575E0745331 (specific to my Mac)

## Adafruit 128x64 OLED FeatherWing

### Install Arudino libs
Follow instructions here: https://learn.adafruit.com/adafruit-128x64-oled-featherwing/arduino-code
- Add "Adafruit SH110x" library to the sketch
- This adds additional libs (including Adafruit GFX)

Now you can run the example code for the display [./OLED_featherwing.ino]

