#include "pid.h"
#include "config.h"

Pid pid;

void Pid::calcular(uint16_t posicionActual, bool estaEnLinea) {
  if (!estaEnLinea) {
    correccion = (errorAnterior > 0) ? 255 : -255;
    pwmSalida = 0;
    return;
  }

  int base = pwmBase;
  int error = (int)posicionActual - Config::centro;
  int derivada = error - errorAnterior;

  correccion = constrain((int)((kp * error) + (kd * derivada)), -base, base);
  errorAnterior = error;

  float pwmTemporal = base - abs(error) * kFreno;
  if (pwmTemporal < 50.0) pwmTemporal = 50.0;
  if (pwmTemporal > 255.0) pwmTemporal = 255.0;
  pwmSalida = (uint8_t)pwmTemporal;
}
