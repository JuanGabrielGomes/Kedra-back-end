#include <Arduino.h>
#include "FirebaseConnection.h"
#include "Usuario.h"
#include "Refeicao.h"
#include "Relatorio.h"

const char* ssid = "SEU_SSID";
const char* password = "SUA_SENHA";
const char* jsonPath = "/path/to/kedra-pet-service-account.json";

const int servoPin = 9;  // Pino do servo motor
const int doutPin = 3;   // Pino de dados da célula de carga
const int sckPin = 2;    // Pino de clock da célula de carga
const float calibracaoFator = 1100.0; // Fator de calibração

FirebaseConnection* firebase;
Usuario* usuario;
Refeicao* refeicao;
Relatorio* relatorio;

void setup() {
    Serial.begin(115200);

    firebase = new FirebaseConnection(ssid, password, jsonPath);
    firebase->conectarWiFi();
    firebase->configurarFirebase();

    usuario = new Usuario(firebase);
    refeicao = new Refeicao(firebase, servoPin, doutPin, sckPin, calibracaoFator);
    relatorio = new Relatorio(firebase);

    usuario->cadastrar("João Silva", "joao@email.com", "123456");
    String usuarioId = usuario->getId();

    refeicao->cadastrar("Café da Manhã", 200.0, 2, usuarioId);
    refeicao->cadastrar("Almoço", 500.0, 4, usuarioId);

    relatorio->gerar(usuarioId);
}

void loop() {
    String usuarioId = usuario->getId();
    refeicao->distribuirAlimento(usuarioId);
    delay(1000); // Evita execuções contínuas
}
