#ifndef CUBE_H
#define CUBE_H
#include <TVout.h>
#include "playControl.h"

int zOff = 150;
int xOff = 0;
int yOff = 0;
int cSize = 50;
int view_plane = 64;
float angle = PI / 60;

float cube3d[8][3] = {
  {xOff - cSize, yOff + cSize, zOff - cSize},
  {xOff + cSize, yOff + cSize, zOff - cSize},
  {xOff - cSize, yOff - cSize, zOff - cSize},
  {xOff + cSize, yOff - cSize, zOff - cSize},
  {xOff - cSize, yOff + cSize, zOff + cSize},
  {xOff + cSize, yOff + cSize, zOff + cSize},
  {xOff - cSize, yOff - cSize, zOff + cSize},
  {xOff + cSize, yOff - cSize, zOff + cSize}
};
unsigned char cube2d[8][2];

void calccube(TVout TV) {
  //calculate 2d points
  for (byte i = 0; i < 8; i++) {
    cube2d[i][0] = (unsigned char)((cube3d[i][0] * view_plane / cube3d[i][2]) + (TV.hres() / 2));
    cube2d[i][1] = (unsigned char)((cube3d[i][1] * view_plane / cube3d[i][2]) + (TV.vres() / 2));
  }
}

void zrotate(float q) {
  float tx, ty, temp;
  for (byte i = 0; i < 8; i++) {
    tx = cube3d[i][0] - xOff;
    ty = cube3d[i][1] - yOff;
    temp = tx * cos(q) - ty * sin(q);
    ty = tx * sin(q) + ty * cos(q);
    tx = temp;
    cube3d[i][0] = tx + xOff;
    cube3d[i][1] = ty + yOff;
  }
}

void yrotate(float q) {
  float tx, tz, temp;
  for (byte i = 0; i < 8; i++) {
    tx = cube3d[i][0] - xOff;
    tz = cube3d[i][2] - zOff;
    temp = tz * cos(q) - tx * sin(q);
    tx = tz * sin(q) + tx * cos(q);
    tz = temp;
    cube3d[i][0] = tx + xOff;
    cube3d[i][2] = tz + zOff;
  }
}

void xrotate(float q) {
  float ty, tz, temp;
  for (byte i = 0; i < 8; i++) {
    ty = cube3d[i][1] - yOff;
    tz = cube3d[i][2] - zOff;
    temp = ty * cos(q) - tz * sin(q);
    tz = ty * sin(q) + tz * cos(q);
    ty = temp;
    cube3d[i][1] = ty + yOff;
    cube3d[i][2] = tz + zOff;
  }
}

void draw_cube(TVout TV) {
  char color = INVERT;
  TV.draw_line(cube2d[0][0], cube2d[0][1], cube2d[1][0], cube2d[1][1], color);
  TV.draw_line(cube2d[0][0], cube2d[0][1], cube2d[2][0], cube2d[2][1], color);
  TV.draw_line(cube2d[0][0], cube2d[0][1], cube2d[4][0], cube2d[4][1], color);
  TV.draw_line(cube2d[1][0], cube2d[1][1], cube2d[5][0], cube2d[5][1], color);
  TV.draw_line(cube2d[1][0], cube2d[1][1], cube2d[3][0], cube2d[3][1], color);
  TV.draw_line(cube2d[2][0], cube2d[2][1], cube2d[6][0], cube2d[6][1], color);
  TV.draw_line(cube2d[2][0], cube2d[2][1], cube2d[3][0], cube2d[3][1], color);
  TV.draw_line(cube2d[4][0], cube2d[4][1], cube2d[6][0], cube2d[6][1], color);
  TV.draw_line(cube2d[4][0], cube2d[4][1], cube2d[5][0], cube2d[5][1], color);
  TV.draw_line(cube2d[7][0], cube2d[7][1], cube2d[6][0], cube2d[6][1], color);
  TV.draw_line(cube2d[7][0], cube2d[7][1], cube2d[3][0], cube2d[3][1], color);
  TV.draw_line(cube2d[7][0], cube2d[7][1], cube2d[5][0], cube2d[5][1], color);
}

void printcube(TVout TV, bool clear) {
  calccube(TV);
  TV.delay_frame(1);
  if (getClear()) {
    TV.clear_screen();
  }
  draw_cube(TV);
}

void drawCube(TVout TV, bool clear) {
  int rsteps = random(10, 60);
  int i = 0;
  switch (random(6)) {
    case 0:
      while (i < rsteps && nowPlaying == ROTATING_CUBE) {
        zrotate(angle);
        printcube(TV, clear);
        i++;
        readMultiButton();
      }
      break;
    case 1:
      while (i < rsteps && nowPlaying == ROTATING_CUBE) {
        zrotate(2 * PI - angle);
        printcube(TV, clear);
        i++;
        readMultiButton();
      }
      break;
    case 2:
      while (i < rsteps && nowPlaying == ROTATING_CUBE) {
        xrotate(angle);
        printcube(TV, clear);
        i++;
        readMultiButton();
      }
      break;
    case 3:
      while (i < rsteps && nowPlaying == ROTATING_CUBE) {
        xrotate(2 * PI - angle);
        printcube(TV, clear);
        i++;
        readMultiButton();
      }
      break;
    case 4:
      while (i < rsteps && nowPlaying == ROTATING_CUBE) {
        yrotate(angle);
        printcube(TV, clear);
        i++;
        readMultiButton();
      }
      break;
    case 5:
      while (i < rsteps && nowPlaying == ROTATING_CUBE) {
        yrotate(2 * PI - angle);
        printcube(TV, clear);
        i++;
        readMultiButton();
      }
      break;
  }
}

#endif