#include <stdio.h>

#define M_PI 3.14159265359
// factorials
const float FAC2 = 2.0;
const float FAC3 = 6.0;
const float FAC4 = 24.0;
const float FAC5 = 120.0;
const float FAC6 = 720.0;
const float FAC7 = 5040.0;
const float FAC8 = 40320.0;
const float FAC9 = 362880.0;
const float FAC10 = 3628800.0;

int factoriali(int n) {
    int i;
    int fact = 1;

    for (i = 1; i <= n; i++) {
        fact *= i;
    }

    return fact;
}

float factorialf(float n) {
    float i;
    float fact = 1;

    for (i = 1; i <= n; i++) {
        fact *= i;
    }

    return fact;
}

int poweri(int n, int power) {
    int result = n;
    for(int i = 1; i < power; i++) {
        result = n * result;
    }
    return result;
}

float powerf(float n, float power) {
    float result = n;
    for(int i = 1; i < power; i++) {
        result = n * result;
    }
    return result;
}

float sinex(float x) {
  return x - (powerf(x, 3.0) / FAC3) + (powerf(x, 5.0) / FAC5) - (powerf(x, 7.0) / FAC7) + (powerf(x, 9.0) / FAC9);
}

float cosx(float x) {
    return 1.0 - (powerf(x, 2.0) / FAC2) + (powerf(x, 4.0) / FAC4) - (powerf(x, 6.0) / FAC6) + (powerf(x, 8.0) / FAC8);
}

int main() {
    // for (int i = 0; i < 10; ++i)
    // {
    printf("%i %f \n", 1, cosx(M_PI / 2.0));
    // }
    return 0;
}