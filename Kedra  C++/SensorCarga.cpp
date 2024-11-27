#include "SensorCarga.h"

SensorCarga::SensorCarga(int pinDT, int pinSCK, float fatorCalibracao)
    : fatorCalibracao(fatorCalibracao), pesoAtual(0) {
    balanca.begin(pinDT, pinSCK);
}

void SensorCarga::iniciar() {
    balanca.set_scale(fatorCalibracao);
    balanca.tare(); // Reseta o peso inicial para zero
}

float SensorCarga::lerPeso() {
    pesoAtual = balanca.get_units();
    return pesoAtual;
}
