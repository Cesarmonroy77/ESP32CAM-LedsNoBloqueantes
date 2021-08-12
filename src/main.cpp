
/*
 * Encende 4 Leds con ESP32CAM
 * Por: Cesar Monroy
 * Fecha: 09 de agosto de 2021
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
#include "stdio.h"
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
char leds;
int segundos=0,veces=0;

//************************
//****** FUNCIONES *******
//************************
void prender_led(char);
void correr_bits(int);
void correr_bits_inverso(int);

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
  if(veces<=4){
  timeNow = millis ();  // Seguimiento de tiempo
  if (timeNow - timeLast > 1000) {
    if ((segundos%120)<=30) {
      if(segundos%120==0){
        veces++;
        printf("veces: %i\n", veces);
      }
      correr_bits(segundos%20);
    }else{
      correr_bits_inverso((segundos-30)%20);
    }
    segundos++;
    printf("%i\n", segundos);
    printf("Residuo: %i\n", segundos%20);
    prender_led(leds);
    timeLast = millis (); // Inicia el control de tiempo
  }
}else{
  leds=0b00000000;
  prender_led(leds);
}
}

void prender_led(char bits){
  if((bits & 0b00001000)==0b00001000){
    digitalWrite(ledPin1,HIGH);
  }else{
    digitalWrite(ledPin1,LOW);
  }
  if((bits & 0b00000100)==0b00000100){
    digitalWrite(ledPin2,HIGH);
  }else{
    digitalWrite(ledPin2,LOW);
  }
  if((bits & 0b00000010)==0b00000010){
    digitalWrite(ledPin3,HIGH);
  }else{
    digitalWrite(ledPin3,LOW);
  }
  if((bits & 0b00000001)==0b00000001){
    digitalWrite(ledPin4,HIGH);
  }else{
    digitalWrite(ledPin4,LOW);
  }
}
void correr_bits(int s){
  if(s==0){
    leds=0b00001000;
  }else if(s<5){
    leds>>=1; //Secuencia exclusiva ascendente
  }else if(s==5){
    leds=0b00001000;
  }else if(s>5 && s<9){
    leds=((leds>>1)|leds); //Secuencia aditiva ascendente
  }else if(s==9){
    leds=0b00000000;
  }else if(s==10){
    leds=0b00000001;
  }else if(s>10 && s<15){
    leds<<=1; //Secuencia descendente exclusiva
  }else if(s==15){
    leds=0b00000001;
  }else if(s>15 && s<19){
    leds=((leds<<1)|leds); //Secuencia descendente aditiva
  }else if(s==19){
    leds=0b00000000;
  }
}

void correr_bits_inverso(int s){
  if (s==0) {
    leds=0b00000001;
  }else if(s<5){
    leds=((leds<<1)|leds); //Secuencia descendente aditiva
  }else if (s==4) {
    leds=0b00000000;
  }else if (s==5){
    leds=0b00000001;
  }else if (s>5 && s<10) {
    leds<<=1; //Secuencia descendente exclusiva
  }else if(s==10){
    leds=0b00001000;
  }else if(s>10 && s<14){
    leds=((leds>>1)|leds); //Secuencia aditiva ascendente
  }else if (s==14){
    leds=0b00000000;
  }else if (s==15){
    leds=0b00001000;
  }else if (s>15 && s<20) {
    leds>>=1; //Secuencia exclusiva ascendente
  }
}
