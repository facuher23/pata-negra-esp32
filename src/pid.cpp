#include "pid.h"
#include "config.h"

Pid pid;

void Pid::calcular(uint16_t posicionActual, bool estaEnLinea) {
  if (!estaEnLinea) {
    if (errorAnterior > 0) {
      correccion = 255;
    } else {
        correccion = -255;
      }
  pwmSalida = 0; 
  return;
  }

  int error = posicionActual - Config::centro;
  int derivada = error - errorAnterior;
    
  correccion = (kp * error) + (kd * derivada);
  errorAnterior = error;

  float pwmTemporal = pwmBase - abs(error) * kFreno;
    
  if (pwmTemporal < 50.0) { 
    pwmTemporal = 50.0; 
  }
  pwmSalida = (uint8_t)pwmTemporal;
}