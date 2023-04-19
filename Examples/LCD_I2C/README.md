# Comunicacion I2C

El ejemplo es para una Pantalla LCD de 20x4 o 16x2, que utiliza el adaptador i2C (PCF8574A).

***```#define  DEVICE_ADDR (0x3D  <<  1)```***

Se agrego una libreria `PCF8574.h` para unicamente colocar la direccion de este modulo y utilizar sus funciones.

Ademas, tambien se adjunta el Datasheet de este tipo de pantallas. Es en este datasheet donde se encuentran las tablas con los bits que deberan tener las lineas de datos para entrar en sus distintos modos de funcionamiento.

# Notas
Para estas pruebas se utilizo el I2C en modo Fast I2C (400Khz) y el lcd se comporto de forma correcta.