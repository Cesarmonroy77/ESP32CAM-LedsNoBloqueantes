
/*
 * Encende 4 Leds con ESP32CAM
 * Por: Cesar Monroy
 * Fecha: 28 de junio de 2021
 *
 * Este programa envía datos  por Internet a través del protocolo MQTT, para poder
 * encender el led Flash.
 * Es necesario conectarse a un broker para poder recibir le información.
 * Para que el programa funciones es necesario cambiar el ssid y el password
 * del internet para conectarse por wifi, ademas, se necesita poner la IP, puerto, tema
 * y un id de usuario para poder conectarse al broker deseado.
 * En este programa se usan los leds soldados sobre la placa
 * ESP32CAM, el led flash y el led de status.
 *
 * Componente     PinESP32CAM     Estados lógicos
 * ledStatus------GPIO 33---------On=>LOW, Off=>HIGH
 * ledFlash-------GPIO 4----------On=>HIGH, Off=>LOW
 */

//**************************************
//*********** LIBRERIAS ****************
//**************************************
#include <WiFi.h>  //Libreria para manejar el WiFi del ESP32CAM
#include <PubSubClient.h> //Libreria para manejar MQTT

//**************************************
//*********** OBJETOS ******************
//**************************************
WiFiClient espClient; //Maneja los datos de conexion WiFi
PubSubClient client(espClient); //Maneja los datos de conexion al broker

//**************************************
//*********** GLOBALES   ***************
//**************************************
double timeLast, timeNow; // Variables para el control de tiempo no bloqueante
bool statusLed = 0;// Bandera que me dice si el led de Status esta encendido o apagado

  //**************************************
  //*********** PINES CONFIG *************
  //**************************************
  int ledPin1 = 4;  // Esta variable controla el led de status ubicado en el pin 4
  int ledPin2 = 2;  // Esta variable controla el led de status ubicado en el pin 2
  int ledPin3 = 14;  // Esta variable controla el led de status ubicado en el pin 14
  int ledPin4 = 15;  // Esta variable controla el led de status ubicado en el pin 15

void setup() {
  pinMode (ledPin1, OUTPUT);// Se configura el pin 4 como salida
  pinMode (ledPin2, OUTPUT);// Se configura el pin 2 como salida
  pinMode (ledPin3, OUTPUT);// Se configura el pin 14 como salida
  pinMode (ledPin4, OUTPUT);// Se configura el pin 15 como salida
  timeLast = millis (); // Inicia el control de tiempo
}
void loop() {
  double wait = 1000;  // Espera de 500 mili segundos para consultar conexión
  timeNow = millis ();  // Seguimiento de tiempo
  if (timeNow - timeLast > wait) {
    
  }
}
