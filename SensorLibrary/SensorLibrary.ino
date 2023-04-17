#include "sensorLibrary.h"
#include "DHT.h"
#define DHT_PIN 8
#define DHTTYPE DHT11

DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}


//local vars
void loop() {
  delay(2000);
  float temp = myDHTf();
  float hum = myDHTh();

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print("%  Temperature: ");
  Serial.print(temp);
  Serial.print("\n");
  
}
