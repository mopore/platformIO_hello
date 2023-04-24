#pragma once

#include <Arduino.h>

typedef struct {
  int16_t x;
  int16_t y;
} CarInput;

extern volatile CarInput carInput;