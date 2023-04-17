#include "sensorLibrary.h"
#include "DHT.h"


DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(WATER_PIN, INPUT);
  pinMode(PHUP_PIN, OUTPUT);
  pinMode(PHDOWN_PIN, OUTPUT);
  pinMode(NUTRIENT_PIN, OUTPUT);
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
  
  // while()
  // {
  //   phUP();
  // }
  phUP();
  phDOWN();
  nutrients();
  
  
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print("\n");
  Serial.print("%  Temperature: ");
  Serial.print(temp);
  Serial.print("\n");
  
}
