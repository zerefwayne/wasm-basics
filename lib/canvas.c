#include<stdio.h>
#include<stdlib.h>
#include<emscripten.h>
#include<time.h>

#define NUM_CIRCLES 20

struct Circle {
  int x;
  int y;
  int radius;
  int color_r;
  int color_g;
  int color_b;
};

struct CircleAnimationData {
  int x;
  int y;
  int radius;
  int v_x;
  int v_y;
  int d_x;
  int d_y;
};

struct Circle circles[NUM_CIRCLES];
struct CircleAnimationData animationData[NUM_CIRCLES];

int getRand(int max) {
  return (rand() % max);
}

int main() {
  srand(time(NULL));

  for( int i = 0; i < NUM_CIRCLES; i++) {
    int radius = getRand(50);
    int x = getRand(1000) + radius;
    int y = getRand(1000) + radius;

    animationData[i].x = x;
    animationData[i].y = y;
    animationData[i].radius = radius;
    animationData[i].v_x = getRand(10);
    animationData[i].v_y = getRand(10);
    animationData[i].d_y = 1;
    animationData[i].d_y = 1;

    circles[i].x = x;
    circles[i].y = y;
    circles[i].radius = radius;
    circles[i].color_r = getRand(255);
    circles[i].color_g = getRand(255);
    circles[i].color_b = getRand(255);
  }

  EM_ASM({render($0, $1);}, NUM_CIRCLES*6, 6);
}

struct Circle * getCircles(int canvasWidth, int canvasHeight) {

  for(int i = 0; i < NUM_CIRCLES; i++) {

    if((animationData[i].x + animationData[i].radius) >= canvasWidth) animationData[i].d_x = 0;
    if((animationData[i].x - animationData[i].radius) <= 0) animationData[i].d_x = 1;
    if((animationData[i].y - animationData[i].radius) <= 0) animationData[i].d_y = 1;
    if((animationData[i].y + animationData[i].radius) >= canvasHeight) animationData[i].d_y = 0;

    if(animationData[i].d_x == 1) {
      animationData[i].x += animationData[i].v_x;
    } else {
      animationData[i].x -= animationData[i].v_x;
    }

    if(animationData[i].d_y == 1) {
      animationData[i].y += animationData[i].v_y;
    } else {
      animationData[i].y -= animationData[i].v_y;
    }

    circles[i].x = animationData[i].x;
    circles[i].y = animationData[i].y;
  }

  return circles;
}
