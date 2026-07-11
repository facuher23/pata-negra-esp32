#pragma once
#include "config.h"
#include <Arduino.h>
#include <QTRSensors.h>

class Sensores {
public:
  void begin();
  void calibrar();
  void leer();

  uint16_t getPosicion() const {
    return posicion;
  }
  bool estaEnLinea() const {
    return enLinea;
  }

private:
  QTRSensors qtr;
  uint16_t valoresSensores[Config::cantidadSensores];
  uint16_t posicion = 0;
  bool enLinea = true;
};

extern Sensores sensores;