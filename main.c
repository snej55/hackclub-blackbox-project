#include "blackbox.h"

// VEXATA QUAESTIO

// i postfix refers to int
// f postfix refers to float

#define BLACKBOX_TIMEOUT_1 1
#define BLACKBOX_TIMEOUT_2 125

// keep track of time
// wraps around from PI to -PI
float Time = 0.0;

// pi constant
const float M_PI = 3.14159265359;

// factorials
// precalculated for performance
const float FAC2 = 2.0;
const float FAC3 = 6.0;
const float FAC4 = 24.0;
const float FAC5 = 120.0;
const float FAC6 = 720.0;
const float FAC7 = 5040.0;
const float FAC8 = 40320.0;
const float FAC9 = 362880.0;
const float FAC10 = 3628800.0;

BlackBox* blackbox;

// float to integer
int f2i(float x) {
  return x - (x % 1);
}

// modulus operator for floats
float fmod(float a, float b)
{
    float frac = a / b;
    int floor = frac > 0 ? f2i(frac) : f2i(frac - 0.99999);
    return (a - b * floor);
}

// factorials
int factoriali(int n) {
    int fact = 1;

    for (int i = 1; i <= n; i++) {
        fact *= i;
    }

    return fact;
}

float factorialf(float n) {
    float fact = 1;

    for (float i = 1; i <= n; i++) {
        fact *= i;
    }

    return fact;
}

// powers
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

// cosinus & sinus functions
// uses Taylors sequence approximation
// is precise from -PI to PI, after that breaks apart
// so make sure to wrap values between these two with limitRangef(x, -M_PI, M_PI)
float sinex(float x) {
  return x - (powerf(x, 3.0) / FAC3) + (powerf(x, 5.0) / FAC5) - (powerf(x, 7.0) / FAC7) + (powerf(x, 9.0) / FAC9);
}

float cosx(float x) {
    return 1.0 - (powerf(x, 2.0) / FAC2) + (powerf(x, 4.0) / FAC4) - (powerf(x, 6.0) / FAC6) + (powerf(x, 8.0) / FAC8);
}

// comparisons
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

// prevent from rendering in wrong places
int clampi(int x, int lower_bound, int upper_bound) {
    return mini(upper_bound, maxi(lower_bound, x));
}

float clampf(float x, float lower_bound, float upper_bound) {
    return minf(upper_bound, maxf(lower_bound, x));
}

int getIndex(int x, int y)
{
    // row * width + col
    return y * 8 + x;
}

int limitRangei(int x, int lower_bound, int upper_bound) {
  if (x > upper_bound) {
    x = lower_bound;
  }
  if (x < lower_bound) {
    x = upper_bound;
  }
  return x;
}

void limitRangef(float x, float lower_bound, float upper_bound) {
  if (x > upper_bound) {
    x = lower_bound;
  }
  if (x < lower_bound) {
    x = upper_bound;
  }
  return x;
}


void drawRect(int x, int y, int w, int h) {
    for (int i = 0; i < h; ++i) {
        blackbox->matrix.slice(getIndex(clampi(x, 0, 7), clampi(y + i, 0, 7)), getIndex(clampi(x + w - 1, 0, 7), clampi(y + i, 0, 7)))->turn_all_on();
    }
}

void clearRect(int x, int y, int w, int h) {
    for (int i = 0; i < h; ++i) {
        blackbox->matrix.slice(getIndex(clampi(x, 0, 7), clampi(y + i, 0, 7)), getIndex(clampi(x + w - 1, 0, 7), clampi(y + i, 0, 7)))->turn_all_off();
    }
}

// checks collision between point and rectangle
// rectx, recty, rectwidth, rectheight, point x, point y
int checkCollisionRect(int rx, int ry, int rw, int rh, int px, int py) {
  if (px >= rx && px < rx + rw && py >= ry && py < ry + rh) {
    return 1;
  }
  return 0;
}

// same with floats
int checkCollisionRectf(float rx, float ry, float rw, float rh, float px, float py) {
  if (px >= rx && px < rx + rw && py >= ry && py < ry + rh) {
    return 1;
  }
  return 0;
}

// draws rotated rect.
void drawRotRect(float xpos, float ypos, float width, float height, float angle)
{
  // convert angle to radians
  float a = limitRangef(angle, -M_PI, M_PI);

  // // sin & cos values
  float s = sinex(a);
  float c = cosx(a);

  // // center x & center y
  float cx = xpos;
  cx = cx + width * 0.5;
  float cy = ypos;
  cy = cy + height * 0.5;

  int ccx = f2i(cx);
  int ccy = f2i(cy);
  blackbox->matrix.pixel_xy(ccx, ccy).turn_on();

  // iterate over points in rectangle, then rotates them
  for (float x = xpos; x < xpos + width; ++x) {
    for (float y = ypos; y < ypos + height; ++y) {
  
      // calculate relative point position
      float px = x - cx;
      float py = y - cy;
  
      // rotate around origin
      float xnew = px * c - py * s;
      float ynew = px * s + py * c;
  
      // move back to rectangle
      px = xnew + cx;
      py = ynew + cy;

      // convert to integer for rendering
      int point_x = f2i(px);
      int point_y = f2i(py);

      // clamp values
      int render_x = clampi(point_x, 0, 7);
      int render_y = clampi(point_y, 0, 7);
      // render
      blackbox->matrix.pixel_xy(render_x, render_y).turn_on();
    }
  }
}

void setpixelf(float x, float y) {
  int xp = f2i(x);
  int yp = f2i(y);
  // check if it's on the screen
  if (xp >= 0 && xp <= 7 && yp >= 0 && yp <= 7) {
    blackbox->matrix.pixel_xy(xp, yp).turn_on();
  }
}

int isontrack(float x, float y) {
  
}

// These functions are called when the buttons are pressed
void on_up() {
}
void on_down() {
}
void on_left() {
}
void on_right() {
}
void on_select() {}

// These functions are called repeatedly
void on_timeout_1() {
  Time = Time + 0.01;
  Time = limitRangef(Time, -M_PI, M_PI);
}

void on_timeout_2() {
  blackbox->matrix.turn_all_off();
  float angle = sinex(Time) * M_PI;
  drawRotRect(3.0, 2.0, 2.0, 5.0, Time);
}
 
// Your main loop goes here!
void main() {
  // float xf = factorial(4);

  // drawRect(1, f2i(cosx(0)), 3, 3);
  // blackbox->matrix.slice(0, 8)->turn_all_on();
  // float x = (int)clampf((float)(1), 0.0, 10.0);
  while (1) {}
}