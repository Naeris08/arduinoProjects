// --- Variáveis dos Sensores ---
const int PIN_LDR = A0;   // Sensor de luz (LDR no A0)
const int PIN_POT = A1;   // Potenciômetro (Quarto no A1)
int valorLDR = 0;
int valorPot = 0;

// --- Definição dos pinos (Atualizada com Jardim no 6 e Banheiro no 7) ---
const int PIN_SALA = 3;     // LED Verde (Sala) -> Pino 3
const int PIN_COZINHA = 4;  // LED Vermelho (Cozinha) -> Pino 4
const int PIN_QUARTO1 = 5;  // LED Amarelo (Quarto) -> Pino 5 (PWM - Potenciômetro)
const int PIN_JARDIM = 6;   // LED do Jardim -> Pino 6 (PWM - Ajustado pelo LDR)
const int PIN_BANHO1 = 7;   // LED Azul (Banheiro) -> Pino 7

void setup() {
  Serial.begin(9600);
 
  // Configura todos os pinos dos LEDs como saídas
  pinMode(PIN_SALA, OUTPUT);
  pinMode(PIN_COZINHA, OUTPUT);
  pinMode(PIN_QUARTO1, OUTPUT);
  pinMode(PIN_JARDIM, OUTPUT);
  pinMode(PIN_BANHO1, OUTPUT);
 
  // Inicializa todos os LEDs desligados
  digitalWrite(PIN_SALA, LOW);
  digitalWrite(PIN_COZINHA, LOW);
  digitalWrite(PIN_QUARTO1, LOW);
  digitalWrite(PIN_JARDIM, LOW);
  digitalWrite(PIN_BANHO1, LOW);
}

void loop() {
  // --- PARTE 1: Controle do Quarto (LED Amarelo) pelo Potenciômetro ---
  valorPot = analogRead(PIN_POT);
  int brilhoQuarto = map(valorPot, 0, 1023, 0, 255);
  brilhoQuarto = constrain(brilhoQuarto, 0, 255);
  analogWrite(PIN_QUARTO1, brilhoQuarto);

  // --- PARTE 2: Controle de Intensidade Gradual do Jardim pelo LDR ---
  valorLDR = analogRead(PIN_LDR);
 
  // CORREÇÃO AQUI: Mudado para acender na luz e apagar no escuro conforme solicitado
  int brilhoJardim = map(valorLDR, 1023, 0, 255, 0);
  brilhoJardim = constrain(brilhoJardim, 0, 255);
 
  // Aplica o brilho dinâmico no pino 6 (Jardim)
  analogWrite(PIN_JARDIM, brilhoJardim);
 
  // --- PARTE 3: Controle dos Outros Cômodos via Serial ---
  if (Serial.available() > 0) {
    char comando = Serial.read();
   
    if(comando == 'S') {
      // ====== SALA - LED VERDE (Pino 3) ======
      digitalWrite(PIN_SALA, HIGH);// break;
    }
    if (comando == 's'){
      digitalWrite(PIN_SALA, LOW);
    }
    if(comando == 'C') {
      // ====== SALA - LED VERDE (Pino 3) ======
      digitalWrite(PIN_COZINHA, HIGH);// break;
    }
    if (comando == 'c'){
      digitalWrite(PIN_COZINHA, LOW);
    }
    if(comando == 'B') {
      // ====== SALA - LED VERDE (Pino 3) ======
      digitalWrite(PIN_BANHO1, HIGH);// break;
    }
    if (comando == 'b'){
      digitalWrite(PIN_BANHO1, LOW);
    }
    if (comando == 'D'){
      digitalWrite(PIN_BANHO1, LOW);
      digitalWrite(PIN_COZINHA, LOW);
      digitalWrite(PIN_SALA, LOW);
    }
  }
 
  delay(30);
}