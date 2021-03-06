/*
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
int puntaje = 0;
int duracionDelFrame = 30;
int fps = 1000/duracionDelFrame;

int imageSpaceShip = 1;

int listaDisparos[32][3];
int indiceDisparo = 0;

int listaExplosiones[32][3];
int indiceExplosiones = 0;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay(); 
  generarAsteroides(nroAsteroides,6); 
}

boolean juego = true;
boolean mostrarExplosion = false;

unsigned long tiempoRebote = 0;
unsigned long reboteDelay = 50;
int ultimoEstadoBoton2 = LOW;
int botonEstado1;   

void loop() {
  display.clearDisplay(); 

  int x = 0;
  int ejeY = analogRead(A0);
  int y = map(ejeY,0,1024,0,32);
  
  
  /*
  if (estadoBoton1 != ultimoEstadoBoton2) {
    tiempoRebote = millis();
  }
  */
  int estadoBoton1 = LOW;
  if ((millis() - tiempoRebote) > reboteDelay) {
    tiempoRebote = millis();
    estadoBoton1 = digitalRead(3);
    if (estadoBoton1 != ultimoEstadoBoton2) {
      botonEstado1 = estadoBoton1;
    }  
  }
  
  
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
          //Trabajamos con los asteroides
          if(listaAsteroides[i][1] > 0) {
            if(listaAsteroides[i][2] > 4) {
              listaAsteroides[i][2] = 1;
            }

            if(!destruirAsteroide(listaAsteroides[i][0],listaAsteroides[i][1])) {
              dibujarAsteroide(listaAsteroides[i][0],listaAsteroides[i][1],listaAsteroides[i][2]);
    
              listaAsteroides[i][2]++;
              listaAsteroides[i][0]--;
            } else { //se destruye el asteroide
              nuevaExplosion(listaAsteroides[i][0],listaAsteroides[i][1]); //se pasa la ubicacion del asteroide
              listaAsteroides[i][1] = -1;
              
              asteroides++;
              puntaje++;
              
              if(asteroides == nroAsteroides) {
                //se completo el nivel, se tiene que avanzar al proximo
                siguienteNivel();
               
              }
              
            }
          }

          //trabajamos con la nave espacial
          if(imageSpaceShip > 3) {
            imageSpaceShip = 1;
          }
          
          dibujarSpaceShip(x,y,imageSpaceShip);
          imageSpaceShip++;

          //disparos
          
          if(estadoBoton1 == HIGH) { //se efectuo un disparo
            nuevoDisparo(x,y);
          }
          dibubjarDisparos();



          //explosiones
          dibujarExplosiones();

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

void siguienteNivel() {
  nivel++;
  asteroides = 0;
  nroAsteroides++;

  int espacioEntreAsteroides = 6;
  if((nivel%3) == 0) {
    espacioEntreAsteroides--;
  }

  generarAsteroides(nroAsteroides,espacioEntreAsteroides); 
}

void nuevaExplosion(int x,int y) {
  if(indiceExplosiones < 32) {
    listaExplosiones[indiceExplosiones][0] = x; 
    listaExplosiones[indiceExplosiones][1] = y; 
    listaExplosiones[indiceExplosiones][2] = 1; //imagen de la explosion
    indiceExplosiones++;
  } else {
    
    listaExplosiones[0][0] = (x+24); //tomamos el final de la imagen de la nave
    listaExplosiones[0][1] = (y+8); //se busca que el disparo salga de la mitad de la nave   
    listaExplosiones[0][2] = 1;

    for(int i = 31;i>0;i=i-1) {
      listaExplosiones[i][0] = listaExplosiones[(i-1)][0];
      listaExplosiones[i][1] = listaExplosiones[(i-1)][1];    
      listaExplosiones[i][2] = listaExplosiones[(i-1)][2];    
    }

    indiceExplosiones = 0;
    
  }  
}

void dibujarExplosiones() {
  for(int d=0;d<32;d++) {
    if(listaExplosiones[d][2] < 4) {

      listaExplosiones[d][2]++;  

    }  
  }
}



void nuevoDisparo(int x,int y) {
  if(indiceDisparo < 32) {
    listaDisparos[indiceDisparo][0] = (x+24); //tomamos el final de la imagen de la nave
    listaDisparos[indiceDisparo][1] = (y+8); //se busca que el disparo salga de la mitad de la nave
    listaDisparos[indiceDisparo][2] = 1;
    indiceDisparo++;
  } else {
    
    listaDisparos[0][0] = (x+24); //tomamos el final de la imagen de la nave
    listaDisparos[0][1] = (y+8); //se busca que el disparo salga de la mitad de la nave   
    listaDisparos[0][2] = 1;

    for(int i = 31;i>0;i=i-1) {
      listaDisparos[i][0] = listaDisparos[(i-1)][0];
      listaDisparos[i][1] = listaDisparos[(i-1)][1];    
      listaDisparos[i][2] = listaDisparos[(i-1)][2];    
    }

    indiceDisparo = 0;
    
  }
}

void dibubjarDisparos() {
  for(int d=0;d<32;d++) {
    if(listaDisparos[d][0] > 0 && listaDisparos[d][2] == 1) {
      display.drawLine(listaDisparos[d][0],listaDisparos[d][1], (listaDisparos[d][0]+1), listaDisparos[d][1], WHITE);
      listaDisparos[d][0] = listaDisparos[d][0] + 1;          
    }  
  }
}



boolean destruirAsteroide(int asteroideX,int asteroideY) {
  boolean impacto = false;
  for(int d=0;d<32;d++) {
    if(listaDisparos[d][0] > 0 && listaDisparos[d][2] == 1) {
      if(listaDisparos[d][0] == asteroideX) {
        if((listaDisparos[d][1] > asteroideY) && (listaDisparos[d][1] < (asteroideY+16))) {
          listaDisparos[d][2] = 0;
          impacto = true;
          break;
        }       
      }
    }
  }
  return impacto;
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
  
  return false;
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

int imagenAsteroide = 1;

void gameOver() {
    display.clearDisplay(); 
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("GAME OVER");
    display.setCursor(0,15); 
    display.setTextSize(1);
    display.print("SCORE ");
    display.println(puntaje);
}


void generarAsteroides(int nroAsteroides,int dificultad) {

  for(int i=0;i<nroAsteroides;i++) {

    if(i == 0) {
      listaAsteroides[i][0] = display.width(); //posicion en x 
    } else {
      //listaAsteroides[i][0] = listaAsteroides[(i-1)][0];
      //listaAsteroides[i][0] = listaAsteroides[i][0] + (dificultad*16);
      listaAsteroides[i][0] = listaAsteroides[(i-1)][0] + (dificultad*16);
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
