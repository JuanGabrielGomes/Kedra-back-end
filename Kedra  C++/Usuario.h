#ifndef USUARIO_H
#define USUARIO_H

#include <Arduino.h>
#include "FirebaseConnection.h"

class Usuario {
private:
    FirebaseConnection* firebase;
    String id;

public:
    Usuario(FirebaseConnection* firebase);
    void cadastrar(const String& nome, const String& email, const String& senha);
    void deletar(const String& email); // Novo método deletar
    String getId();
};

#endif
