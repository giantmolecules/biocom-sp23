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

int displayInterval = 5;
int screenInterval = 5;
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

  int analogVal = analogRead(18);

  int averageVal = updateFilterBuffer(analogVal);

  updateScreenBuffer(averageVal);

  updateDisplay();

/*
  if (millis() - lastTime2 > screenInterval) {
    //updateScreenBuffer(analogVal);
    updateScreenBuffer(averageVal);
    lastTime2 = millis();
  }

  if (millis() - lastTime > displayInterval) {
    updateDisplay();
    lastTime = millis();
  }

  if (millis() - lastTime3 > printInterval) {
    printValue(averageVal);
    lastTime3 = millis();
  }
*/


}

int updateFilterBuffer(int val) {

  // shift values in the buffer
  for (int i = 0; i < 19; i++) {
    filterBuffer[i] = filterBuffer[i+1];
    //read the analog value from pin 18 (A0)
  }
  filterBuffer[19] = val;
  int sum = 0;

  for (int i = 0; i < 20; i++) {
    sum += filterBuffer[i];
  }

  filteredValue = sum / 20;
  constrain(filteredValue, 0, 4095);
  return filteredValue;
}

void updateScreenBuffer(int val) {

  for (int i = 0; i < 239; i++) {
    screenBuffer[i] = screenBuffer[i+1];
    //tft.drawPixel(i, screenBuffer[i], ST77XX_WHITE);
  }

  int mappedValue = map(val, 0, 4095, 134, 0);
  
  screenBuffer[239] = mappedValue;

}

void updateDisplay() {

  tft.fillScreen(ST77XX_BLACK);
  for (int i = 0; i < 240; i++) {
    tft.drawPixel(i, screenBuffer[i], ST77XX_WHITE);
  }

}

void printValue(int val) {
  Serial.print(0);
  Serial.print(",");
  Serial.print(val);
  Serial.print(",");
  Serial.println(4095);
}
