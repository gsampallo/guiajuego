/*
 * Demo de como mostrar una imagen en la pantalla oled i2c.
 * Arduino A4 a pantalla Oled SDA
 * Arduino A5 a pantalla Oled SCK
 * Arduino pin A0 a VRx
 * Arduino pin A1 a VRy
 * Arduino D2 a SW
 * 
 * Guillermo Sampallo 
 * https://github.com/gsampallo/guiajuego
 */
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();  

}

// 'spaceship', 48x32px
const unsigned char myBitmap [] PROGMEM = {
  0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x1c, 0x00, 0xe0, 
  0x00, 0x00, 0x00, 0x30, 0x00, 0x30, 0x00, 0x00, 0x00, 0x60, 0x00, 0x18, 0x00, 0x00, 0x00, 0x38, 
  0x00, 0x0c, 0x00, 0x00, 0x00, 0x0c, 0x07, 0xff, 0xc0, 0x00, 0x00, 0x06, 0x7e, 0x00, 0x78, 0x00, 
  0x00, 0x03, 0xc0, 0x00, 0x0e, 0x00, 0x00, 0x06, 0x00, 0x00, 0x07, 0x80, 0x01, 0xfc, 0x00, 0x00, 
  0x04, 0xc0, 0x07, 0x1c, 0x00, 0x1f, 0x04, 0x70, 0x1c, 0x24, 0x00, 0x31, 0xc4, 0x18, 0x30, 0xfc, 
  0x00, 0x60, 0x44, 0x0c, 0x63, 0x04, 0x00, 0x40, 0x64, 0x06, 0x42, 0x04, 0x00, 0x40, 0xa4, 0x02, 
  0x42, 0x04, 0x00, 0x40, 0xa4, 0x06, 0x61, 0x8c, 0x00, 0x41, 0xe4, 0x04, 0x30, 0xfc, 0x00, 0x67, 
  0x44, 0x0c, 0x1c, 0x04, 0x00, 0x31, 0x84, 0x38, 0x07, 0xbc, 0x00, 0x1f, 0x04, 0x60, 0x01, 0xf4, 
  0x00, 0x00, 0x04, 0xc0, 0x00, 0x06, 0x00, 0x00, 0x07, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x1e, 0x00, 
  0x00, 0x06, 0x7f, 0x00, 0xf0, 0x00, 0x00, 0x0c, 0x03, 0xff, 0xc0, 0x00, 0x00, 0x38, 0x00, 0x0c, 
  0x00, 0x00, 0x00, 0x60, 0x00, 0x18, 0x00, 0x00, 0x00, 0x30, 0x00, 0x30, 0x00, 0x00, 0x00, 0x1c, 
  0x00, 0xe0, 0x00, 0x00, 0x00, 0x07, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00
};



void loop() {
  display.clearDisplay(); 

  display.drawBitmap(0, 0, myBitmap,48, 32, WHITE);

  display.display();
  
  delay(50);
}
