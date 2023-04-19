# USART

 ## Objetivo
 El ejemplo es para recibir mediante comunicacion Serial (USART1) una cadena de caracteres con el formato:
 
***```#xxxxxxxxxxxxxxxxxxx&```***

Es decir, la cadena a recibir debera empezar con el caracter `#` y finalizar con el caracter `&`.
Se agrego una libreria `BufferRing.h` que es el famoso Buffer Circular que permite ir guardando bytes y siempre mantener los ultimos `N` bytes recibidos. Donde `N=30` pero este valor se puede cambiar dentro de la libreria.

## Interrupciones
Se utilizan interrupciones para lograr captar byte a byte a medida que llegan.
El funcionamiento es simple, se inicializa la interrupcion de recepcion una unica vez antes del `while(1)`. Luego cuando llega el primer byte se lanza la interrupcion que permite ir guardando los datos en el buffer. Una vez finalizada la logica de guardado, se vuelve a habilitar la interrupcion de recepcion, permitiendo asi siempre recibir datos por medio de estas interrupciones.

  

## Notas
Se deja dentro del bucle las lineas correspondientes al parpadeo del led, con el fin de dejar en evidencia que el bucle corre correctamente.