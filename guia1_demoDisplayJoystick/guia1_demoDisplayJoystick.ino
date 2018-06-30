/*
 * Demo de la pantalla oled i2c con el joystick. Mueve una esfera segun la posicion que indica el joystick.
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

int i = 1;

void loop() {

  display.clearDisplay();

  int posicionX = analogRead(A0);
  int posicionY = analogRead(A1);

  int x = map(posicionX, 0, 1024, 0, 128);
  int y = map(posicionY, 0, 1024, 0, 32);

  display.drawCircle(x, y, 6, WHITE);

  display.display();
  delay(10);
}
