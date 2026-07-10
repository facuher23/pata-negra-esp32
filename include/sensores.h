#pragma once
#include <Arduino.h>
#include "config.h"

struct Sensores {
  uint16_t valoresSensores[cantidadSensores];
  uint16_t posicion = 0;
  bool enLinea = true;
};

extern Sensores sensores;

void leerSensores();
void configSensores();
void calibrarSensores();
void leerSensores();