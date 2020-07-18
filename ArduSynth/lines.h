#ifndef LINES_H
#define LINES_H
#include <TVout.h>
#include "playControl.h"
#include "draws.h"

int heavenState = 0;

void theHeaven(TVout TV) {
  char color = INVERT;
  if (TV.hres() > heavenState) {
    TV.draw_line(heavenState, TV.vres(), TV.hres() - heavenState, 0, color);
    heavenState += 4;
  } else {
    heavenState = 0;
  }
}

int x1 = 0;
int y1 = 0;
int x2 = 0;
int y2 = 0;
float t = 0;

void lissa(TVout TV) {
  int s = 1+(potValNorm*15);
  
  int hl = (TV.hres() * 0.5) - 1;
  int vl = (TV.vres() * 0.5) - 1;

  char color = INVERT;
  float st = sin(t) + 1.0;
  float ct = cos(t) + 1.0;
  x1 = ((sin(t * randomFloat[0]) + 1.0) * hl) - (s*0.5);
  y1 = ((sin(t * randomFloat[1]) + 1.0) * vl)- (s*0.5);
  
  drawRect(TV, x1,y1,s,s,WHITE,color);
  // TV.draw_rect(x2,y2,1,1,WHITE);
  TV.delay_frame(1);
  // TV.clear_screen();
  t = t + 0.13 + (0.0f);
}

void drawLineFlow(TVout TV) {
  lissa(TV);
}

#endif
