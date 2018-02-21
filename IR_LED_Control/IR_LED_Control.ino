#include <IRremote.h>
#include <IRremoteInt.h>

IRrecv receiver(2); //pin where IR receiver inputs value
decode_results IRnum; //Holds value retrived by IR sensor
unsigned int remoteNum; //Will determine what LED will turn on
bool powerToggle = false; //Power toggle switch

void setup() 
{
  Serial.begin(9600); //Set up device for inputting information
  receiver.enableIRIn(); //Enable IR input

  //Initialize Pins 10-13 for LED strip
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

}

void loop() 
{
  if(receiver.decode(&IRnum)) //Returns results address into a value
  {
    Serial.println(IRnum.value, DEC); //Turns value into DEC value (also here for debugging)
    remoteNum = IRnum.value; //Send value to remoteNum

    if(remoteNum == 16753245 && !(powerToggle))
    {
      powerToggle = 1;
    }
    else if(remoteNum == 16753245 && powerToggle)
    {
      powerToggle = 0;
    }

    if(powerToggle)
    {
      if(remoteNum == 16738455) //Turn on color on PIN10
      {
        digitalWrite(10, HIGH);
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);
      }
      else if(remoteNum == 16724175) //Turn on color on PIN11
      {
        digitalWrite(10, LOW);
        digitalWrite(11, HIGH);
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);
      }
      else if(remoteNum == 16716015) //Turn on color on PIN12
      {
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        digitalWrite(12, HIGH);
        digitalWrite(13, LOW);
      }
      else if(remoteNum == 16728765) //Turn on color on PIN13
      {
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        digitalWrite(13, HIGH);
      }
    }
    
    receiver.resume(); //The receive can now take a command
  }
}
