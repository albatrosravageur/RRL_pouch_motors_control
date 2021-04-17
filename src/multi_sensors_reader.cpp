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
#include <Arduino.h>

// the constant U_DEG means the results are given in degrees
#define U_DEG 3

// declare an array of sensors (addresses found with find_adress.ino)
#define NUM_SENSORS 4

// Choose verbose of not
#define verbose

// Choose performance estimation of not
//#define performance

AMS_AS5048B sensors[NUM_SENSORS]; // = {AMS_AS5048B(0x40), AMS_AS5048B(0x48), AMS_AS5048B(0xBE), AMS_AS5048B(0xC8)};
double angles[NUM_SENSORS];
unsigned long time = 0;

void I2C_scanner()
{
    byte error, address;
    int nDevices;

    Serial.println("Scanning...");

    nDevices = 0;
    for (int i = 0x30; i < 0xFF; i++)
    {
        AMS_AS5048B mysensor(i);
        mysensor.begin();
        uint8_t adress = mysensor.addressRegR();
        if (adress != 255)
        {
            Serial.print("I2C device found at address 0x");
            Serial.print(i, HEX);
            Serial.println("  !");
            sensors[nDevices].addressRegW(i); // choose this adress for device i
            nDevices++;
        }
        delay(5);
    }

    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    if (nDevices != NUM_SENSORS)
        Serial.println("Only " + String(nDevices) + " sensors were found!");
    else
        Serial.println("done\n");
}

void setup()
{
    //Start serial
    Serial.begin(9600);
    while (!Serial)
        ; //wait until Serial ready

    I2C_scanner(); //find the devices

    for (int i = 0; i < NUM_SENSORS; i++)
    {
        sensors[i].begin();
    }
#ifdef verbose
    Serial.println("Let's start reading Hall sensors!");
#endif

#ifdef performance
    time = micros();
#endif
}

void loop()
{

    for (int j = 0; j < 1000; j++)
    {
        for (int i = 0; i < NUM_SENSORS; i++)
        {
            angles[i] = sensors[i].angleR(U_DEG, true);
        }

#ifdef verbose
        for (int i = 0; i < NUM_SENSORS; i++)
        {
            Serial.print(angles[i]);
            Serial.print("    ");
        }
        Serial.println("--------");
#endif

#ifndef verbose
        for (int i = 0; i < NUM_SENSORS; i++)
        {
            Serial.println(String(i) + " " + String(angles[i]));
        }
#endif
        delayMicroseconds(50000);
    }

#ifdef performance
    Serial.print("Final freq for 1000x4 datapoints: ");
    Serial.print(1000000000.0 / ((double(micros() - time))));
    Serial.println(" Hz");

    delay(20000);
    time = micros();
#endif
}
