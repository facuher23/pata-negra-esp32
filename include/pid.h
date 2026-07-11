#pragma once
#include <Arduino.h>

class Pid {
public:
    void calcular(uint16_t posicionActual, bool estaEnLinea);

    int getCorreccion() const { return correccion; }
    uint8_t getPwmSalida() const { return pwmSalida; }

private:
    float kp = 0.05;
    float kd = 0.3;
    float kFreno = 0.01;

    int errorAnterior = 0;
    int correccion = 0;
    
    int pwmBase = 200;
    uint8_t pwmSalida = 0;
};

extern Pid pid;