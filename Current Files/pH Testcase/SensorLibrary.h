#ifndef SENSORLIBRARY_H
#define SENSORLIBRARY_H
#define pHrx 14
#define pHtx 15
// #define WATER_PIN 6
// #define IOTRELAY_PIN 7
// #define DHT_PIN 8
// #define NUTRIENT_PIN 11
#define PHUP_PIN 3
#define PHDOWN_PIN 2
// #define DHTTYPE DHT11







#include <Arduino.h>

//func definitions
//DHT dht(DHT_PIN, DHTTYPE);
// float myDHTf();
// float myDHTh();
// int waterDetect();
void phUP();
void phDOWN();
// void nutrients();
// void relay();
float pH();
#endif
