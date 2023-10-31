#include "sensorLibrary.h"
#include "DHT.h"
#include <SoftwareSerial.h>  

SoftwareSerial myserial(pHrx, pHtx);   
//DHT dht(DHT_PIN, DHTTYPE);


String inputstring = "";                             
String sensorstring = "";                             
boolean input_string_complete = false;                
boolean sensor_string_complete = false;               
float pHval;                                             



void setup() {
  Serial.begin(9600);
  myserial.begin(9600);
  inputstring.reserve(10);
  sensorstring.reserve(30);

  //Pin Setup
  pinMode(WATER_PIN, INPUT);
  pinMode(PHUP_PIN, OUTPUT);
  pinMode(PHDOWN_PIN, OUTPUT);
  pinMode(NUTRIENT_PIN, OUTPUT);
  pinMode(IOTRELAY_PIN, OUTPUT);

  
  //dht.begin();
}


//local vars
void loop() {
  
  // float temp = myDHTf();
  // delay(500);
  // float hum = myDHTh();
  // delay(500);


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
  
  //phUP();
  //phDOWN();
  //nutrients();


  //relay(); //turns on grow lights & water pump -> should be on unless nighttime/maintenance
  
    if (myserial.available() > 0) {                     
    char inchar = (char)myserial.read();              
    sensorstring += inchar;                           
    if (inchar == '\r') {                             
      sensor_string_complete = true;                  
    }
  }


  if (sensor_string_complete == true) {               
    //Serial.println(sensorstring);                    
    
                                                    
    if (isdigit(sensorstring[0])) {                   
      pHval = sensorstring.toFloat();
    }
  }
  delay(1000);




//Data readout

  // Serial.print("Humidity: ");
  // Serial.print(hum);
  // Serial.print(" %");
  // Serial.print("\n");
  // Serial.print("Temperature: ");
  // Serial.print(temp);
  // Serial.print("\n");
  Serial.print("pH: " );
  Serial.print(pHval);
  Serial.print("\n");
  
}
