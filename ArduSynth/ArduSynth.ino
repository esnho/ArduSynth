#include <TVout.h>
#include "schematic.h"
#include "playControl.h"
#include "lines.h"
#include "draws.h"
#include "cube.h"

TVout TV;

void setup() {
  Serial.begin(9600);

  onButtonPress = &buttonPressed;

  initializeBufferArray();
  TV.begin(PAL, 120, 96);
  // TV.select_font(font6x8);

  /*TV.clear_screen();
    circles(TV);*/

  /*TV.clear_screen();
    rectangles();*/

  //random cube forever.
  TV.clear_screen();

  randomSeed(analogRead(0));
  calccube(TV);
  TV.delay_frame(1);
  TV.clear_screen();
  draw_cube(TV);
  TV.clear_screen();
}

void loop() {
  //drawCube(false);
  
  if (getClear()) {
    TV.clear_screen();
  }

  //TV.clear_screen();
  switch (nowPlaying) {
    case 0:
      drawZero();
    break;
    case GLITCH_CIRCLES:
      drawGlitchCircles();
      break;
    case ROTATING_CUBE:
      drawCube(TV, getClear());
      break;
    case LINE_FLOW:
      drawLineFlow(TV);
  }
  readMultiButton();
}

int counter = 0;

void drawZero() {
  int duration = 80;
  if (counter % (duration * 2) < duration) {
    circles(TV, counter, potValNorm);
  } else {
    rectangles(TV, counter, potValNorm);
  }
  counter++;
  int rando = random(0, 2048);
  if (rando < 1024) {
    TV.delay_frame(((rando - 1023) / 512) + 1);
  }
}

void drawGlitchCircles() {
  int horCount = random(3, 40);
  int vertCount = 3;
  uint8_t radius = TV.vres() / random(5, 18);
  int i = 0;
  int j = 0;
  while (i < horCount - 1 && nowPlaying == GLITCH_CIRCLES) {
    j = 0;
    while (j < vertCount && nowPlaying == GLITCH_CIRCLES) {
      readMultiButton();
      radius = TV.vres() / random(5, 18);
      TV.draw_circle(
        ((TV.hres() / horCount) * i) + radius,
        ((TV.vres() / vertCount) * j) + radius,
        radius, INVERT, INVERT);
      // flash TV.draw_rect(0,0,TV.hres(),TV.vres(),INVERT, INVERT);
      TV.delay_frame(2);
      if (getClear()) {
        TV.clear_screen();
      }
      j++;
    }
    TV.delay_frame(2);
    i++;
  }
  horCount = 43 - horCount;
  i = horCount - 1;
  while (i > 0 && nowPlaying == GLITCH_CIRCLES) {
    j = 0;
    while (j < vertCount && nowPlaying == GLITCH_CIRCLES) {
      readMultiButton();
      TV.draw_circle(
        ((TV.hres() / horCount) * i) + radius,
        ((TV.vres() / vertCount) * j) + radius,
        radius, INVERT, INVERT);
      TV.delay_frame(2);
      if (getClear()) {
        TV.clear_screen();
      }
      j++;
    }
    TV.delay_frame(2);
    i--;
  }
  TV.clear_screen();
}
