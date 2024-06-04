//Proyecto Sensores y Actuadores
//Parte II: Usos del PWM

//PWM AUTOMATICO ------------------------------------------------------------
// Definición del pin para el LED
const int Pin_LED = 9; 

// Variables para la intensidad del LED
int brillo = 0; // Brillo inicial
int atenuacion = 5; // Cantidad de incremento

void setup() {
  Serial.begin(9600);
  pinMode(Pin_LED, OUTPUT);
}

void loop() {
  // primero ajustamos el brillo del LED
  analogWrite(Pin_LED, brillo);

  // Cambiamos el brillo para la próxima vez
  brillo = brillo + atenuacion;

  // Invertimos la dirección del cambio de brillo al llegar a los límites
  if (brillo <= 0 || brillo >= 255) {
    atenuacion = -atenuacion ;
  }

  // velocidad de la atenuación
  delay(100);
  Serial.println(brillo);
}
