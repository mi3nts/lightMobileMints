#ifndef DEVICES_MINTS_H
#define DEVICES_MINTS_H
//
#include <Arduino.h>
#include "OPCN3NanoMints.h"
#include "MutichannelGasSensor.h"
#include "Seeed_BME280.h"
#include "jobsMints.h"

extern BME280 bme280;
bool initializeBME280Mints();
void readBME280Mints();

bool initializeMGS001Mints();
void readMGS001Mints();

extern OPCN3NanoMints opc;
bool initializeOPCN3Mints();
bool readOPCN3Mints(bool status);


#endif
