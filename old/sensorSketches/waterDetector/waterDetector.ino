// const int pin = 7;
// int Water_level = 0;


// void setup() {
//   pinMode(pin, INPUT);
//   Serial.begin(9600);
// }

// void loop() {
//   Water_level = digitalRead(pin);

//   if(Water_level == 1)
//   {
//     Serial.println("Water Detected");
//   }
//   else{
//     Serial.println("Water Not Detected");
//   }

//   //Serial.println("Water Detection:");
//   //Serial.println(Water_level);
//   delay(1000);
// }

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    Serial.println("hi");
    delay(1000);
}