#ifndef DRAWS_H
#define DRAWS_H
#include <TVout.h>

void drawRect(TVout TV, int x0, int y0, int width, int height, char c, char fc) {
  
  int x = max(x0-(width*0.5), 1);
  int w = min(width, TV.hres()-1-x0);
  int y = max(y0-(height*0.5), 1);
  int h = min(height, TV.vres()-1-y0);
  
  TV.draw_rect(x, y, w, h, c, fc);
}

void rectangles(TVout TV, int counter, float potValNorm) {
  int halfHor = TV.hres()/2;
  int halfVert = TV.vres()/2;
  int current = counter % 4;
  
  switch (current) {
    case 0:
      /*drawRect(TV,
        (halfHor - 40) + (sin(counter * 0.05) * potValNorm * halfHor),
        (halfVert - 29) + (cos(counter * 0.05) * potValNorm * halfVert),
        80, 56,
        WHITE,WHITE);*/
      // drawRect(TV, halfHor, halfVert, 40, 29,WHITE,WHITE);
      TV.draw_rect(20,20,80,56,INVERT);
    break;
    case 1:
      /*drawRect(TV,
        (halfHor-50) + (sin(counter * 0.3f) * potValNorm * halfHor),
        (halfVert-38) + (cos(counter * 0.3f) * potValNorm * halfVert),
        100, 76,
        WHITE,INVERT);*/
      TV.draw_rect(10,10,100,76,INVERT,INVERT);
    break;
    case 2:
      if (random(0, 2048) > 1023) {
        TV.draw_line(60,20+(38*potValNorm),60,76*potValNorm,INVERT);
      } else {
        TV.draw_line((60+(((potValNorm*2)-1))*30),20,(60-(((potValNorm*2)-1))*30),76,INVERT);
      }
      TV.draw_line(20*potValNorm,48,100*potValNorm,48,INVERT);
    break;
    case 3:
      TV.draw_line(10,10,110,86,INVERT);
      TV.draw_line(10,86,110,10,INVERT);
    break;
  }
  //rectangles and lines
  
  /*TV.delay(500);
  
  TV.delay(500);
  
  TV.delay(500);
  
  TV.delay(2000);*/
}

void circles(TVout TV, int counter, float potValNorm) {
  int halfHor = TV.hres()/2;
  int halfVert = TV.vres()/2;
  // rectangles(TV, counter, potValNorm);
  /*drawRect(TV,
    halfHor + (sin(counter * 0.1f) * potValNorm * halfHor),
    halfVert + (cos(counter * 0.1f) * potValNorm * halfVert),
    10, 10,
    WHITE,WHITE);
  TV.delay_frame(1);*/
  
  int centerX = halfHor; // + (sin(counter * 0.1f) * potValNorm * halfHor);
  int centerY = halfVert; // + (cos(counter * 0.1f) * potValNorm * halfVert);
  int radius = halfVert * potValNorm * 0.9;
    //circles
  if (counter % 2 == 0) {
    TV.draw_circle(
      centerX,
      centerY,
      radius,
      INVERT
    );
  } else {
    TV.draw_circle(halfHor,TV.vres()/2,TV.vres()/2 * (1.0f - potValNorm),INVERT,INVERT);
  }
}

#endif