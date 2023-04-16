String inputstring = "";                             
String sensorstring = "";                             
boolean input_string_complete = false;               
boolean sensor_string_complete = false;    
float pH;           

 void setup() {
  Serial.begin(9600);                                
  Serial3.begin(9600);                                
  inputstring.reserve(10);                            
  sensorstring.reserve(30);   
  pinMode(7,OUTPUT);

 

}

int x = 50;
void serialEvent() {                                 
  inputstring = Serial.readStringUntil(13);          
  input_string_complete = true;                       
}

void serialEvent3() {                                 
  sensorstring = Serial3.readStringUntil(13);         
  sensor_string_complete = true;                     
}

void loop() {
  
  if (input_string_complete == true) {  
    //Serial3.print("pH:");             
    Serial3.print(inputstring);                      
    Serial3.print('\r');                            
    inputstring = "";                               
    input_string_complete = false;                   
  }

  if (sensor_string_complete == true) {              
    if (isdigit(sensorstring[0])) {                
      pH = sensorstring.toFloat();
      Serial.println("pH:");
      Serial.println(pH);
      //Serial.println("\n");
    }
  }

  sensorstring = "";
  sensor_string_complete = false;

  digitalWrite(7, HIGH);
  Serial.println("Motor On");
  delay(1000);
  digitalWrite(7, LOW);
  Serial.println("Motor Off");
  delay(1000);

}


