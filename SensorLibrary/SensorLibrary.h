#ifndef SENSORLIBRARY_H
#define SENSORLIBRARY_H
#define DHT_PIN 8
#define DHTTYPE DHT11
#define WATER_PIN 6
#define PHUP_PIN 12
#define PHDOWN_PIN 13
#define NUTRIENT_PIN 11
#define IOTRELAY_PIN 7
#define pHrx 2
#define pHtx 3


#include <Arduino.h>

//func definitions
//DHT dht(DHT_PIN, DHTTYPE);
float myDHTf();
float myDHTh();
int waterDetect();
void phUP();
void phDOWN();
void nutrients();
void relay();
float pH();
#endif
