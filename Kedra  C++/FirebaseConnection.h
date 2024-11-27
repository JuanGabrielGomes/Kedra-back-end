#ifndef FIREBASE_CONNECTION_H
#define FIREBASE_CONNECTION_H

#include <WiFi.h>
#include <Firebase_ESP_Client.h>

class FirebaseConnection {
private:
    FirebaseData fbdo;
    FirebaseAuth auth;
    FirebaseConfig config;
    const char* ssid;
    const char* password;
    const char* jsonPath;

public:
    FirebaseConnection(const char* ssid, const char* password, const char* jsonPath);
    void conectarWiFi();
    void configurarFirebase();
    FirebaseData& getFirebaseData();
};

#endif
