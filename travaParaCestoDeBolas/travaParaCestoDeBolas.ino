#include <Keypad.h>
#include <Servo.h>

const byte LINHAS = 4;
const byte COLUNAS = 4;

char teclas[LINHAS][COLUNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinosLinhas[LINHAS] = {2,3,4,5};
byte pinosColunas[COLUNAS] = {6,7,8,9};

Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);

Servo tranca;

String senhaCorreta = "5632";
String senhaDigitada = "";
String idDigitada = "";

const int led1 = 12;
const int led2 = 13;
const int buzzer = 10;

bool trancaAberta = false;
bool pedindoID = true;
bool idValida = false;

String listaIDs[] = {
 
  "2365"
};
const int qtdIDs = sizeof(listaIDs) / sizeof(listaIDs[0]);

#define MAX_LOG 10
#define LIMITE_REGISTROS 15

String logIDsUtilizadas[MAX_LOG];
int logCount = 0;
void adicionarLog(String id) {
  if (logCount >= LIMITE_REGISTROS) {
    apagarLista();
    logCount = 0;
    Serial.println("Lista de logs apagada após 15 registros.");
  }
  int index = logCount % MAX_LOG;
  logIDsUtilizadas[index] = id;
  logCount++;
}

void apagarLista() {
  for (int i = 0; i < MAX_LOG; i++) {
    logIDsUtilizadas[i] = "";
  }
}

void imprimirLog() {
  Serial.println("IDs usadas:");
  int max = logCount < MAX_LOG ? logCount : MAX_LOG;
  for (int i = 0; i < max; i++) {
    Serial.println(logIDsUtilizadas[i]);
  }
}

bool verificarID(String id) {
  for (int i = 0; i < qtdIDs; i++) {
    if (listaIDs[i] == id) {
      return true;
    }
  }
  return false;
}

void setup() {
  Serial.begin(9600);
  tranca.attach(11);
  tranca.write(40);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  Serial.println("Digite a ID (4 dígitos):");
  // Pota buzzer
  pinMode(buzzer, OUTPUT);
}

void loop() {
  char tecla = teclado.getKey();
  if (!tecla) return;

  Serial.print(tecla);

  if (tecla == 'D') {
    fecharTranca();
    resetSistema();
    return;
  }

  if (tecla == 'A') {
    if (pedindoID) {
      idDigitada = "";
      Serial.println(" - ID apagada");
    } else {
      senhaDigitada = "";
      Serial.println(" - Senha apagada");
    }
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    return;
  }

  if (tecla == 'B') {
    if (pedindoID) {
      if (idDigitada.length() == 4) {
        if (verificarID(idDigitada)) {
          idValida = true;
          pedindoID = false;
          Serial.println("\nID válida. Digite a senha:");
          tone(buzzer,4000,500);
          digitalWrite(led1, HIGH);
          delay(2000);
          digitalWrite(led1,LOW);


          adicionarLog(idDigitada);

          idDigitada = "";
        } else {
          Serial.println("\nID inválida. Tente novamente:");
          tone(buzzer,100,1000);
          for (int i = 0; i < 3; i++) {
            digitalWrite(led2, HIGH);
            delay(300);
            digitalWrite(led2, LOW);
            delay(300);
          }
          idDigitada = "";
        }
      } else {
        Serial.println("\nID incompleta. Digite 4 dígitos:");
        tone(buzzer,100,1000);
        idDigitada = "";
        digitalWrite(led2, HIGH);
        delay(300);
        digitalWrite(led2, LOW);
        delay(300);
      }
    } else {
      if (senhaDigitada == senhaCorreta) {
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
        if (!trancaAberta) abrirTranca();
      } else {
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
        Serial.println("\nSenha incorreta.");
        tone(buzzer,100,500);
      }
      senhaDigitada = "";
    }
    return;
  }

  if (pedindoID) {
    if (idDigitada.length() < 4) {
      idDigitada += tecla;
    }
  } else {
    if (senhaDigitada.length() < 4) {
      senhaDigitada += tecla;
    }
  }
}

void abrirTranca() {
  tranca.write(160);
  trancaAberta = true;
  Serial.println("Tranca aberta");
  tone(buzzer,4000,500);
  Serial.println("Tranca aberta");
  delay (3000);
  tranca.write(40);
  trancaAberta = false;
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  Serial.println("Tranca Fechada");
}

void fecharTranca() {
  tranca.write(160);
  trancaAberta = false;
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  Serial.println("Tranca fechada");
}

void resetSistema() {
  pedindoID = true;
  idValida = false;
  senhaDigitada = "";
  idDigitada = "";
  Serial.println("Digite a ID (4 dígitos):");
  imprimirLog();
}
