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

char* waterDetect()
{
  static char waterStr[] = "Nor Read";
  int waterVal = digitalRead(WATER_PIN);
  Serial.print(waterVal);
  if(waterVal == 1)
  {
    strcpy(waterStr, "Water Detected");
  }
  else
  {
    strcpy(waterStr, "NO WATER!!");
  }
  
  return waterStr;
}