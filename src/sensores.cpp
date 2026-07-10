#include <QTRSensors.h>
#include "sensores.h"
#include "motores.h"
#include "config.h"

Sensores sensores; extern QTRSensors qtr; QTRSensors qtr;

void configSensores() {
    qtr.setTypeRC(); qtr.setSensorPins((const uint8_t[]){4, 5, 6, 7, 8, 9, 10, 11},cantidadSensores);
}

void calibrarSensores() {
  rotarEnLugar(80, -80);

  for (uint16_t i = 0; i < 200; i++) {
    qtr.calibrate(); delay(10);
  }
  rotarEnLugar(0, 0); delay(100);
}

void leerSensores() {
  sensores.posicion = qtr.readLineWhite(sensores.valoresSensores);
  sensores.enLinea = false;

  for (int i = 0; i < cantidadSensores; i++) {
    if (sensores.valoresSensores[i] < limitBlanco) { 
      sensores.enLinea = true;
      break;
    }
  }
}