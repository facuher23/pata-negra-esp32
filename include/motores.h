#pragma once
#include <Arduino.h>

class Motores {
public:

  void begin();
  void rotarEnLugar(int velocidadIzq, int velocidadDer);
  void mover(int pwmVelocidad, int correccion);

private:

  bool estadoIzqActual = false;
  bool estadoDerActual = false;
  bool primerMovimiento = true;
};

extern Motores motores;