#include "MotorController.h"

MotorController::MotorController(int pin, int openAngle, int closeAngle)
    : pin(pin), openAngle(openAngle), closeAngle(closeAngle) {}

void MotorController::iniciar() {
    servo.attach(pin);
    fechar(); // Garante que o servo começa fechado
}

void MotorController::abrir() {
    servo.write(openAngle);
    delay(1000); // Aguarda para o movimento completo
}

void MotorController::fechar() {
    servo.write(closeAngle);
    delay(1000); // Aguarda para o movimento completo
}
