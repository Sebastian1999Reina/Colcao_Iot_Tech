#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <max6675.h>
#include <SHT1x.h>

#include "millisAlbin.h"
#include "printAlbin.h"

#define ARRANQUE_PIN          2
#define SOMAX1_PIN            3
#define CSMAX1_PIN            4
#define SCKMAX1_PIN           5
#define SOMAX2_PIN            6
#define CSMAX2_PIN            7
#define SCKMAX2_PIN           8
#define clockPin              9
#define dataPin               10
#define DATADHT_PIN           11
#define SALIDA_LEDVERDE_PIN   12
#define SALIDA_MOTOR_PIN      13

#define DHTTYPE DHT11

#define TIEMPO_AEROBICO       10000
#define TIEMPO_PRODUCCION     120000

int arranque=0;       //Arranque de Motor
int enclavamiento=0;  //Enclavamiento de Motor
int paro=0;           //Paro del Modor
int estado=0;         //Estado de comprobacion para el arranque
int inicioRBPi;
int motor=0;

myMillis MM;  //Contador para envio de datos
myMillis MM2; //Contador de Inicio del tiempo de fermentacion
myMillis MM3; 
myMillis MM4;
myMillis MM5;


SHT1x sht1x(dataPin, clockPin);

DHT dht(DATADHT_PIN, DHTTYPE);

MAX6675 thermocouple(SCKMAX1_PIN, CSMAX1_PIN, SOMAX1_PIN);
MAX6675 thermocouple2(SCKMAX2_PIN, CSMAX2_PIN, SOMAX2_PIN);

printAlbin printA;

void sensados(){
  
  temp_c = sht1x.readTemperatureC();
  temp_f = sht1x.readTemperatureF();
  humidity = sht1x.readHumidity();
  
  dhth = dht.readHumidity();
  dhtt = dht.readTemperature();
  dhtf = dht.readTemperature(true);
  hif = dht.computeHeatIndex(dhtf, dhth);
  hic = dht.computeHeatIndex(dhtt, dhth, false);

  tempCmax1 = thermocouple.readCelsius();
  tempFmax1 = thermocouple.readFarenheit();
  
  tempCmax2 = thermocouple2.readCelsius();
  tempFmax2 = thermocouple2.readFarenheit();

}
void lecturaSerial(){
  if(Serial.available()>0){  
    int lecturaIA = Serial.read();
    if (lecturaIA == 49){    //SI ES 1 SERIAN 49
      digitalWrite(SALIDA_MOTOR_PIN,HIGH);
      digitalWrite(SALIDA_LEDVERDE_PIN,HIGH);
    }else
    {                       // SI ES 0 EN 48
      digitalWrite(SALIDA_MOTOR_PIN,LOW);
      digitalWrite(SALIDA_LEDVERDE_PIN,LOW);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(ARRANQUE_PIN,INPUT);
  pinMode(SALIDA_LEDVERDE_PIN, OUTPUT);
  //pinMode(SALIDA_LEDROJO_PIN, OUTPUT);
  pinMode(SALIDA_MOTOR_PIN, OUTPUT);
  dht.begin();
  while (MM2.get() <= TIEMPO_AEROBICO)
  {
    
    if(MM3.get() > 10000){
      inicioRBPi=Serial.read();
      if(inicioRBPi==79){
        digitalWrite(SALIDA_LEDVERDE_PIN,1);
        MM2.reset();
      }else{
        digitalWrite(SALIDA_LEDVERDE_PIN,0);
      }
      sensados();
      printA.printDATA();
      
      MM3.reset();
    
    }
  }
delay(10);
      
}

void loop() {

  arranque=digitalRead(ARRANQUE_PIN);
  //paro=digitalRead(PARO_PIN);
  enclavamiento=estado;
  while (MM2.get() > TIEMPO_AEROBICO && MM2.get() < TIEMPO_PRODUCCION)
  {
    lecturaSerial();
    if(arranque==HIGH){//podria ser interrupcion exterma
        digitalWrite(SALIDA_MOTOR_PIN, HIGH);
        digitalWrite(SALIDA_LEDVERDE_PIN, HIGH);
        delay(7000);
        digitalWrite(SALIDA_MOTOR_PIN, LOW);
        digitalWrite(SALIDA_LEDVERDE_PIN, LOW);
    }
   if(MM.get() > 10000){
    lecturaSerial();
    sensados();
    printA.printDATA();
    MM.reset();
    };         
      
  }MM2.reset();

}  
