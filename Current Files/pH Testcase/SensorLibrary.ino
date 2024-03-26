#include "sensorLibrary.h"
// #include "DHT.h"
#include <SoftwareSerial.h>  

SoftwareSerial myserial(pHrx, pHtx);   
//DHT dht(DHT_PIN, DHTTYPE);


String inputstring = "";                             
String sensorstring = "";                             
boolean input_string_complete = false;                
boolean sensor_string_complete = false;               
float pHval;                                             
int lowI=0;
int highI=0;


void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  inputstring.reserve(10);
  sensorstring.reserve(30);

  //Pin Setup
  // pinMode(WATER_PIN, INPUT);
  pinMode(PHUP_PIN, OUTPUT);
  pinMode(PHDOWN_PIN, OUTPUT);
  // pinMode(NUTRIENT_PIN, OUTPUT);
  // pinMode(IOTRELAY_PIN, OUTPUT);

  
  //dht.begin();
}

void serialEvent() {                                  //if the hardware serial port_0 receives a char
  inputstring = Serial.readStringUntil(13);           //read the string until we see a <CR>
  input_string_complete = true;                       //set the flag used to tell if we have received a completed string from the PC
}

void serialEvent3() {                                 //if the hardware serial port_3 receives a char
  sensorstring = Serial3.readStringUntil(13);         //read the string until we see a <CR>
  sensor_string_complete = true;                      //set the flag used to tell if we have received a completed string from the PC
}



//local vars
void loop() {
  
  digitalWrite(PHUP_PIN, LOW);
  digitalWrite(PHDOWN_PIN, LOW);

  
  delay(1000); //off for 1
  if (input_string_complete == true) {                //if a string from the PC has been received in its entirety
    //Serial3.print(inputstring);                       //send that string to the Atlas Scientific product
    //Serial3.print('\r');                              //add a <CR> to the end of the string
    inputstring = "";                                 //clear the string
    input_string_complete = false;                    //reset the flag used to tell if we have received a completed string from the PC
  }


  if (sensor_string_complete == true) {               //if a string from the Atlas Scientific product has been received in its entirety
    //Serial.println(sensorstring);
    pHval = sensorstring.toFloat(); 
    Serial.print("pH Value: "); 
    Serial.println(pHval);                    

  }
  sensorstring = "";                                  //clear the string:
  sensor_string_complete = false;  



//Data readout

  // Serial.print("Humidity: ");
  // Serial.print(hum);
  // Serial.print(" %");
  // Serial.print("\n");
  // Serial.print("Temperature: ");
  // Serial.print(temp);
  // Serial.print("\n");
  //Serial.print("pH: " );
  //Serial.print(pHval);
  //Serial.print("\n");

  
  if(pHval < 6)
  {
    lowI++;
    if(lowI>60){
      Serial.println("Raising pH"); 
      // phUP();
      delay(5000); //on for 1 second, accounts for pHup/down concentration
      Serial.println("Pump Off");
      lowI=0; 
    }
    
  }

  if(pHval > 7)
  {
    highI++;
    if(highI>60){
      Serial.println("Lowering pH"); 
      // phDOWN();
      
      delay(5000); //on for 1 second, accounts for pHup/down concentration
      Serial.println("Pump Off");
      highI=0;
    } 
  }


}
