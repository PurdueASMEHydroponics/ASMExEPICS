#include "sensorLibrary.h"
// #include "DHT.h"
#include <SoftwareSerial.h>  

//sensor funcs
// float myDHTf()
// {
//   DHT dht(DHT_PIN, DHTTYPE);
//   float tf = dht.readTemperature(); 

//   return tf;
// }

// float myDHTh()
// {
//   DHT dht(DHT_PIN, DHTTYPE);
//   float h = dht.readHumidity(); //humidity %
//   return h;
// }

// int waterDetect()
// {

//   int waterVal = digitalRead(WATER_PIN);
  
//   return waterVal;
// }

void phUP()
{
  digitalWrite(PHUP_PIN, HIGH);

}
void phDOWN()
{
  digitalWrite(PHDOWN_PIN, HIGH);
  
}
// void nutrients()
// {
//   digitalWrite(NUTRIENT_PIN, HIGH);
//   // delay(1000);
//   // digitalWrite(PHUP_PIN, LOW);
// }
// void relay()
// {
//   digitalWrite(IOTRELAY_PIN, HIGH);
//   // delay(1000);
//   // digitalWrite(PHUP_PIN, LOW);
// }

float pH()
{
  SoftwareSerial myserial(pHrx, pHtx);

  String inputstring = "";                             
  String sensorstring = "";                             
  boolean input_string_complete = false;                
  boolean sensor_string_complete = false;   
  float pHval;


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
      return pHval;
      delay(1000);
    }
  }



}

