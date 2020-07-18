#ifndef POTS_H
#define POTS_H

uint8_t potPin = A0; // The input port
int potVal = 0; // Current reading
float potValNorm = 0.0f; // Current reading

void UpdatePot() {
  // read the value from the sensor:
  potVal = analogRead(potPin);
  potValNorm = 1.0f - ((float) potVal / 1024.0);
}

#endif
