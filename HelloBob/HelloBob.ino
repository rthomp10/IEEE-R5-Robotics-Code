
/*
 Stepper Motor Control - one step at a time

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor will step one step at a time, very slowly.  You can use this to
 test that you've got the four wires of your stepper wired to the correct
 pins. If wired correctly, all steps should be in the same direction.

 Use this also to count the number of steps per revolution of your motor,
 if you don't know it.  Then plug that number into the oneRevolution
 example to see if you got it right.

 Created 30 Nov. 2009
 by Tom Igoe

 */

#include <Stepper.h>

int Electromagnet = 0;
int LED = 13;

// the setup routine runs once when you press reset:
void setup() {
    // initialize the digital pin as an output.
    pinMode(Electromagnet, OUTPUT);
    pinMode(LED, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
    digitalWrite(Electromagnet, HIGH);  // turn the Electromagnet on (HIGH is the voltage level)
    digitalWrite(LED, HIGH);            // turn the LED on (HIGH is the voltage level)
    delay(1000);                        // wait for a second
    digitalWrite(Electromagnet, LOW);   // turn the Electromagnet off by making the voltage LOW
    digitalWrite(LED, LOW);             // turn the LED off by making the voltage LOW
    delay(1000);                        // wait for a second
}

