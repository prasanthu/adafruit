#include <Adafruit_SH110X.h>
#include <splash.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SHT31.h>

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
Adafruit_SHT31 sht31 = Adafruit_SHT31();

// OLED FeatherWing buttons map to different pins depending on board:

// ADAFRUIT_FEATHER_ESP32_V2
#define BUTTON_A 15
#define BUTTON_B 32
#define BUTTON_C 14

bool enableHeater = false;
uint8_t loopCnt = 0;

void setup() {
  Serial.begin(115200);

  Serial.println("128x64 OLED FeatherWing test");
  delay(250); // wait for the OLED to power up
  display.begin(0x3C, true); // Address 0x3C default

  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);
  resetDisplay();

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  display.display(); // actually display all of the above
  SHT31_Setup();
}

void SHT31_Setup() {
  Serial.println("SHT31 test");
  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }

  Serial.print("Heater Enabled State: ");
  if (sht31.isHeaterEnabled())
    Serial.println("ENABLED");
  else
    Serial.println("DISABLED");

}

void resetDisplay() {
  // Clear the buffer.
  display.clearDisplay();
  display.display();

  display.setRotation(3);
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0,0);
}

void loop() {
  if(!digitalRead(BUTTON_C)) {
    resetDisplay();
  }
  if (loopCnt%4 == 0) {
      resetDisplay();
  }
  SHT31_Loop();
  yield();
  display.display();
  delay(1000);
}

void SHT31_Loop() {
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  if (! isnan(t)) {  // check if 'is not a number'
    display.print("Temp *C = "); display.println(t);
  } else { 
    Serial.println("Failed to read temperature");
  }
  
  if (! isnan(h)) {  // check if 'is not a number'
    display.print("Hum. % = "); display.println(h);
  } else { 
    Serial.println("Failed to read humidity");
  }

  // Toggle heater enabled state every 30 seconds
  // An ~3.0 degC temperature increase can be noted when heater is enabled
  if (loopCnt >= 30) {
    enableHeater = !enableHeater;
    sht31.heater(enableHeater);
    Serial.print("Heater Enabled State: ");
    if (sht31.isHeaterEnabled())
      Serial.println("ENABLED");
    else
      Serial.println("DISABLED");

    loopCnt = 0;
  }
  loopCnt++;
}
