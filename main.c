#include "blackbox.h"

// VEXATA QUAESTIO

#define BLACKBOX_TIMEOUT_1 1
#define BLACKBOX_TIMEOUT_2 125

BlackBox* blackbox;

// These functions are called when the buttons are pressed
void on_up() {}
void on_down() {}
void on_left() {}
void on_right() {}
void on_select() {}

// These functions are called repeatedly
void on_timeout_1() {}
void on_timeout_2() {}

int maxi(int x, int y) {
    return x > y ? x : y;
}

float maxf(float x, float y) {
    return x > y ? x : y;
}

int mini(int x, int y) {
    return x < y ? x : y;
}

float minf(float x, float y) {
    return x < y ? x : y;
}

int clampi(int x, int lower_bound, int upper_bound) {
    return mini(upper_bound, maxf(lower_bound, x));
}

float clampf(float x, float lower_bound, float upper_bound) {
    return mini(upper_bound, maxf(lower_bound, x));
}

int getIndex(int x, int y)
{
    // row * width + col
    return y * 8 + x;
}

void drawRect(int x, int y, int w, int h) {
    for (int i = 0; i < h; ++i) {
        blackbox->matrix.slice(getIndex(clampi(x, 0, 7), clampi(y + i, 0, 7)), getIndex(clampi(x + w - 1, 0, 7), clampi(y + i, 0, 7)))->turn_all_on();
    }
}
 
// Your main loop goes here!
void main() {
  while (1) {

  }
}