#include <Encoder.h>
#include "Adafruit_VL53L0X.h"
#include <Servo.h>

// Declarar sensor de distancia
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// Pin digital sensor IR
int Pin_IR = 11;
//int posicionActual = 0;

// Pines para el driver del motor
const int motorPin1 = 5;  // Pin de dirección 1
const int motorPin2 = 6;  // Pin de dirección 2
const int motorPinPWM = 9;  // Pin PWM para controlar la velocidad

// Pines para el encoder
const int encoderPinA = 2;  // Pin A del encoder
const int encoderPinB = 3;  // Pin B del encoder

// Configurar el encoder
Encoder myEncoder(encoderPinA, encoderPinB);

// Parámetros de control
int posicion90Grados = (341.2 / 4);  // Posición para 90 grados
int posicion45Grados = (341.2 / 8);  // Posición para 45 grados


void setup() {
  Serial.begin(115200);

  // inicializar pin del IR
  pinMode(Pin_IR, INPUT);

  // inicializar pines del driver
  pinMode(motorPinPWM, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  while (! Serial) {
    delay(1);
  }
  // boot VL53L0X sensor
  Serial.println("Adafruit VL53L0X test.");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power
  Serial.println(F("VL53L0X API Continuous Ranging example\n\n"));

  // start continuous ranging
  lox.startRangeContinuous();
}

void loop() {
  if (lox.isRangeComplete()) {
    float distance = lox.readRange();
    bool IR_sense = digitalRead(Pin_IR);
    int posicionActual = myEncoder.read();  //posición actual del encoder

    if (distance < 80 && posicionActual < posicion90Grados) {
      // Abrir la aguja cuando se acerca un carro
      analogWrite(motorPin1, 255);
      digitalWrite(motorPin2, LOW);
    }
    else if (distance >= 100 && !IR_sense){
      //||
      // Cerrar aguja a velocidad rápida hasta llegar a la mitad
      if (posicionActual > posicion90Grados) {
        digitalWrite(motorPin1, LOW);
        analogWrite(motorPin2, 255);
      }
      else if (posicionActual > posicion45Grados){
        // Continuar cerrando a velocidad lenta hasta llegar a cero
        digitalWrite(motorPin1, LOW);
        analogWrite(motorPin2, 150);
      }
      else{
        // Detener el motor si está en cualqueir otra posición
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, LOW);
      }
    }

    else{
      // Detener el motor si está en cualqueir otra posición
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
    }

    Serial.print("Distancia en mm: ");
    Serial.println(distance);
    Serial.print("Lectura IR: ");
    Serial.println(IR_sense);
    Serial.print("Posicion Actual: ");
    Serial.println(posicionActual);
    Serial.print("90°: ");
    Serial.println(posicion90Grados);
    Serial.print("45°: ");
    Serial.println(posicion45Grados);

    delay(100);

  }
  else {
    Serial.println("¡El sensor está fuera de rango!");
  }
}