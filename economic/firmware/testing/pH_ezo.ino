#include <SoftwareSerial.h>

SoftwareSerial phSerial(0, 1); // RX (D2), TX (D3)

void setup() {
  Serial.begin(9600);    // To computer
  phSerial.begin(9600);  // To sensor
  delay(1000);           // Let sensor stabilize
  Serial.println("Starting pH Readings...");
}

void loop() {
  phSerial.print("R\r"); // Send the "Read" command
  
  // Wait a moment for the sensor to process and send data back
  delay(1000); 

  while (phSerial.available() > 0) {
    char c = phSerial.read();
    Serial.print(c); // Print the sensor response to the monitor 
  }
  
  Serial.print("\n"); 
  
  // The sensor usually sends the value followed by a carriage return
  // so we don't need to add an extra Serial.println() here.
}