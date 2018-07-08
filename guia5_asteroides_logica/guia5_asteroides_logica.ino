/*
 * Regeneracion de asteroides
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
#include "imagenes.h";

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

int listaAsteroides[16][3];
int nroAsteroides = 8;
int nivel = 1;
int asteroides = 0;

int framePorSegundo = 30;
int fps = 1000/framePorSegundo;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay(); 
  generarAsteroides( nroAsteroides,1); 
}



void loop() {
  display.clearDisplay(); 

  for(int i=0;i<nroAsteroides;i++) {

    if(((listaAsteroides[i][0]+16) < 0) && (listaAsteroides[i][1] > 0)) {
      listaAsteroides[i][1] = -1;
      asteroides++;

      if(asteroides == nroAsteroides) {
        asteroides = 0;
        nroAsteroides++;
        generarAsteroides(nroAsteroides,1); 
      }
    } else {

        if(listaAsteroides[i][2] > 4) {
          listaAsteroides[i][2] = 1;
        }
        dibujarAsteroide(listaAsteroides[i][0],listaAsteroides[i][1],listaAsteroides[i][2]);
    
        listaAsteroides[i][2]++;
        listaAsteroides[i][0]--;
      
    }
  }
  delay(fps);
  
  display.display();
  
}

void generarAsteroides(int nroAsteroides,int dificultad) {

  for(int i=0;i<nroAsteroides;i++) {

    if(i == 0) {
      listaAsteroides[i][0] = display.width(); //posicion en x 
    } else {
      listaAsteroides[i][0] = listaAsteroides[(i-1)][0];
      listaAsteroides[i][0] = listaAsteroides[i][0] + (dificultad*16);
    }
    listaAsteroides[i][1] = random(0,32); //posicion en y
    listaAsteroides[i][2] = 1; //imagen a mostrar
    
  }
}

void dibujarAsteroide(int x,int y,int imagen) {
  if(imagen == 1) {
    display.drawBitmap(x, y, asteroide1,16, 16, WHITE);
  } else if(imagen == 2) {
    display.drawBitmap(x, y, asteroide2,16, 16, WHITE);
  } else if(imagen == 3) {
    display.drawBitmap(x,y, asteroide3,16, 16, WHITE);
  } else if(imagen == 4) {
    display.drawBitmap(x,y, asteroide4,16, 16, WHITE);
  }  
}


