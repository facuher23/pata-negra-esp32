#include "motores.h"
#include "config.h"

Motores motores;

void Motores::begin() {
  pinMode(Config::In1, OUTPUT); pinMode(Config::In2, OUTPUT); 
  pinMode(Config::In3, OUTPUT); pinMode(Config::In4, OUTPUT);
  ledcAttach(Config::In1, 31250, 8); ledcAttach(Config::In2, 31250, 8); 
  ledcAttach(Config::In3, 31250, 8); ledcAttach(Config::In4, 31250, 8);
}

void Motores::rotarEnLugar(int velocidadIzq, int velocidadDer) {
  if (velocidadIzq >= 0) {ledcWrite(Config::In2, 0); ledcWrite(Config::In1, velocidadIzq);}
  else {ledcWrite(Config::In1, 0); ledcWrite(Config::In2, -velocidadIzq);}

  if (velocidadDer >= 0) {ledcWrite(Config::In4, 0); ledcWrite(Config::In3, velocidadDer);}
  else {ledcWrite(Config::In3, 0); ledcWrite(Config::In4, -velocidadDer);}
}

void Motores::mover(int pwmVelocidad, int correccion) {
  int motorIzq = pwmVelocidad + correccion;
  int motorDer = pwmVelocidad - correccion;
  
  if (motorIzq > 255) motorIzq = 255;
  else if (motorIzq < -255) motorIzq = -255;
  
  if (motorDer > 255) motorDer = 255;
  else if (motorDer < -255) motorDer = -255;

  bool adelanteIzq = motorIzq >= 0;
  bool adelanteDer = motorDer >= 0;

  if (primerMovimiento || adelanteIzq != estadoIzqActual) {
    if (adelanteIzq) { ledcWrite(Config::In2, 0); } 
    else { ledcWrite(Config::In1, 0); }
    estadoIzqActual = adelanteIzq;
  }
  ledcWrite(adelanteIzq ? Config::In1 : Config::In2, abs(motorIzq));

  if (primerMovimiento || adelanteDer != estadoDerActual) {
    if (adelanteDer) { ledcWrite(Config::In4, 0); } 
    else { ledcWrite(Config::In3, 0); }
    estadoDerActual = adelanteDer;
  }
  ledcWrite(adelanteDer ? Config::In3 : Config::In4, abs(motorDer));

  primerMovimiento = false;
}