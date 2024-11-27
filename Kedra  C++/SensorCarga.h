#ifndef SENSORCARGA_H
#define SENSORCARGA_H

#include <HX711.h>

class SensorCarga {
private:
    HX711 balanca;
    float fatorCalibracao;
    float pesoAtual;

public:
    SensorCarga(int pinDT, int pinSCK, float fatorCalibracao = 2280.0);
    void iniciar();
    float lerPeso();
};

#endif
