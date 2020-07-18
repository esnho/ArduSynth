#ifndef MULTIBUTTON_H
#define MULTIBUTTON_H

#define PRESS 2
#define NORMAL 0
#define RELEASE 1
#include <Arduino.h>

uint8_t state = NORMAL;
const uint8_t readingBuffer = 3; // the buffer size
/*
2.75 +/-0.1
3.30 +/-0.1
3.75 +/-0.1
4.10 +/-0.1
4.51 +/-0.1
4.89 +/-0.1
*/
uint8_t sensorPin = A5; // The input port
int sensorValue; // Current reading
int outputValue; // The reported reading
int lastValues[readingBuffer]; // The last 3 readings

void UpdateRead() {
  // read the value from the sensor:
  sensorValue = analogRead(A5);
  // Initialise variables for checks
  uint8_t i;
  uint8_t updateOutput = 1;
  // Loop through previous readings
  for ( i = 0 ; i < readingBuffer ; i++ ) {
    // If this historic value doesn't match the current reading,
    // we will not update the output value
    if ( abs(lastValues[i] - sensorValue) > 3  ) {
      updateOutput = 0;
    }
    // Shift the array elements to make room for new value
    if ( i > 0 ) {
      lastValues[(i - 1)] = lastValues[i];
    }
  }
  // Update if needed
  if ( updateOutput == 1 ) {
    outputValue = sensorValue;
  }
  // Append the new value
  lastValues[2] = sensorValue;
}

void initializeBufferArray() {
  uint8_t i;
  for (i = 0 ; i < readingBuffer ; i++ ) {
    lastValues[i] = 0;
  }
}

#endif
