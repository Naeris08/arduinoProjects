// C++ code
//
int led = 12;
void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0){
    char comando = Serial.read();
    
    if(comando == 'L' || comando == 'l') {
     digitalWrite(led, HIGH); 
    }
    else if (comando == 'D' || comando == 'd'){
      digitalWrite(led, LOW);
    }
  }
}