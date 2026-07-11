#include "pid.h"
#include "sensores.h"
#include "config.h"

Pid pid;

void calcularPID() {
  if (!sensores.enLinea) {
    if (pid.errorAnterior > 0) {
      pid.correccion = 255;
    } else {
      pid.correccion = -255;
    }
    pid.pwmSalida = 0; 
    return;
  }

  int error = sensores.posicion - centro;
  int derivada = error - pid.errorAnterior;
  
  pid.correccion = (pid.kp * error) + (pid.kd * derivada);
  pid.errorAnterior = error;

  float pwmTemporal = pid.pwmBase - abs(error) * pid.kFreno;
  
  if (pwmTemporal < 50.0) { 
    pwmTemporal = 50.0; 
  }

  pid.pwmSalida = (uint8_t)pwmTemporal; 
}