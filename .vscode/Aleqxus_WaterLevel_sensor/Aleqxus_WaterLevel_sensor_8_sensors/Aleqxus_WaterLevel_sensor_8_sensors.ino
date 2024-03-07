/*
CURRENT CODE ON THE SYSTEM
*/

#define relay 13          // Tells Arduino the relay is connected to pin 13
#define sensorPower 7

int threshold = 300;
int val = 0;
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

void loop()                  // Loops forever
{
  // digitalWrite(relay, HIGH);   // Turn the relay on (HIGH is the voltage level = 1)
  // delay(10000);                 // Stay ON
  // digitalWrite(relay, LOW);    // Turn the relay off by making the voltage LOW = 0
  // delay(10000);                 // Stay OFF

  int level1 = readSensor(1);
  int level2 = readSensor(2);
  int level3 = readSensor(3);
  int level4 = readSensor(4);
  int level5 = readSensor(5);
  int level6 = readSensor(6);
  int level7 = readSensor(7);
  int level8 = readSensor(8);


  char lvlC[80];
  sprintf(lvlC, "Water level: %4d | %4d | %4d | %4d | %4d | %4d | %4d | %4d", level1, level2, level3, level4, level5, level6, level7, level8);
  Serial.println(lvlC);
    
    delay(500); //wait 0.5 seconds

  if (level1 > threshold || level2 > threshold || level3 > threshold || level4 > threshold || level5 > threshold || level6 > threshold || level7 > threshold || level8 > threshold)
  {
    stayOn = 0;
  }

  if (stayOn == 1)
  {
    digitalWrite(relay, HIGH);
  }
  else
  {
    digitalWrite(relay, LOW);
  }

}

int readSensor(int sensorPin) {
    digitalWrite(sensorPower, HIGH);    // Turn the sensor ON
    delay(10);                            // wait 10 milliseconds
  if (sensorPin == 1)
  {
    val = analogRead(A0);
  }
  else if (sensorPin == 2)
  {
    val = analogRead(A1);
  }
  else if (sensorPin == 3)
  {
    val = analogRead(A2);
  }
  else if (sensorPin == 4)
  {
    val = analogRead(A3);        // Read the analog value from sensor
  }
  else if (sensorPin == 5)
  {
    val = analogRead(A4);
  }
  else if (sensorPin == 6)
  {
    val = analogRead(A5);
  }
  else if (sensorPin == 7)
  {
    val = analogRead(A7);
  }
  else
  {
    val = analogRead(A8);
  }

  else 
    digitalWrite(sensorPower, LOW);        // Turn the sensor OFF
    return val;                            // send current reading
}

//trigger how? 
