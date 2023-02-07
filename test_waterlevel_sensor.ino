const int pin = 7;
int Water_level = 0;

void setup() {
  pinMode(pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  Water_level = digitalRead(pin);
  Serial.println(Water_level);
  delay(200);
}
