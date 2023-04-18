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

int waterDetect()
{
  //static char waterStr[] = "No Read";
  int waterVal = digitalRead(WATER_PIN);
  //Serial.print(waterVal);
  // if(waterVal == 1)
  // {
  //   strcpy(waterStr, "Water Detected");
  // }
  // else
  // {
  //   strcpy(waterStr, "NO WATER!!");
  // }
  
  return waterVal;
}

void phUP()
{
  digitalWrite(PHUP_PIN, HIGH);
  // delay(1000);
  // digitalWrite(PHUP_PIN, LOW);
}
void phDOWN()
{
  digitalWrite(PHDOWN_PIN, HIGH);
  // delay(1000);
  // digitalWrite(PHUP_PIN, LOW);
}
void nutrients()
{
  digitalWrite(NUTRIENT_PIN, HIGH);
  // delay(1000);
  // digitalWrite(PHUP_PIN, LOW);
}
void relay()
{
  digitalWrite(IOTRELAY_PIN, HIGH);
  // delay(1000);
  // digitalWrite(PHUP_PIN, LOW);
}



