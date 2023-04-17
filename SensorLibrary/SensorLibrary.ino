#include "sensorLibrary.h"
#include "DHT.h"


DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  pinMode(WATER_PIN, INPUT);
  Serial.begin(9600);
  dht.begin();
}


//local vars
void loop() {
  delay(1000);

  float temp = myDHTf();
  float hum = myDHTh();
  int waterVal = waterDetect();
  
  if(waterVal == 1)
  {
    Serial.print("Water Detected");
    Serial.print("\n");
  }
  else
  { 
    Serial.print("NO WATER");
    //Serial.print("Error Code: FFFFF");
    Serial.print("\n");
  }
  
  
  
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print("\n");
  Serial.print("%  Temperature: ");
  Serial.print(temp);
  Serial.print("\n");
  
}
