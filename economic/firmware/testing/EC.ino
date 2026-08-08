void setup() {
  // Start serial communication at 9600 bits per second
  Serial.begin(9600);
}

void loop() {
  // Read the input on analog pin 0
  int sensorValue = analogRead(A0);

  // Convert the reading (0-1023) to voltage (0-5V)
  float voltage = sensorValue * (5.0 / 1023.0);

  // Print out the values
  Serial.print("Raw: ");
  Serial.print(sensorValue);
  Serial.print(" | Voltage: ");
  Serial.println(voltage);

  // Wait 500 milliseconds so the screen doesn't scroll too fast
  delay(500);
}