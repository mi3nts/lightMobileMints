#ifndef TMG_39931_MINTS_H
#define TMG_39931_MINTS_H

#include <Arduino.h>
#include <Wire.h>

class TMG39931Mints
{
private:
    // attributes
    uint8_t i2cAddress;

public:

  TMG39931Mints(uint8_t i2cAddress);
  // Alpha Sensor Functions
  void begin();
  struct sensorData readData();
  void i2cTransfer(uint8_t send1, uint8_t send2);
  void printMintsBegin();
  void printMintsEnd();

};

  struct sensorData
    {
    float green;
    float red;
    float blue;
    float infraRed;
    uint8_t proximity;
    };

#endif
