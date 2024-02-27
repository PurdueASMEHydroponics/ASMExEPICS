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

  char lvlC[40];
  sprintf(lvlC, "Water level: %4d | %4d | %4d | %4d", level1, level2, level3, level4);
  Serial.println(lvlC);
    
    delay(500);

  if (level1 > threshold || level2 > threshold || level3 > threshold || level4 > threshold)
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
  else
  {
    val = analogRead(A3);        // Read the analog value from sensor
  }
    digitalWrite(sensorPower, LOW);        // Turn the sensor OFF
    return val;                            // send current reading
}

//trigger how? 