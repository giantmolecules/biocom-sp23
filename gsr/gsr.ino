// ST77XX Template
// Brett Balogh Spring 2023

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// Use dedicated hardware SPI pins
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

int filterBuffer[20];
int filteredValue = 0;

//int screenBuffer[240];

void setup() {

  // Start serial communications
  Serial.begin(115200);

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
  tft.fillScreen(0x0000);

  // initialize filter buffer
  for (int i = 0; i < 10; i++) {
    filterBuffer[i] = 0;
  }
/*
  // initialize screen buffer
  for (int i = 0; i < 240; i++) {
    filterBuffer[i] = 0;
  }
*/
}

void loop() {

  // shift values in the buffer
  for (int i = 19; i >= 1; i--) {
    filterBuffer[i - 1] = filterBuffer[i];
    //read the analog value from pin 18 (A0)
  }

  filterBuffer[19] = analogRead(18);

  // average values in buffer to get filtered value
  int sum = 0;

  for (int i = 0; i < 20; i++) {
    sum += filterBuffer[i];
  }

  filteredValue = sum / 20.0;

  //for serial plotter
  Serial.print(0);
  Serial.print(",");
  Serial.print(filteredValue);
  Serial.print(",");
  Serial.println(4093);
  delay(100);
/*
  for (int i = 0; i < 240; i++) {
    tft.drawPixel(i, screenBuffer[i], 0x0000);
  }

  // for screen
  for (int i = 239; i >= 1; i--) {
    screenBuffer[i - 1] = screenBuffer[i];
  }

  int mappedValue = map(filteredValue, 0, 4093, 135,0);
  
  screenBuffer[239] = mappedValue;

  for (int i = 0; i < 240; i++) {
    tft.drawPixel(i, screenBuffer[i], 0xFFFF);
  }
*/
}
