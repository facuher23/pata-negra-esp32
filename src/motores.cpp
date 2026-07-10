#include "motores.h"
#include "pid.h"
#include "config.h"

Motores motores;

void configMotores() {
  pinMode(In1, OUTPUT); pinMode(In2, OUTPUT); pinMode(In3, OUTPUT); pinMode(In4, OUTPUT);
  ledcAttach(In1, 31250, 8); ledcAttach(In2, 31250, 8); ledcAttach(In3, 31250, 8); ledcAttach(In4, 31250, 8);
}

void rotarEnLugar(int velocidadIzq, int velocidadDer) {
  if (velocidadIzq >= 0) {ledcWrite(In2, 0); ledcWrite(In1, velocidadIzq);}
  else {ledcWrite(In1, 0); ledcWrite(In2, -velocidadIzq);}

  if (velocidadDer >= 0) {ledcWrite(In4, 0); ledcWrite(In3, velocidadDer);}
  else {ledcWrite(In3, 0); ledcWrite(In4, -velocidadDer);}
}

void moverMotores() {
  int motorIzq = motores.pwmActual + pid.correccion;
  int motorDer = motores.pwmActual - pid.correccion;
  
  if (motorIzq > 255) motorIzq = 255;
  else if (motorIzq < -255) motorIzq = -255;
  
  if (motorDer > 255) motorDer = 255;
  else if (motorDer < -255) motorDer = -255;

  bool adelanteIzq = motorIzq >= 0;
  bool adelanteDer = motorDer >= 0;

  if (motores.primerMovimiento || adelanteIzq != motores.estadoIzqActual) {
    if (adelanteIzq) {
      ledcWrite(In2, 0); 
    } else {
      ledcWrite(In1, 0);
    }
    motores.estadoIzqActual = adelanteIzq;
  }
  ledcWrite(adelanteIzq ? In1 : In2, abs(motorIzq));

  if (motores.primerMovimiento || adelanteDer != motores.estadoDerActual) {
    if (adelanteDer) {
      ledcWrite(In4, 0);
    } else {
      ledcWrite(In3, 0);
    }
    motores.estadoDerActual = adelanteDer;
  }
  ledcWrite(adelanteDer ? In3 : In4, abs(motorDer));

  motores.primerMovimiento = false;
}