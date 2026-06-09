#include <Servo.h>

Servo meuServo;  // cria um objeto servo
int pinoServo = 11; // pino digital onde o sinal do servo está conectado

void setup() {
  meuServo.attach(pinoServo); // conecta o servo ao pino
}

void loop() {
  // Gira de 0 a 180 graus
  for (int pos = 0; pos <= 180; pos++) {
    meuServo.write(pos);    // define a posição do servo
    delay(15);              // espera para o movimento
  }

  // Gira de 180 a 0 graus
  for (int pos = 180; pos >= 0; pos--) {
    meuServo.write(pos);
    delay(15);
  }
}
