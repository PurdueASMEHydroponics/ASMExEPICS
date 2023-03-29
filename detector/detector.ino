int pin = 7;
int Water_level = 0;

void setup() {
    pinMode(pin, INPUT);
    Serial.begin(9600);

}

void loop() {
  detector();
}


void detector()
{
   Water_level = digitalRead(pin);

    if(Water_level == 1)
    {
        Serial.println("Water Detected");
    }
    else
    {
        Serial.println("Water Not Detected");
    }
    delay(1000);
}

