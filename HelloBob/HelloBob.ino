#include <Adafruit_TCS34725.h>
#include <Stepper.h>
#include <Wire.h>
#include <math.h>

byte i2cWriteBuffer[10];
byte i2cReadBuffer[10];

//RGB Sensor Methods and Defininitions definitions
#define SensorAddressWrite 0x29 //
#define SensorAddressRead 0x29 // 
#define EnableAddress 0xa0 // register address + command bits
#define ATimeAddress 0xa1 // register address + command bits
#define WTimeAddress 0xa3 // register address + command bits
#define ConfigAddress 0xad // register address + command bits
#define ControlAddress 0xaf // register address + command bits
#define IDAddress 0xb2 // register address + command bits
#define ColorAddress 0xb4 // register address + command bits

#define RELAY_MAGNET  6

//color sensor functions
void Writei2cRegisters(byte, byte);
byte Readi2cRegisters(int, byte);
void init_TCS34725(void);
void get_TCS34725ID(void);
char get_Colors(void);

//terminal clean-up
void clearScreen(void);

//Stepper control
const float STEPS_PER_REV = 32; // Number of steps per internal motor revolution 
const float GEAR_RED = 64;	  //  Amount of Gear Reduction
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;	  // Number of steps per geared output rotation
int speedVar = 100; 	// Define Variables
int StepsRequired;	// Number of Steps Required

// Create Instance of Stepper Class
// Specify Pins used for motor coils
// The pins used are 8,9,10,11 
// Connected to ULN2003 Motor Driver In1, In2, In3, In4 
// Pins entered in sequence 1-3-2-4 for proper step sequencing
Stepper steppermotor(STEPS_PER_REV, 10, 12, 11, 13);


// the setup routine runs once when you press reset:
void setup() {
      Serial.begin(115200);
      Wire.begin();
      pinMode(RELAY_MAGNET, OUTPUT);
      init_TCS34725();
      get_TCS34725ID();  // get the device ID, this is just a test to see if we're connected
}

// the loop routine runs over and over again forever:
void loop() {
	Serial.println("");
	if( Serial.read() == 'a' )
	{
	  digitalWrite(RELAY_MAGNET, LOW);
	  delay(100);
	}
	digitalWrite(RELAY_MAGNET, HIGH);

	Serial.println("");
	if(get_Colors() == 'r')
	{
		digitalWrite(RELAY_MAGNET, LOW);
	}
	delay(40);
	
   // Rotate CCW 1/2 turn quickly
    //StepsRequired  =  STEPS_PER_OUT_REV / 2;   
    //steppermotor.setSpeed(1000);  
    //steppermotor.step(StepsRequired);
    clearScreen();
}
//end of main loop

/*  
Send register address and the byte value you want to write the magnetometer and 
loads the destination register with the value you send
*/
void Writei2cRegisters(byte numberbytes, byte command)
{
    byte i = 0;

    Wire.beginTransmission(SensorAddressWrite);   // Send address with Write bit set
    Wire.write(command);                          // Send command, normally the register address 
    for (i=0;i<numberbytes;i++)                       // Send data 
      Wire.write(i2cWriteBuffer[i]);
    Wire.endTransmission();

    delayMicroseconds(100);      // allow some time for bus to settle      
}

//Sends register address to this function and it returns byte value
//for the magnetometer register's contents 
byte Readi2cRegisters(int numberbytes, byte command)
{
   byte i = 0;

    Wire.beginTransmission(SensorAddressWrite);   // Write address of read to sensor
    Wire.write(command);
    Wire.endTransmission();

    delayMicroseconds(100);      // allow some time for bus to settle      

    Wire.requestFrom(SensorAddressRead,numberbytes);   // read data
    for(i=0;i<numberbytes;i++)
      i2cReadBuffer[i] = Wire.read();
    Wire.endTransmission();   

    delayMicroseconds(100);      // allow some time for bus to settle      
}  

void init_TCS34725(void)
{
  i2cWriteBuffer[0] = 0x10;
  Writei2cRegisters(1,ATimeAddress);    // RGBC timing is 256 - contents x 2.4mS =  
  i2cWriteBuffer[0] = 0x00;
  Writei2cRegisters(1,ConfigAddress);   // Can be used to change the wait time
  i2cWriteBuffer[0] = 0x00;
  Writei2cRegisters(1,ControlAddress);  // RGBC gain control
  i2cWriteBuffer[0] = 0x03;
  Writei2cRegisters(1,EnableAddress);    // enable ADs and oscillator for sensor  
}

void get_TCS34725ID(void)
{
  Readi2cRegisters(1,IDAddress);
  if (i2cReadBuffer[0] = 0x44)
    Serial.println("TCS34725 is present");    
  else
    Serial.println("TCS34725 not responding");    
}

//Reads the register values for clear, red, green, and blue.
char get_Colors(void)
{
  unsigned int clear_color = 0;
  unsigned int red_color = 0;
  unsigned int green_color = 0;
  unsigned int blue_color = 0;
  
  unsigned int clear_offset = 0;
  unsigned int red_offset = 0;
  unsigned int green_offset = 0;
  unsigned int blue_offset = 0;

  Readi2cRegisters(8,ColorAddress);
  clear_color = (unsigned int)(i2cReadBuffer[1]<<8) + clear_offset + (unsigned int)i2cReadBuffer[0];
  red_color = (unsigned int)(i2cReadBuffer[3]<<8) + red_offset + (unsigned int)i2cReadBuffer[2];
  green_color = (unsigned int)(i2cReadBuffer[5]<<8) + green_offset + (unsigned int)i2cReadBuffer[4];
  blue_color = (unsigned int)(i2cReadBuffer[7]<<8) + blue_offset + (unsigned int)i2cReadBuffer[6];

  // send register values to the serial monitor 

  Serial.print("clear=");
  Serial.println(clear_color, DEC);    
  Serial.print("red=");
  Serial.println(red_color, DEC);    
  Serial.print("green=");
  Serial.println(green_color, DEC);    
  Serial.print("blue=");
  Serial.println(blue_color, DEC);


 // Basic RGB color differentiation can be accomplished by comparing the values and the largest reading will be 
 // the prominent color

  if((red_color>blue_color) && (red_color>green_color)){
	  Serial.println("detecting red");
	  return 'r';
  }
  else if((green_color>blue_color) && (green_color>red_color)){
    Serial.println("detecting green");
	return 'g';
  }
  else if((blue_color>red_color) && (blue_color>green_color)){
    Serial.println("detecting blue");
	return 'b';
  }
  else{
    Serial.println("color not detectable");
	return 'c';
  }
}

void clearScreen(){
	  Serial.write(27);       // ESC command
	  Serial.print("[2J");    // clear screen command
	  Serial.write(27);
	  Serial.print("[H");     // cursor to home command
}

