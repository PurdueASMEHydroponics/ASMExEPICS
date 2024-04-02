/*
CURRENT CODE ON THE SYSTEM
*/

#define relay 13          // Tells Arduino the relay is connected to pin 13
#define sensorPower 7
#define threshold 300

int waterVal = 0;
int stayOn = 1;

void setup()
{
  pinMode(relay, OUTPUT);       // Initialize the Atmel GPIO pin as an output
  
  Serial.begin(9600);

  Serial.println("Setting up...");

    // Set D7 as an OUTPUT
    pinMode(sensorPower, OUTPUT);
    
    // Set to LOW so no power flows through the sensor
    digitalWrite(sensorPower, LOW); 

  Serial.println("Ready!");
}

void waterDetectionMain()                  // Loops forever
{
  // digitalWrite(relay, HIGH);   // Turn the relay on (HIGH is the voltage level = 1)
  // delay(10000);                 // Stay ON
  // digitalWrite(relay, LOW);    // Turn the relay off by making the voltage LOW = 0
  // delay(10000);                 // Stay OFF

  int level1 = readSensor(1);     // Stores data from sensors 1, 2, 3, etc.
  int level2 = readSensor(2);     // The code is like this because the analog ports don't line up to sensor numbers
  int level3 = readSensor(3);
  int level4 = readSensor(4);
  int level5 = readSensor(5);
  int level6 = readSensor(6);
  int level7 = readSensor(7);
  int level8 = readSensor(8);


  char lvlC[80];  // Prints all the water levels
  sprintf(lvlC, "Water level: %4d | %4d | %4d | %4d | %4d | %4d | %4d | %4d", level1, level2, level3, level4, level5, level6, level7, level8);
  Serial.println(lvlC);
    
    delay(500); //wait 0.5 seconds

  if (level1 > threshold || level2 > threshold || level3 > threshold || level4 > threshold || level5 > threshold || level6 > threshold || level7 > threshold || level8 > threshold)
  {
    stayOn = 0;   // Turns off the pumps
  }

  if (stayOn == 1)
  {
    digitalWrite(relay, HIGH);   // Pump power is KEPT on by arduino - circuit is normally off 
  }
  else
  {
    digitalWrite(relay, LOW);
  }

}

int readSensor(int sensorPin)           // This is just storing sensors and their respective analog pins
{                                       // The function will be called upon in the above section
    
    digitalWrite(sensorPower, HIGH);    // Turn the sensor ON
    delay(10);                            // wait 10 milliseconds
  if (sensorPin == 1)
  {
    waterVal = analogRead(A0);          // Read the analog value from corresponding sensor
  }
  else if (sensorPin == 2)
  {
    waterVal = analogRead(A1);
  }
  else if (sensorPin == 3)
  {
    waterVal = analogRead(A2);
  }
  else if (sensorPin == 4)
  {
    waterVal = analogRead(A3);        
  }
  else if (sensorPin == 5)
  {
    waterVal = analogRead(A4);
  }
  else if (sensorPin == 6)
  {
    waterVal = analogRead(A5);
  }
  else if (sensorPin == 7)
  {
    waterVal = analogRead(A7);
  }
  else
  {
    waterVal = analogRead(A8);
  }

  else 
    digitalWrite(sensorPower, LOW);        // Turn the sensor OFF
    return waterVal;                            // send current reading
}

//trigger how? 
