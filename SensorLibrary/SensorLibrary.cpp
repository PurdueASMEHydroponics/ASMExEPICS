#include "sensorLibrary.h"
#include "DHT.h"
//sensor funcs

float myDHTf()
{
  DHT dht(DHT_PIN, DHTTYPE);
  float tf = dht.readTemperature(); //farenheit

  return tf;

}
float myDHTh()
{
  DHT dht(DHT_PIN, DHTTYPE);
  float h = dht.readHumidity(); //humidity %
  return h;
}