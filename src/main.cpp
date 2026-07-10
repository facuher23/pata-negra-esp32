#include "motores.h"
#include "sensores.h"
#include "pid.h"

void setup() {
  configMotores();
  configSensores();
  calibrarSensores();
}

void loop() {
  leerSensores();
  calcularPID();
  moverMotores();
}