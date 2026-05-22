// Sensor ultrassônico
const int trigPin = 6;
const int echoPin = 7;

// LEDs
const int ledVerde = 5;
const int ledVermelho = 13;

// Buzzer
const int buzzer = 11;

// Variáveis
long duracao;
float distancia;

// Notas
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

void tocarStarWars() {

  tone(buzzer, NOTE_A4, 500);
  delay(600);

  tone(buzzer, NOTE_A4, 500);
  delay(600);

  tone(buzzer, NOTE_A4, 500);
  delay(600);

  tone(buzzer, NOTE_F4, 350);
  delay(400);

  tone(buzzer, NOTE_C5, 150);
  delay(200);

  tone(buzzer, NOTE_A4, 500);
  delay(600);

  tone(buzzer, NOTE_F4, 350);
  delay(400);

  tone(buzzer, NOTE_C5, 150);
  delay(200);

  tone(buzzer, NOTE_A4, 650);
  delay(700);

  noTone(buzzer);
}

void setup() {

  // Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // LEDs
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  // Buzzer
  pinMode(buzzer, OUTPUT);

  // Serial
  Serial.begin(9600);

  // Estado inicial
  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledVermelho, LOW);
}

void loop() {

  // Limpa TRIG
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Pulso ultrassônico
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Leitura
  duracao = pulseIn(echoPin, HIGH);

  // Distância
  distancia = duracao * 0.034 / 2;

  // Monitor serial
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Se objeto estiver perto
  if (distancia > 2 && distancia < 10) {

    // Apaga verde
    digitalWrite(ledVerde, LOW);

    // Liga vermelho
    digitalWrite(ledVermelho, HIGH);

    // Toca música
    tocarStarWars();

  } else {

    // Liga verde
    digitalWrite(ledVerde, HIGH);

    // Desliga vermelho
    digitalWrite(ledVermelho, LOW);

    // Desliga buzzer
    noTone(buzzer);
  }

  delay(200);
}