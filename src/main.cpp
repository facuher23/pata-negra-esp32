#include "motores.h"
#include "pid.h"
#include "sensores.h"

void setup() {
  motores.begin();
  sensores.begin();
  sensores.calibrar();
}

void loop() {
  sensores.leer();
  pid.calcular(sensores.getPosicion(), sensores.estaEnLinea());
  motores.mover(pid.getPwmSalida(), pid.getCorreccion());
}