//Proyecto Sensores y Actuadores
//Parte II: Usos del PWM

//PWM MANUAL ------------------------------------------------------------
//Definición de pines
const int Pin_LED = 9; 
const int Pin_potenciometro = 0;
int intensidad;  //variable para la intensidad de brillo

void setup() {
  Serial.begin(9600);
  pinMode (Pin_LED, OUTPUT);  // se declara el LED como salida

}

void loop() {
  // se lee el valor del potenciómetro para regular la intensidad
  // los valores analogicos se usan entre 0 y 255, 
  // por lo que se divide entre 4
  
  intensidad = analogRead (Pin_potenciometro) / 4;
  Serial.println(intensidad);

  // se asigna la salida del LED con el valor analógico del potenciómetro
  analogWrite(Pin_LED, intensidad);

}