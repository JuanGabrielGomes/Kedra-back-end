#ifndef RELATORIO_H
#define RELATORIO_H

#include <Arduino.h>
#include "FirebaseConnection.h"

class Relatorio {
private:
    FirebaseConnection* firebase;

public:
    Relatorio(FirebaseConnection* firebase);
    void gerar(const String& usuarioId);
};

#endif
