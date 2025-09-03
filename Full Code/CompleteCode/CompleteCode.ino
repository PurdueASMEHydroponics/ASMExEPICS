//testing how the hell github works!

//display
#include "Arduino_GigaDisplay_GFX.h"

GigaDisplay_GFX display;  // create the object

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define TAN 0xd591

int displaySwitchPin = 50;
int displayFrequency = (2 * 1000);  //how often the display is updated [ms]

//storage
#include <Arduino_USBHostMbed5.h>
#include <DigitalOut.h>
#include <FATFileSystem.h>

USBHostMSD msd;
mbed::FATFileSystem usb("usb");

int logCount = 0;
int days = 0;
int hours = 0;
int logFrequency = (12 * 60 * 1000);  //how often data is logged [ms]

//sensors
#define PH_Serial Serial4  //physical 3
#define EC_Serial Serial3  //physical 2


float idealPH = 6.5;  //default ideal value
float idealEC = 675;  //default ideal value

float idealPHThreshold = .3;                      //how much PH error is allowed (+_ .25)
int pumpTime = 2000;                              //how long the pump doses at a time for [ms]
int sensorFrequency = (10 * 60 * 1000);           //how often more chemicals will be added (waits for them to disperse) [ms]
int thresholdValues[5] = { 500, 500, 500, 500 };  //threshold for water level sensors

int reservoirSensor = A5;

int floodFrequency = (5 * 1000);  //how often to check if system is flooding

int pumpPin = 1;       //pin pump relay is on
int PHUpPin = 3;       //pin phUp pump relay is on
int PHDownPin = 2;     //pin phDown pump relay is on
int NutrientsPin = 4;  //pin nutrients pump relay is on

String inputstring = "";      //a string to hold incoming data from the PC
String PH_sensorstring = "";  //a string to hold the data from the PH sensor
String EC_sensorstring = "";  //a string to hold the data from the EC sensor

float PH;  //used to hold a floating point number that is the pH
float EC;  //used to hold a floating point number that is the EC
float TDS;
float Salinity;
bool Flooding = false;  //system flooding status
int sensorValues[4];    //array of water level sensor readings

long long sensorTempTime = 0;
long long displayTempTime = 0;
long long logTempTime = 0;
long long floodingTempTime = 0;
long long timeTempCount = 0;

void processInput();
void updatePH();
void updateEC();
void checkFlooding();
void regulateLevels();
void updateDisplay();
void logData();

void setup() {
  Serial.begin(9600);  //set baud rate for the serial port between the PC and Arduino

  PH_Serial.begin(9600);  //set baud rate for the serial port between the Arduino and PH sensor
  EC_Serial.begin(9600);  //set baud rate for the serial port between the Arduino and EC sensor

  inputstring.reserve(10);      //set aside some bytes for receiving data from the PC
  PH_sensorstring.reserve(30);  //set aside some bytes for receiving data from PH sensor
  EC_sensorstring.reserve(30);  //set aside some bytes for receiving data from EC sensor

  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, HIGH);

  pinMode(reservoirSensor, INPUT);

  //display
  pinMode(displaySwitchPin, INPUT);

  display.begin();
  display.setRotation(1);

  pinMode(PA_15, OUTPUT);  //enable the USB-A port
  digitalWrite(PA_15, HIGH);

  delay(500);

  Serial.print("\nReady!\n");
}

void loop() {
  //for reading user commands
  if (Serial.available() > 0) {                //bc arduino cant do their job! (lets us read the message from the user)
    inputstring = Serial.readStringUntil(13);  //read the string until we see a <CR>
    processInput();
  }

  //for reading sensors
  if (PH_Serial.available() > 0) {         //if we see that the Atlas Scientific product has sent a character
    char inchar = (char)PH_Serial.read();  //get the char we just received
    PH_sensorstring += inchar;             //add the char to the var called sensorstring
    if (inchar == '\r') {                  //if the incoming character is a <CR>
      updatePH();
    }
  }

  if (EC_Serial.available() > 0) {         //if we see that the Atlas Scientific product has sent a character
    char inchar = (char)EC_Serial.read();  //get the char we just received
    EC_sensorstring += inchar;             //add the char to the var called sensorstring
    if (inchar == '\r') {                  //if the incoming character is a <CR>
      updateEC();
    }
  }

  if ((millis() - floodingTempTime) > floodFrequency) {
    checkFlooding();
    floodingTempTime = millis();
  }

  if ((millis() - sensorTempTime) > sensorFrequency) {
    regulateLevels();
    sensorTempTime = millis();
  }

  if ((millis() - displayTempTime) > displayFrequency) {
    if (digitalRead(displaySwitchPin)) {  //if the switch is on power on and update the screen
      digitalWrite(D74, HIGH);
      updateDisplay();
    } else {
      digitalWrite(D74, LOW);  //if the switch is off power down the screen
    }
    displayTempTime = millis();
  }

  if ((millis() - logTempTime) > logFrequency) {
    logData();
    logTempTime = millis();
  }

  if ((millis() - timeTempCount) > 60 * 60 * 1000) {
    // if ((millis() - timeTempCount) > 10*1000) {
    hours++;
    if (hours >= 24) {
      days += 1;
      hours -= 24;
    }
    timeTempCount = millis();
  }
}

void processInput() {
  int first_comma = inputstring.indexOf(',');  //find where the actual message begins

  if (inputstring.startsWith("PH")) {                         //if it begins with PH
    PH_Serial.print(inputstring.substring(first_comma + 1));  //send the rest of the message to PH sensor
    PH_Serial.print('\r');
  }

  else if (inputstring.startsWith("EC")) {                    //if it begins with EC
    EC_Serial.print(inputstring.substring(first_comma + 1));  //send the rest of the message to the EC sensor
    EC_Serial.print('\r');
  }

  else if (inputstring.startsWith("OUTPUT")) {  //if it begins with UPDATE or OUTPUT
    //give an update to the user about current values
    Serial.print("\n\nPH: ");
    Serial.print(PH);
    Serial.print("\nEC: ");
    Serial.print(EC);
    Serial.print("\nTDS: ");
    Serial.print(TDS);
    Serial.print("\nSalinity: ");
    Serial.print(Salinity);

    for (int i = 0; i < 4; i++) {
      sensorValues[i] = analogRead(i);  // Call readSensor() function for each sensor
      Serial.print("\n Sensor ");
      Serial.print(i);
      Serial.print(" - ");
      Serial.print(sensorValues[i]);
    }

    if (!digitalRead(reservoirSensor)) {
      Serial.print("\nReservoir sensor reads flooding\n");
    } else {
      Serial.print("Reservoir sensor reads NOT flooding\n");
    }
  }

  //command in looks like SETPH,6.5
  else if (inputstring.startsWith("SETPH")) {  //if it begins with UPDATE or OUTPUT
    inputstring = inputstring.substring(first_comma + 1);
    idealPH = inputstring.toFloat();

    Serial.print("\nSet PH: ");
    Serial.print(idealPH);
  }

  //command in looks like SETEC,600
  else if (inputstring.startsWith("SETEC")) {  //if it begins with UPDATE or OUTPUT
    inputstring = inputstring.substring(first_comma + 1);
    idealEC = inputstring.toFloat();

    Serial.print("\nSet EC: ");
    Serial.print(idealEC);
  }

  //command in looks like
  //SETTIME,[days],[hours]
  //ex. SETTIME,0,0
  //ex. SETTIME,5,13
  else if (inputstring.startsWith("SETTIME")) {
    int seperator;

    // Remove "SET TIME," from the input string
    inputstring = inputstring.substring(first_comma + 1);
    seperator = inputstring.indexOf(',');
    days = inputstring.substring(0, seperator).toInt();

    inputstring = inputstring.substring(seperator + 1);
    seperator = inputstring.indexOf(',');
    hours = inputstring.substring(0, seperator).toInt();

    Serial.print("\nDays: ");
    Serial.print(days);
    Serial.print(", Hours: ");
    Serial.print(hours);
  }

  //could optimize
  else if (inputstring.startsWith("PUMP,MAIN,1")) {
    Serial.print("Turning pump on\n");
    digitalWrite(pumpPin, 1);
  } else if (inputstring.startsWith("PUMP,MAIN,0")) {
    Serial.print("Turning pump off\n");
    digitalWrite(pumpPin, 0);
  }

  else if (inputstring.startsWith("PUMP,PH,UP")) {
    Serial.print("Adding PH up\n");
    digitalWrite(PHUpPin, 1);
    delay(pumpTime);
    digitalWrite(PHUpPin, 0);
  }

  else if (inputstring.startsWith("PUMP,PH,DOWN")) {
    Serial.print("Adding PH down\n");
    digitalWrite(PHDownPin, 1);
    delay(pumpTime);
    digitalWrite(PHDownPin, 0);
  }

  else if (inputstring.startsWith("PUMP,NUTRIENTS")) {
    Serial.print("Adding nutrients\n");
    digitalWrite(NutrientsPin, 1);
    delay(pumpTime);
    digitalWrite(NutrientsPin, 0);
  }

  else {
    Serial.println("\nHere are the available commands:");
    Serial.println("To set the ideal PH type:");
    Serial.println("SETPH,(ideal PH value)");
    Serial.println("To set the ideal EC type:");
    Serial.println("SETEC,(ideal EC value)");
    Serial.println("To set the clock type:");
    Serial.println("SETTIME,[day],[hour]");
    Serial.println("To manually operate the pumps:");
    Serial.println("PUMP,MAIN,[1 or 0] - this will change the state until another command or the system updates it");
    Serial.println("PUMP,PH,UP - this will only turn on for a short time");
    Serial.println("PUMP,PH,DOWN - this will only turn on for a short time");
    Serial.println("PUMP,NUTRIENTS - this will only turn on for a short time");
    Serial.println("To get a system update of all current values type:");
    Serial.println("OUTPUT");
    Serial.println("To send commands to the PH sensor (found in the guidebook or atlas scientific pdf) type:");
    Serial.println("PH,(comamnd)");
    Serial.println("To send commands to the EC sensor (found in the guidebook or atlas scientific pdf) type:");
    Serial.println("EC,(comamnd)\n");
  }

  inputstring = "";  //clear the input string for next time
}

void updatePH() {
  delay(10);
  //Serial.println(PH_sensorstring);

  if (isdigit(PH_sensorstring[0])) {  //if the first character in the string is a digit
    PH = PH_sensorstring.toFloat();   //update the PH float variable
  } else {
    Serial.println(PH_sensorstring);  //if its a message from the sensor (not a number) then print it to the user
  }
  PH_sensorstring = "";  //clear the string
}

void updateEC() {
  delay(10);
  //Serial.println(EC_sensorstring);

  int first_comma = EC_sensorstring.indexOf(',');
  int second_comma = EC_sensorstring.lastIndexOf(',');
  if (isdigit(EC_sensorstring[0])) {  //if the first character in the string is a digit
    EC = EC_sensorstring.substring(0, first_comma + 1).toFloat();
    TDS = EC_sensorstring.substring(first_comma + 1, second_comma + 1).toFloat();
    Salinity = EC_sensorstring.substring(second_comma + 1).toFloat();
  } else {
    Serial.println(EC_sensorstring);  //if its a message from the sensor (not a number) then print it to the user
  }
  EC_sensorstring = "";  //clear the string
}

void checkFlooding() {
  //overflow analog section
  //update sensor values
  for (int i = 0; i < 4; i++) {
    sensorValues[i] = analogRead(i);  // Call readSensor() function for each sensor
    // Serial.print("\n Sensor ");
    // Serial.print(i);
    // Serial.print(" - ");
    // Serial.print(sensorValues[i]);
  }
  //check if they are flooding
  bool tempFloodFlag = false;
  for (int i = 0; i < 4; i++) {
    if (sensorValues[i] > thresholdValues[i]) {
      tempFloodFlag = true;
    }
  }
  if (tempFloodFlag) {
    Flooding = true;
  } else {
    Flooding = false;
  }

  //turn off pump if flooding
  if (Flooding || !digitalRead(reservoirSensor)) {
  // if (Flooding) {
    Serial.print("\nSystem Flooding\n");
    digitalWrite(pumpPin, 0);
  } else {
    digitalWrite(pumpPin, 1);
  }

  // if (!digitalRead(reservoirSensor)) {
  //   Serial.print("\nReservoir sensor reads flooding\n");
  // }
  // else {
  //   Serial.print("Reservoir sensor reads NOT flooding\n");
  // }
}

void regulateLevels() {
  //regulating ph section
  if (PH < (idealPH - .5 * idealPHThreshold)) {
    Serial.print("\nIncreasing PH");
    digitalWrite(PHUpPin, HIGH);
    delay(pumpTime);
    digitalWrite(PHUpPin, LOW);
  } else if (PH > (idealPH + .5 * idealPHThreshold)) {
    Serial.print("\nDecreasing PH");
    digitalWrite(PHDownPin, HIGH);
    delay(pumpTime);
    digitalWrite(PHDownPin, LOW);
  }

  //regulating EC section
  if (EC < idealEC) {
    Serial.print("\nAdding nutrients");
    digitalWrite(NutrientsPin, HIGH);
    delay(pumpTime);
    digitalWrite(NutrientsPin, LOW);
  }
}

void updateDisplay() {
  //screen resolution 480x800
  //default text size is 7 pixels tall
  display.fillScreen(TAN);

  display.setTextSize(5);

  //ph
  display.setCursor(25, 25);
  display.setTextColor(RED);
  display.print("PH: ");
  display.print(PH);
  display.print(" | ");
  display.print(idealPH);

  //ec
  display.setCursor(25, 111);
  display.setTextColor(BLUE);
  display.print("EC: ");
  display.print(EC);
  display.print(" | ");
  display.print(idealEC);

  //tds
  display.setCursor(25, 197);
  display.setTextColor(BLUE);
  display.print("TDS: ");
  display.print(TDS);

  //salinity
  display.setCursor(25, 283);
  display.print("Salinity: ");
  display.print(Salinity);

  //time
  display.setTextSize(3);
  display.setTextColor(BLACK);
  display.setCursor(25, 434);
  display.print("Time: ");
  display.print(days);
  display.print(" days, ");
  display.print(hours);
  display.print(" hours | ");
  display.print(logCount);
  display.print(" data logs");

  //overflow
  for (int i = 0; i < 4; i++) {
    if (sensorValues[i] <= thresholdValues[i]) {
      display.fillCircle(735, 65 + (i)*115, 40, GREEN);  //was 117
    } else {
      display.fillCircle(735, 65 + (i)*115, 40, RED);
    }
  }
}

void logData() {
  if (msd.connect()) {
    if (usb.mount(&msd)) {

      mbed::fs_file_t file;
      struct dirent *ent;

      FILE *f = fopen("/usb/Data.csv", "a");
      if (f != NULL) {

        logCount++;
        if (logCount == 1) {
          fprintf(f, "%s", "Log, Days, Hours, PH, EC, TDS, Salinity\n");
        }
        fprintf(f, "%d", logCount);
        fprintf(f, "%s", ",");
        fprintf(f, "%d", days);
        fprintf(f, "%s", ",");
        fprintf(f, "%d", hours);
        fprintf(f, "%s", ",");
        fprintf(f, "%.3f", PH);
        fprintf(f, "%s", ",");
        fprintf(f, "%.f", EC);
        fprintf(f, "%s", ",");
        fprintf(f, "%.f", TDS);
        fprintf(f, "%s", ",");
        fprintf(f, "%.2f", Salinity);
        fprintf(f, "%s", "\n");

        fflush(f);

        fclose(f);


      } else {
        Serial.print("\nData log failed");
      }
    }
  } else {
    Serial.print("\nNo USB detected!");
  }
}