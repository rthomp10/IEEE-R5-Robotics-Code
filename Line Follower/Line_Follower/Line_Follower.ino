#include <Wire.h>
#define uchar unsigned char
uchar t;
//void send_data(short a1,short b1,short c1,short d1,short e1,short f1);
uchar data[16];

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  t = 0;
}
void loop()
{
  Wire.requestFrom(9, 16);    // request 16 bytes from slave device #9
  while (Wire.available())   // slave may send less than requested
  {
    data[t] = Wire.read(); // receive a byte as character
    if (t < 15)
      t++;
    else
      t = 0;
  }

  //Uses data[whatever] as the only variables so we can save some memory
  if(data[0] < data[6] || data[2] < data[6] || data[4] < data[6] || data[0] < data[8] || data[2] < data[8] || data[4] < data[8]) //if left 3 is less than middle 2
  {
    //GIVE MORE POWER TO RIGHT MOTOR
  }
  else if(data[10] < data[6] || data[12] < data[6] || data[14] < data[6] || data[10] < data[8] || data[12] < data[8] || data[14] < data[8]) //if right 3 is less than middle 2
  {
    //GIVE MORE POWER TO LEFT MOTOR
  }
  else //if middle 2 is less than anything else
  {
    //POWER OF LEFT MOTOR = POWER OF RIGHT MOTOR
  }
  

  for(int i = 0; i < 8; i++)
  {
    Serial.print(data[2*i]);
    Serial.print(" ");
  }
  Serial.println("");
  delay(1000);
}
