#include "Usuario.h"

Usuario::Usuario(FirebaseConnection* firebase) : firebase(firebase) {}

void Usuario::cadastrar(const String& nome, const String& email, const String& senha) {
    id = String(random(10000, 99999)); // Geração de ID único simples
    Firebase.RTDB.setString(firebase->getFirebaseData(), "/usuarios/" + id + "/nome", nome);
    Firebase.RTDB.setString(firebase->getFirebaseData(), "/usuarios/" + id + "/email", email);
    Firebase.RTDB.setString(firebase->getFirebaseData(), "/usuarios/" + id + "/senha", senha);
    Serial.println("Usuário cadastrado com sucesso!");
}

void Usuario::deletar(const String& email) {
    String path = "/usuarios";
    if (Firebase.RTDB.get(firebase->getFirebaseData(), path)) {
        FirebaseJson json = firebase->getFirebaseData().jsonObject();
        FirebaseJsonData result;

        json.toString().toCharArray(buffer, sizeof(buffer));
        Serial.println(buffer);

        if (json.get(result, "/email", email)) {
            // Remove usuário se o e-mail for encontrado
            String idUsuario = result.stringValue;
            Firebase.RTDB.deleteNode(firebase->getFirebaseData(), path + "/" + idUsuario);
            Serial.println("Usuário deletado com sucesso!");
        } else {
            Serial.println("Usuário não encontrado!");
        }
    } else {
        Serial.println("Erro ao acessar usuários no banco de dados.");
    }
}

String Usuario::getId() {
    return id;
}
