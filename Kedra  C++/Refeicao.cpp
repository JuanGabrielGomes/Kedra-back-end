#include "Refeicao.h"

Refeicao::Refeicao(FirebaseConnection* firebase, int servoPin, int doutPin, int sckPin, float calibracaoFator)
    : servoPin(servoPin), doutPin(doutPin), sckPin(sckPin), calibracaoFator(calibracaoFator) {
    this->firebase = firebase;
    servo.attach(servoPin); // Inicializa o servo motor
    balanca.begin(doutPin, sckPin);
    configurarBalanca();
}

void Refeicao::configurarBalanca() {
    balanca.set_scale(calibracaoFator);
    balanca.tare(); // Define o peso inicial como zero
    Serial.println("Célula de carga configurada.");
}

void Refeicao::cadastrar(const String& nome, float quantidade, int intervalo, const String& usuarioId) {
    String path = "/refeicoes/" + usuarioId + "/" + nome;

    FirebaseJson json;
    json.set("quantidade", quantidade);
    json.set("intervalo", intervalo);

    if (Firebase.RTDB.set(firebase->getFirebaseData(), path, json)) {
        Serial.println("Refeição cadastrada com sucesso!");
    } else {
        Serial.println("Erro ao cadastrar refeição.");
    }
}

void Refeicao::deletar(const String& nome, const String& usuarioId) {
    String path = "/refeicoes/" + usuarioId + "/" + nome;

    if (Firebase.RTDB.deleteNode(firebase->getFirebaseData(), path)) {
        Serial.println("Refeição deletada com sucesso!");
    } else {
        Serial.println("Erro ao deletar refeição.");
    }
}

void Refeicao::distribuirAlimento(const String& usuarioId) {
    String path = "/refeicoes/" + usuarioId;

    if (Firebase.RTDB.get(firebase->getFirebaseData(), path)) {
        FirebaseJson json = firebase->getFirebaseData().jsonObject();
        size_t refeicoesCount = json.iteratorBegin();

        for (size_t i = 0; i < refeicoesCount; i++) {
            String nomeRefeicao;
            json.iteratorGet(i, nomeRefeicao);

            // Recuperar dados da refeição
            Firebase.RTDB.get(firebase->getFirebaseData(), path + "/" + nomeRefeicao + "/quantidade");
            float quantidade = firebase->getFirebaseData().floatData();

            Firebase.RTDB.get(firebase->getFirebaseData(), path + "/" + nomeRefeicao + "/intervalo");
            int intervalo = firebase->getFirebaseData().intData();

            // Monitorar peso e controlar o servo
            float pesoAtual = obterPesoAtual();
            if (pesoAtual < quantidade) {
                Serial.println("Distribuindo alimento...");
                servo.write(90); // Abre o servo
                delay(1000); // Tempo para a ração cair

                while (pesoAtual < quantidade) {
                    pesoAtual = obterPesoAtual();
                    Serial.print("Peso atual: ");
                    Serial.println(pesoAtual);
                    delay(500);
                }

                servo.write(0); // Fecha o servo
                Serial.println("Distribuição concluída.");
            }
        }

        json.iteratorEnd();
    } else {
        Serial.println("Erro ao acessar refeições.");
    }
}

float Refeicao::obterPesoAtual() {
    return balanca.get_units(); // Retorna o peso atual em gramas
}
