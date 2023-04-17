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
  delay(250);

  float temp = myDHTf();
  float hum = myDHTh();
  char* waterStr = waterDetect();
  
  
  Serial.print(waterStr);
  Serial.print("\n");
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print("\n");
  Serial.print("%  Temperature: ");
  Serial.print(temp);
  Serial.print("\n");
  
}
