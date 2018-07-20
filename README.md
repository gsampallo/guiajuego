# Guia para juegos con Arduino Nano

La idea es programar un juego para Arduino, paso a paso donde se puede ir viendo el progreso y el uso de los distintos componentes de hardware y algoritmos en el software.

29-06-2018
**********
guia1_demoDisplayJoystick 

Muestra como conectar la pantalla oled por medio de i2c al arduino nano (tambien se puede aplicar a Arduino UNO), como dibujar una pequeña esfera en la pantalla y controlarla por medio del joystick.

![alt text](https://raw.githubusercontent.com/gsampallo/guiajuego/master/protoboard.png "Esquematico")

[![Video](https://img.youtube.com/vi/HjorjRJRUFs/0.jpg)](https://www.youtube.com/watch?v=HjorjRJRUFs)

30-06-2018
**********
guia2_demoDisplayImagen

De manera sencillo incorporamos graficos mas elaborados en el juego.

![alt text](https://raw.githubusercontent.com/gsampallo/guiajuego/master/procesar_imagenes.png "Imagenes")

Tomamos una imagen preferentemente en blanco y negro, la redimensionamos para que pueda dibujarse completa en la pantalla, y luego utilizando la url http://javl.github.io/image2cpp/ la convertimos en una cadena char pueden ser interpretadas por Arduino.

[![Video](https://img.youtube.com/vi/OMatRmGb0Nk/0.jpg)](https://www.youtube.com/watch?v=OMatRmGb0Nk)

02-07-2018
**********
guia3_demoAnimacionBasica

Un ejemplo de como realizar animaciones con los graficos del juego, de manera de hacerlo mas atractivo.
Las imagenes utilizadas se encuentran en la carpeta "imagenes".

![alt text](https://raw.githubusercontent.com/gsampallo/guiajuego/master/animacion1.png "Animacion")

Intercalamos las imagenes en cada iteracion del juego, cuando llegamos a la ultima volvemos a mostrar la primer imagen del grupo.

[![Video](https://img.youtube.com/vi/XTn7QsnC1Xo/0.jpg)](https://www.youtube.com/watch?v=XTn7QsnC1Xo)

05-07-2018
**********
guia4_asteroides

Trabajamos en un archivo independiente el manejo de los asteroides y de como vamos a ir generandolos en el tiempo antes de integrarlos al juego. Utilizamos la tecnica de la animacion del capitulo anterior, pero le sumamos el movimiento sobre el eje X, de forma que en cada ciclo del juego se acerquen a la nave.

[![Video](https://img.youtube.com/vi/kkq6B8eZpTI/0.jpg)](https://www.youtube.com/watch?v=kkq6B8eZpTI)


08-07-2018
**********
guia5_asteroides_logica

Contamos los asteroides que van pasando y cuando llegamos a la cantidad que generamos, volvemos a generar nuevos asteroides.
Tenemos que tener en cuenta que la funcion drawBitmap (copio tal cual una de las lineas)
	display.drawBitmap(x, y, asteroide2,16, 16, WHITE);
	
Recibe los puntos x,y para dibujar en la pantalla, y el bitmap se extiende hasta (x+16),(y+16); a continuacion un breve esquema.

![alt text](https://raw.githubusercontent.com/gsampallo/guiajuego/master/asteroides.png "Asteroides")


[![Video](https://img.youtube.com/vi/aAHSvF9e9S8/0.jpg)](https://www.youtube.com/watch?v=aAHSvF9e9S8)

16-07-2018
**********
guia6_spaceship

Integramos en el juego a la nave espacial que se puede controlar con el joystick, como lo hicimos en la segunda parte; solo que esta vez esta junto con los asteroides.

[![Video](https://img.youtube.com/vi/SEokz4ttd_4/0.jpg)](https://www.youtube.com/watch?v=SEokz4ttd_4)

17-07-2018
**********
guia7_impactos

Agregamos las colisiones entre los asteroides y la nave, ademas de una animacion para cuando existan impactos.

En la imagen siguiente tenemos los puntos de la nave y de los asteroides, que tenemos que analizara para determinar si existen impactos o no.
![alt text](https://raw.githubusercontent.com/gsampallo/guiajuego/master/posicion.png "Posicion")

Las siguientes son las dos posibilidades de impactos que existen:

![alt text](https://raw.githubusercontent.com/gsampallo/guiajuego/master/impacto.png "Impacto")

Una vez que determinamos que el asteroide entro en la zona de peligro (listaAsteroides[i][1] < (x+24)) y que el asteroide aun esta en la pantalla (listaAsteroides[i][1] > 0) se presentan dos situaciones:
Situacion 1, que el asteroide impacte a la nave por debajo, donde debemos controlar que (y) < listaAsteroides[i][1] y listaAsteroides[i][1] < (y+16)
Situacion 2, el asteroide impacte a la nave por encima, donde debemos controlar que (listaAsteroides[i][1] + 16) > (y) y (listaAsteroides[i][1] + 16) < (y+16)


[![Video](https://img.youtube.com/vi/3CT9MAgIodY/0.jpg)](https://www.youtube.com/watch?v=3CT9MAgIodY)

18-08-2018
**********
guia8_disparos

Se incorpora a la nave la posibilidad de disparar contra los asteroides. Se implementa por medio de un array, donde definimos una cantidad maxima de disparos y vamos recorriendo el array cada vez que debemos dibujarlos en la pantalla. Cuando los disparos que realizamos exceden esa cantidad maxima, se van sobreescribiendo.
Todo se implementa por medio de dos funciones: 

nuevoDisparo(int x,int y) recibe como parametros la posicion (x,y) de la nave, calcula el valor medio, de forma que el disparo salga desde el frente de la nave. Carga en el array el nuevo disparo y su posicion. En caso que exceden los 32 disparos maximos, se sobreescribe el array.
dibubjarDisparos() Se ocupa de recorrer el array y dibujar los disparos en la pantalla.

[![Video](https://img.youtube.com/vi/-ogrUrgD27o/0.jpg)](https://www.youtube.com/watch?v=-ogrUrgD27o)

20-02-2018
**********
guia9_destruir_asteroides

Incluimos la logica para destruir los asteroides. Incorporamos varias funciones para el manejo de las explosiones de los asteroides, empleamos el mismo concepto que para los disparos.

[![Video](https://img.youtube.com/vi/i3VGcISwTac/0.jpg)](https://www.youtube.com/watch?v=i3VGcISwTac)

