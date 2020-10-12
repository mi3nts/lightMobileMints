/***************************************************************************
  TMG39931Mints
  ---------------------------------
  Written by: Lakitha Omal Harindha Wijeratne
  - for -
  Mints: Multi-scale Integrated Sensing and Simulation
  ---------------------------------
  Date: September 10th, 2019
  ---------------------------------
  This library is written for the Grove Light & Gesture & Color & Proximity Sensor (TMG39931)
  ----------------> http://wiki.seeedstudio.com/Grove-Light-Gesture-Color-Proximity_Sensor-TMG39931/
  --------------------------------------------------------------------------
  https://github.com/mi3nts
  http://utdmints.info/

 ***************************************************************************/

#include "TMG39931Mints.h"
#include <Arduino.h>

/***************************************************************************
 PRIVATE FUNCTIONS
 ***************************************************************************/

 TMG39931Mints::TMG39931Mints(uint8_t address){
  i2cAddress  = address;
 }

// Sensor Functions
 void TMG39931Mints::begin()
{
  Wire.begin();
    i2cTransfer(0x80,0x0F);
    i2cTransfer(0x81,0x00);
    i2cTransfer(0x83,0xFF);
    i2cTransfer(0x8F,0x00);

  
  delay(300);

}
 struct sensorData TMG39931Mints::readData(){

  uint8_t  data[9];
  
  // Initiating Data Inputs
  Wire.beginTransmission(i2cAddress);
  Wire.write(0x94);
  Wire.endTransmission();
  
 Wire.requestFrom(i2cAddress, 9);

  if(Wire.available() == 9) 
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
    data[6] = Wire.read();
    data[7] = Wire.read();
    data[8] = Wire.read();
   }
   
  // Convert the data
  sensorData sensorDataFile;
  sensorDataFile.infraRed = data[1] * 256.0 + data[0];
  sensorDataFile.red      = data[3] * 256.0 + data[2];
  sensorDataFile.green    = data[5] * 256.0 + data[4];
  sensorDataFile.blue     = data[7] * 256.0 + data[6];
  sensorDataFile.proximity     = data[8];

return sensorDataFile;
}


void TMG39931Mints::i2cTransfer(uint8_t send1, uint8_t send2) {
  Wire.beginTransmission(i2cAddress);
  Wire.write(send1);
  Wire.write(send2);
  Wire.endTransmission();
}


void TMG39931Mints::printMintsBegin(){
  Serial.println("");
  Serial.println("--------------------------------");
  Serial.println("-------------MINTS--------------");

}

void TMG39931Mints::printMintsEnd(){
    Serial.println("");
    Serial.println("-------------MINTS--------------");
    Serial.println("--------------------------------");
}
