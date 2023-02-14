
void setup() {
  // put your setup code here, to run once:
pinMode(7,OUTPUT);
}
int x=21;
void loop() {
  x = pump(x);
}

double pump(int a)
{
  if(a > 20) //runs for 1 iteration
{
digitalWrite(7,HIGH);
delay(2000); 
digitalWrite(7,LOW);
delay(2000);
a = a-5;
return a;
}
}
