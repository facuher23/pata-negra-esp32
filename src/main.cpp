#include "motores.h"
#include "sensores.h"
#include "pid.h"

void setup() {
  motores.begin();
  configSensores();
  calibrarSensores();
}

void loop() {
  leerSensores();
  calcularPID();
  motores.mover(pid.pwmSalida, pid.correccion);
}