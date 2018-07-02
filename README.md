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