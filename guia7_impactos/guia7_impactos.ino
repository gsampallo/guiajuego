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
int nroAsteroides = 3;
int nivel = 1;
int asteroides = 0;

int duracionDelFrame = 30;
int fps = 1000/duracionDelFrame;

int imageSpaceShip = 1;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay(); 
  generarAsteroides( nroAsteroides,6); 
}

boolean juego = true;
boolean mostrarExplosion = false;

void loop() {
  display.clearDisplay(); 

  int x = 0;
  int ejeY = analogRead(A0);
  int y = map(ejeY,0,1024,0,32);

  if(juego) {

    for(int i=0;i<nroAsteroides;i++) {

      if(((listaAsteroides[i][0]+16) < 0) && (listaAsteroides[i][1] > 0)) {
        listaAsteroides[i][1] = -1;
        asteroides++;

        if(asteroides == nroAsteroides) {
          asteroides = 0;
          nroAsteroides++;
          generarAsteroides(nroAsteroides,6); 
        }
      } else {


        if(existeImpacto(x,y,listaAsteroides[i][0],listaAsteroides[i][1])) {

          mostrarExplosion = true;
          juego = false;
          dibujarExplosion(y);

        } else {
          if(listaAsteroides[i][1] > 0) {
            if(listaAsteroides[i][2] > 4) {
              listaAsteroides[i][2] = 1;
            }
            dibujarAsteroide(listaAsteroides[i][0],listaAsteroides[i][1],listaAsteroides[i][2]);
  
            listaAsteroides[i][2]++;
            listaAsteroides[i][0]--;
          }
          
          if(imageSpaceShip > 3) {
            imageSpaceShip = 1;
          }
          
          dibujarSpaceShip(x,y,imageSpaceShip);
          imageSpaceShip++;

        }

      }


    }
  } else {
    if(mostrarExplosion) {
      dibujarExplosion(y);
    } else {
      gameOver();
    }
  }
  delay(fps);

  display.display();
  
}

boolean existeImpacto(int naveX,int naveY,int asteroideX,int asteroideY) {
  int naveXmax = naveX + 24;
  int naveYmax = naveY + 16;
  int asteroideYmax = asteroideY + 16;

  if((asteroideX < naveXmax) &&  (asteroideX > -16)) {

    if((asteroideY > naveY) && (asteroideY < naveYmax)) {
      return true;
    } else if((asteroideYmax > naveY) && (asteroideYmax < naveYmax)) {
      return true;
    } else {
      return false;
    }
    
  } else {
    return false;
  }
}

int imagenExplosion = 1;
int nroExplosion = 0;
void dibujarExplosion(int y) {
    
    if(imagenExplosion > 4) {
      if(nroExplosion < 2) {
        nroExplosion++;
        imagenExplosion = 1;
      } else {
        imagenExplosion = 1;
        mostrarExplosion = false;
        return;
      }
    }

    if(imagenExplosion == 1) {
      display.drawBitmap(8, y, explosion1,16, 16, WHITE);
    } else if(imagenExplosion == 2) {
      display.drawBitmap(8, y, explosion2,16, 16, WHITE);
    } else if(imagenExplosion == 3) {
      display.drawBitmap(8, y, explosion2,16, 16, WHITE);   
    } 
    imagenExplosion++;   
}


void gameOver() {
    display.clearDisplay(); 
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(8,0);
    display.println("GAME OVER");  
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

void dibujarSpaceShip(int x,int y,int imagen) {
  if(imagen == 1) {
    display.drawBitmap(x, y, spaceship1,24, 16, WHITE);
  } else if(imagen == 2) {
    display.drawBitmap(x, y, spaceship2,24, 16, WHITE);
  } else if(imagen == 3) {
    display.drawBitmap(x,y, spaceship3,24, 16, WHITE);
  }  
}

