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

void drawRect(int x, int y, int w, int h) {
    
}
 
// Your main loop goes here!
void main() {
  while (1) {

  }
}