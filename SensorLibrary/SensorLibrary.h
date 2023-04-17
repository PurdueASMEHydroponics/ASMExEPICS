#ifndef SENSORLIBRARY_H
#define SENSORLIBRARY_H
#define DHT_PIN 8
#define DHTTYPE DHT11
#define WATER_PIN 5


#include <Arduino.h>

//func definitions
//DHT dht(DHT_PIN, DHTTYPE);
float myDHTf();
float myDHTh();
char* waterDetect();

#endif
