char status = 'D';

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {  
  if(Serial.available()>0){
    char command = Serial.read();
    if (command == 'P'){
      status = 'P';
    }
    if (command == 'L'){
      status = 'L';
    }
    if (command == 'D'){
      status = 'D';
    }

  }
  
  
  if (status == 'D'){
    digitalWrite(13, LOW);
  }
  else if(status == 'L'){
    bool blink = false;
    digitalWrite(13, HIGH);
  }
  else if(status == 'P'){
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
  }
}