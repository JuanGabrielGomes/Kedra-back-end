#include "FirebaseConnection.h"

FirebaseConnection::FirebaseConnection(const char* ssid, const char* password, const char* jsonPath)
    : ssid(ssid), password(password), jsonPath(jsonPath) {}

void FirebaseConnection::conectarWiFi() {
    WiFi.begin(ssid, password);
    Serial.println("Conectando ao Wi-Fi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConectado ao Wi-Fi!");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());
}

void FirebaseConnection::configurarFirebase() {
    config.service_account.json.path = jsonPath;
    config.timeout.serverResponse = 10000;
    Firebase.begin(&config, &auth);
    Serial.println("Firebase configurado com sucesso!");
}

FirebaseData& FirebaseConnection::getFirebaseData() {
    return fbdo;
}
