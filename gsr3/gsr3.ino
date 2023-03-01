// ST77XX Template
// Brett Balogh Spring 2023

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// Use dedicated hardware SPI pins
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

int filterBuffer[20];

int filteredValue = 0;

int screenBuffer[240];

int counter = 0;

int lastTime = 0;
int lastTime2 = 0;
int lastTime3 = 0;

int displayInterval = 1000;
int screenInterval = 1000;
int printInterval = 100;

void setup() {

  // Start serial communications
  Serial.begin(115200);
  Serial.println("Entering Setup...");

  // turn on backlite
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  // turn on the TFT / I2C power supply
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);

  // initialize TFT
  tft.init(135, 240); // Init ST7789 240x135

  // Set screen rotation. 3=landscape with usb to the left
  tft.setRotation(3);

  // Fill screen with a color. Can use hex rgb values
  tft.fillScreen(ST77XX_BLACK);

  // initialize filter buffer
  for (int i = 0; i < 10; i++) {
    filterBuffer[i] = 0;
  }

  // initialize screen buffer
  for (int i = 0; i < 240; i++) {
    screenBuffer[i] = 0;
  }

  lastTime = millis();
}

void loop() {

  int analogValue = analogRead(18);

  int mappedValue = map(analogValue, 0, 4095, 134, 0);

  screenBuffer[counter] = mappedValue;

  tft.drawPixel(counter, screenBuffer[counter], ST77XX_WHITE);

  if (counter >= 240) {
    tft.fillScreen(ST77XX_BLACK);
    counter = 0;
  }
  else{
    counter++;
  }
  delay(10);
}

void printValues(int val) {
  Serial.print(0);
  Serial.print(",");
  Serial.print(val);
  Serial.print(",");
  Serial.println(4095);
}
