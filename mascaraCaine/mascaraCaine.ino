#include <Servo.h>

// C++ code
//
Servo ois;
Servo meuServo;
int oi = 7;
int servo = 6;
int bot = 10;

void setup()
{
  meuServo.attach(servo);
  pinMode(bot, INPUT_PULLUP);
  ois.attach(oi);
}

void loop()
{
	if(digitalRead(bot) != HIGH){
   		meuServo.write(180);  // Comanda o servo para ir para a posição atual
    	ois.write(180);
      	delay(15);                // Aguarda 15 milissegundos para o servo alcançar a posição
  		
  	}
  	else{
    	meuServo.write(0);  // Comanda o servo para ir para a posição atual
    	ois.write(0);
      	delay(15);
    }
}
