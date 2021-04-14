/**************************************************************************/
/*!
    @file     read_simple_angle.ino
    @author   SOSAndroid (E. Ha.)
    @license  BSD (see license.txt)

	read a simple angle from AS5048B over I2C bus

    @section  HISTORY

    v1.0 - First release
*/
/**************************************************************************/

#include <ams_as5048b.h>

//unit consts
#define U_RAW 1
#define U_TRN 2
#define U_DEG 3
#define U_RAD 4
#define U_GRAD 5
#define U_MOA 6
#define U_SOA 7
#define U_MILNATO 8
#define U_MILSE 9
#define U_MILRU 10

AMS_AS5048B mysensor;

void setup() {

	//Start serial
	Serial.begin(9600);
	while (!Serial) ; //wait until Serial ready

	//consider the current position as zero
	//mysensor.setZeroReg();
	for(int i=0x30;i<0xFF;i++){
		AMS_AS5048B mysensor(i);
		mysensor.begin();
		uint8_t adress = mysensor.addressRegR();
		if (adress != 255){
			Serial.println( "\n ----------------------- \n \n Adress "+ String(i)+" : "+String(adress) + "\n -----------");
		    delay(2000);
		}
		delay(5);
	}
}

void loop() {
	//print to serial the raw angle and degree angle every 2 seconds
	//print 2 times the exact same angle - only one measurement
	Serial.println("Programme fini");
	delay(3000);
}
