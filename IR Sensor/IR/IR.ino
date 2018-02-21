#include <IRremote.h>
#include <IRremoteInt.h>

  IRrecv receiver(2);
  decode_results results;

void setup() 
{
  Serial.begin(9600);
  receiver.enableIRIn();
}

void loop() 
{
  if(receiver.decode(&results))
  {
     Serial.println(results.value, HEX);
     receiver.resume();
  }
}
