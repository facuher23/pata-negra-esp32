#include <QTRSensors.h>
#define In1 2
#define In2 3
#define In3 4
#define In4 5
QTRSensors qtr;
const uint8_t cantidadSensores = 8;
uint16_t valoresSensores[cantidadSensores];
constexpr int centro = 3500;
constexpr uint16_t limitBlanco = 500; 
int pwmBase = 200;

float kp = 0.05;  
float kd = 0.3;   
float kFreno = 0.01; 

int errorAnterior = 0;
int correccion = 0;
uint16_t posicion = 0;
uint8_t pwmActual = 200;
bool enLinea = true;

int estadoIzqActual = -1;
int estadoDerActual = -1;

inline void rotarEnLugar(int velocidadIzq, int velocidadDer) {
  if (velocidadIzq >= 0) {
    analogWrite(In2, 0); digitalWrite(In2, LOW); analogWrite(In1, velocidadIzq);
  } else {
    analogWrite(In1, 0); digitalWrite(In1, LOW); analogWrite(In2, -velocidadIzq);
  }

  if (velocidadDer >= 0) {
    analogWrite(In4, 0); digitalWrite(In4, LOW); analogWrite(In3, velocidadDer);
  } else {
    analogWrite(In3, 0); digitalWrite(In3, LOW); analogWrite(In4, -velocidadDer);
  }
}

void setup() {
  pinMode(In1, OUTPUT); pinMode(In2, OUTPUT); pinMode(In3, OUTPUT); pinMode(In4, OUTPUT); analogWriteFreq(31250);
  qtr.setTypeRC(); qtr.setSensorPins((const uint8_t[]){10, 11, 12, 13, 14, 15, 16, 17}, cantidadSensores);

  rotarEnLugar(80, -80); 

  for (uint16_t i = 0; i < 200; i++) {
    qtr.calibrate();
    delay(10);
  }

  rotarEnLugar(0, 0);
  delay(1000); 
}

inline void leerSensores() {
  posicion = qtr.readLineWhite(valoresSensores);
  enLinea = false;

  for (int i = 0; i < cantidadSensores; i++) {
    if (valoresSensores[i] < limitBlanco) { 
      enLinea = true;
      break;
    }
  }
}

inline void calcularPID() {
  if (!enLinea) {
    if (errorAnterior > 0) {
      correccion = 255;
    } else {
      correccion = -255;
    }
    pwmActual = 0;
    return;
  }

  int error = posicion - centro;
  int derivada = error - errorAnterior;
  
  correccion = (kp * error) + (kd * derivada);
  errorAnterior = error;

  float pwmTemporal = (float)pwmBase - (fabsf((float)error) * kFreno);
  
  if (pwmTemporal < 50.0) { 
    pwmTemporal = 50.0; 
  }
  
  pwmActual = (uint8_t)pwmTemporal;
}

inline void moverMotores() {
  int motorIzq = (int)pwmActual + correccion;
  int motorDer = (int)pwmActual - correccion;
  
  if (motorIzq > 255) motorIzq = 255;
  else if (motorIzq < -255) motorIzq = -255;
  
  if (motorDer > 255) motorDer = 255;
  else if (motorDer < -255) motorDer = -255;
  
  int estadoIzqNuevo = (motorIzq >= 0) ? 1 : 0;
  int estadoDerNuevo = (motorDer >= 0) ? 1 : 0;

  if (estadoIzqNuevo != estadoIzqActual) {
    if (estadoIzqNuevo) {
      analogWrite(In2, 0);
      digitalWrite(In2, LOW);
    } else {
      analogWrite(In1, 0);
      digitalWrite(In1, LOW);
    }
    estadoIzqActual = estadoIzqNuevo;
  }
  analogWrite((estadoIzqNuevo == 1) ? In1 : In2, motorIzq >= 0 ? motorIzq : -motorIzq);

  if (estadoDerNuevo != estadoDerActual) {
    if (estadoDerNuevo) {
      analogWrite(In4, 0);
      digitalWrite(In4, LOW);
    } else {
      analogWrite(In3, 0);
      digitalWrite(In3, LOW);
    }
    estadoDerActual = estadoDerNuevo;
  }
  analogWrite((estadoDerNuevo == 1) ? In3 : In4, motorDer >= 0 ? motorDer : -motorDer);
}

void loop() {
  leerSensores();
  calcularPID();
  moverMotores();
}// Pia ♡