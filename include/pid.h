#pragma once
#include <Arduino.h>

class Pid {
public:
  void calcular(uint16_t posicionActual, bool estaEnLinea);

  int getCorreccion() const { return correccion; }
  uint8_t getPwmSalida() const { return pwmSalida; }

  float getKp() const { return kp; }
  float getKd() const { return kd; }
  float getKFreno() const { return kFreno; }
  int getPwmBase() const { return pwmBase; }

  void setParams(float nkp, float nkd, float nkFreno, int npwmBase) {
    kp = nkp;
    kd = nkd;
    kFreno = nkFreno;
    pwmBase = constrain(npwmBase, 0, 255);
  }

private:
  volatile float kp = 0.02;
  volatile float kd = 0.8;
  volatile float kFreno = 0.04;
  volatile int pwmBase = 120;

  int errorAnterior = 0;
  int correccion = 0;
  uint8_t pwmSalida = 0;
};

extern Pid pid;
