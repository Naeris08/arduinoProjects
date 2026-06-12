#include <Stepper.h>
#include <Servo.h>

Servo ois;
Servo meuServo;

// Pinos alterados para NÃO dar conflito com o motor de passo (4, 5, 6, 7)
int oi = 9;        // Antes era 7
int servo = 8;     // Antes era 6
int bot = 10;      // Botão no pino 10

const int passosPorVolta = 2048;

// Motor de passo usa os pinos 7, 6, 5 e 4
Stepper meuMotor(passosPorVolta, 7, 6, 5, 4);

void setup() {
  meuServo.attach(servo);
  pinMode(bot, INPUT_PULLUP);
  ois.attach(oi);
  meuMotor.setSpeed(15);
}

void loop() {
  // Como usa INPUT_PULLUP, o botão vira LOW quando é pressionado
  if (digitalRead(bot) == LOW) { 
    meuServo.write(90);  
    ois.write(90);
    meuMotor.step(1024); // Gira meio ambiente (meia volta)
    //delay(15);           // Delay opcional para o servo se mover
  } 
  else {
    meuServo.write(0);  
    ois.write(0);
    meuMotor.step(-1024);
   // delay(15);           // Delay opcional para o servo se mover
  }
}