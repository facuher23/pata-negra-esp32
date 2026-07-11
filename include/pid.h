#pragma once
#include <Arduino.h>

struct Pid {
    float kp = 0.05;
    float kd = 0.3;
    float kFreno = 0.01;

    int errorAnterior = 0;
    int correccion = 0;
    
    int pwmBase = 200;
    int pwmSalida = 0; 
};

extern Pid pid;

void calcularPID();