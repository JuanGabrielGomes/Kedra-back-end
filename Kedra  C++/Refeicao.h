#ifndef REFEICAO_H
#define REFEICAO_H

#include <Arduino.h>
#include "FirebaseConnection.h"
#include <Servo.h>           // Biblioteca para controle do servo motor
#include "HX711.h"           // Biblioteca para célula de carga

class Refeicao {
private:
    FirebaseConnection* firebase;
    Servo servo;             // Objeto para o servo motor
    HX711 balanca;           // Objeto para a célula de carga
    int servoPin;            // Pino do servo motor
    int doutPin;             // Pino de dados da célula de carga
    int sckPin;              // Pino de clock da célula de carga
    float calibracaoFator;   // Fator de calibração da célula de carga

public:
    // Construtor
    Refeicao(FirebaseConnection* firebase, int servoPin, int doutPin, int sckPin, float calibracaoFator);

    // Métodos
    void configurarBalanca();  // Configura a célula de carga
    void cadastrar(const String& nome, float quantidade, int intervalo, const String& usuarioId);
    void deletar(const String& nome, const String& usuarioId);
    void distribuirAlimento(const String& usuarioId); // Controla o servo e a célula de carga para distribuir alimento

    // Funções auxiliares
    float obterPesoAtual();  // Obtém o peso atual na célula de carga
};

#endif
