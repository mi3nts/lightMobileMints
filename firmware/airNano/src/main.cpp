#include "Arduino.h"
#include "jobsMints.h"
#include "devicesMints.h"



#define CS 10

OPCN3NanoMints opc = OPCN3NanoMints(CS);
bool  OPCN3Online;
bool opcStatus = false;


bool MGS001Online;

bool BME280Online;
BME280 bme280; // I2C

uint16_t sensingPeriod = 1000;
uint16_t initPeriod = 1500;

unsigned long startTime;

void setup() {

  delay(initPeriod);
  initializeSerialMints();

  delay(initPeriod);
  BME280Online = initializeBME280Mints();
  //
  delay(initPeriod);
  MGS001Online =  initializeMGS001Mints();

  delay(initPeriod);
  OPCN3Online =  initializeOPCN3Mints();


}


// the loop routine runs over and over again forever:
void loop() {
    
    startTime  = millis();
    
    delay(sensingPeriod);
    if(BME280Online)
    {
      readBME280Mints();
    }

    delay(sensingPeriod);
    if(MGS001Online)
    {
      readMGS001Mints();
    }

    delay(sensingPeriod);
    if(OPCN3Online)
    {
      opcStatus =  readOPCN3Mints(opcStatus);
    }

    delayMints(millis() - startTime,10000);

}