#include "Lib_Math.h"
#include <Arduino.h>
Lib_Math::Lib_Math() {}

void Lib_Math::summ(int a, int b) {
    int c = a+b;
    Serial.println(c);
}