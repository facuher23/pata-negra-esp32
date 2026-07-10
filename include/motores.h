#pragma once
#include <Arduino.h>

struct Motores {
  uint8_t pwmActual = 200;
  int pwmBase = 200;
  bool estadoIzqActual = false;
  bool estadoDerActual = false;
  bool primerMovimiento = true;
};

extern Motores motores;

void moverMotores();
void configMotores();
void rotarEnLugar(int velocidadIzq, int velocidadDer);
void moverMotores();