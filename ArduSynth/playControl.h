#ifndef PLAYCONTROL_H
#define PLAYCONTROL_H

#define GLITCH_CIRCLES 1
#define ROTATING_CUBE 2
#define LINE_FLOW 3
#include "multibutton.h"
#include "pots.h"

int nowPlaying = ROTATING_CUBE;
int shiftDir = 2;

bool clear = true;

void (*onButtonPress)(int);

float randomFloat[] = {1.0, 1.0};

float randomize() {
  randomFloat[0] = (random(0, 2048) / 2048.0);
  randomFloat[1] = (random(0, 2048) / 2048.0);
}

void buttonPressed(int buttonID) {
  /*Serial.print("wat a test! such a callbak! "); */
  // Serial.println(buttonID);
  if (buttonID >= 0 && buttonID != 5) {
    if (buttonID == 4) {
      clear = !clear;
    } else {
      nowPlaying = buttonID;
    }
  }
  if (buttonID == 5 || buttonID < 0) {
    randomize();
    shiftDir = (shiftDir + 1) % 4;
  }
}

void checkReads() {
  if (outputValue == 0 && sensorValue != 0) {
    // a better choice for the resistor would permit to remove the (-10) subtraction
    int buttonID = ((sensorValue - 10) / 100) - 5;
    if (state == NORMAL) {
//      Serial.print("DOWN! ");
//      Serial.print(buttonID);
//      Serial.print(" ");
//      Serial.print(sensorValue);
//      Serial.println(" ");
      onButtonPress(buttonID);
      state = PRESS;
    }
    return;
  } else if (outputValue != 0 && sensorValue == 0) {
    int buttonID = (outputValue / 100) - 5;
    if (state == NORMAL) {
      /*Serial.print("UP! ");
      Serial.print(buttonID);
      Serial.println(" ");*/
      state = RELEASE;
    }
    return;
  } else {
    state = NORMAL;
  }
  return;
}

void readMultiButton() {
  UpdateRead();
  UpdatePot();
  checkReads();
}

bool getClear() {
  return clear;
}

#endif
