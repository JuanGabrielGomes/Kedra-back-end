#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Servo.h>

class MotorController {
private:
    Servo servo;
    int pin;
    int openAngle;
    int closeAngle;

public:
    MotorController(int pin, int openAngle = 90, int closeAngle = 0);
    void iniciar();
    void abrir();
    void fechar();
};

#endif
