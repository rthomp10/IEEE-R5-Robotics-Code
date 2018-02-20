int motorPin = 13;
int speed = 10;

void setup() 
{ 
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Speed 0 to 255");
} 
 
 
void loop() 
{ 
      if( Serial.read() == '1')
        speed += 50;
      if( Serial.read() == '0' )
        speed = speed - 50;

      analogWrite( motorPin, speed);
} 
