// ST77XX Template
// Brett Balogh Spring 2023

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// Use dedicated hardware SPI pins
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

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
  
}

void loop() {
  int value = analogRead(18);
  Serial.println(value);
  delay(100);
}
