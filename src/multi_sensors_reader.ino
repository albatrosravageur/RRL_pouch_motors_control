/**************************************************************************/
/*!
    @file     xplane_dials.ino
    @author   @DavidHowlett (David Howlett, Peter Dobson)
    @license  BSD (see license.txt)

    This example reads an array of 4 sensors and prints the results to serial.
    This was originally developed to upload dial positions to a flight simulator
    called X-Plane using a modified version of Arduino called Teensyduino.
    The Teensyduino specific code has now been commented out.
    If you want to enable the live upload of values to xplane you need to:
        - Download and install Teensyduino
        - Set the board type to Teensy++ 2.0 (or which ever version of Teensy you are using)
        - Set the USB type to "Flight Sim Controls" in the tools menu (this adds some definitions)
        - Uncomment the marked lines


    @section  HISTORY

    v1.0.0 - First release
    v1.0.1 - Now works without Teensyduino, also added build instructions
*/
/**************************************************************************/

#include <ams_as5048b.h>

// the constant U_DEG means the results are given in degrees
#define U_DEG 3

// declare an array of sensors (addresses found with find_adress.ino)
# define NUM_SENSORS 4
AMS_AS5048B sensors[NUM_SENSORS] = {AMS_AS5048B(0x40), AMS_AS5048B(0x48), AMS_AS5048B(0xBE), AMS_AS5048B(0xC8)};


void setup() {
    //Start serial
    Serial.begin(9600);
    while (!Serial) ; //wait until Serial ready


    for(int i=0;i<NUM_SENSORS;i++){
        sensors[i].begin();
    }
}

void loop() {

    for(int i=0;i<NUM_SENSORS;i++){
        Serial.print("Sensor ");
        Serial.print(i);
        Serial.print(" | auto gain: ");
        Serial.print(sensors[i].getAutoGain());
        Serial.print(" | angle: ");
        Serial.println(sensors[i].angleR(U_DEG,true));
    }
    Serial.println("--------");

    delay(500);
}
