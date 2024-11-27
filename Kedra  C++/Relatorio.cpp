#include "Relatorio.h"

Relatorio::Relatorio(FirebaseConnection* firebase) : firebase(firebase) {}

void Relatorio::gerar(const String& usuarioId) {
    String path = "/refeicoes/" + usuarioId;

    if (Firebase.RTDB.get(firebase->getFirebaseData(), path)) {
        FirebaseJson json = firebase->getFirebaseData().jsonObject();
        size_t refeicoesCount = json.iteratorBegin();

        Serial.println("Relatório de Refeições:");
        for (size_t i = 0; i < refeicoesCount; i++) {
            String nomeRefeicao, pathRefeicao;
            json.iteratorGet(i, nomeRefeicao, pathRefeicao);

            Firebase.RTDB.get(firebase->getFirebaseData(), path + "/" + nomeRefeicao + "/quantidade");
            float quantidade = firebase->getFirebaseData().floatData();

            Firebase.RTDB.get(firebase->getFirebaseData(), path + "/" + nomeRefeicao + "/intervalo");
            int intervalo = firebase->getFirebaseData().intData();

            Serial.printf("Refeição: %s\n", nomeRefeicao.c_str());
            Serial.printf("  Quantidade: %.2f gramas\n", quantidade);
            Serial.printf("  Intervalo: %d horas\n", intervalo);
        }

        json.iteratorEnd();
    } else {
        Serial.println("Erro ao gerar relatório. Usuário não encontrado.");
    }
}
