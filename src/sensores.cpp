#include "sensores.h"
#include "motores.h"

Sensores sensores;

void Sensores::begin() {
    qtr.setTypeRC();
    qtr.setSensorPins((const uint8_t[]){4, 5, 6, 7, 8, 9, 10, 11}, Config::cantidadSensores);
}

void Sensores::calibrar() {
    motores.rotarEnLugar(80, -80);

    for (uint16_t i = 0; i < 200; i++) {
        qtr.calibrate(); 
        delay(10);
    }
    
    motores.rotarEnLugar(0, 0); 
    delay(100);
}

void Sensores::leer() {
    posicion = qtr.readLineWhite(valoresSensores);
    enLinea = false;

    for (int i = 0; i < Config::cantidadSensores; i++) {
        if (valoresSensores[i] < Config::limitBlanco) { 
            enLinea = true;
            break;
        }
    }
}