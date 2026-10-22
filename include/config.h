#pragma once
#include <Arduino.h>

namespace Config {
constexpr uint8_t In1 = 12;
constexpr uint8_t In2 = 13;
constexpr uint8_t In3 = 14;
constexpr uint8_t In4 = 15;

constexpr uint8_t cantidadSensores = 5;
constexpr int centro = 2000;
constexpr uint16_t limitBlanco = 500;
}