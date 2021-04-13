#include <Arduino.h>

#define PWR_PIN1 1
#define PWR_PIN2 4
#define PWR_PIN3 7
#define PWR_PIN4 10

#define PWM_PIN1 2
#define PWM_PIN2 5
#define PWM_PIN3 8
#define PWM_PIN4 11

#define GND_PIN1 3
#define GND_PIN2 6
#define GND_PIN3 9
#define GND_PIN4 12

#define nb_samples 10 // the highest the most precise, but also the slowest

int pwm_value1;
int pwm_value2;
int pwm_value3;
int pwm_value4;

#ifdef demo_mode
unsigned long time;
#endif

void setup()
{
	// Setup of reading pins
	pinMode(PWM_PIN1, INPUT);
	pinMode(PWM_PIN2, INPUT);
	pinMode(PWM_PIN3, INPUT);
	pinMode(PWM_PIN4, INPUT);

	// Setup of 5V pins
	pinMode(PWR_PIN1, OUTPUT);
	pinMode(PWR_PIN2, OUTPUT);
	pinMode(PWR_PIN3, OUTPUT);
	pinMode(PWR_PIN4, OUTPUT);
	digitalWrite(PWR_PIN1, HIGH);
	digitalWrite(PWR_PIN2, HIGH);
	digitalWrite(PWR_PIN3, HIGH);
	digitalWrite(PWR_PIN4, HIGH);

	// Setup of ground pins
	pinMode(GND_PIN1, OUTPUT);
	pinMode(GND_PIN2, OUTPUT);
	pinMode(GND_PIN3, OUTPUT);
	pinMode(GND_PIN4, OUTPUT);
	pinMode(GND_PIN1, LOW);
	pinMode(GND_PIN2, LOW);
	pinMode(GND_PIN3, LOW);
	pinMode(GND_PIN4, LOW);

	Serial.begin(9600);

#ifdef demo_mode
	time = micros();
	for (int i = 0; i < 1000; i++)
	{
		pwm_value1 = pulseIn(PWM_PIN1, HIGH);
	}

	Serial.print("It takes ");
	Serial.print((micros() - time) / 1000);
	Serial.print("microseconds to read PWM");
	Serial.flush();

	for (int i = 0; i < 5; i++)
	{
		delay(1000);
		Serial.println(".");
	}
#endif
}

void loop()
{
	// Reinitalize values
	pwm_value1 = 0;
	pwm_value2 = 0;
	pwm_value3 = 0;
	pwm_value4 = 0;

	// Average results over a given amount of samples
	for (int i = 0; i < nb_samples; i++)
	{
		pwm_value1 += pulseIn(PWM_PIN1, HIGH) / nb_samples;
		pwm_value2 += pulseIn(PWM_PIN2, HIGH) / nb_samples;
		pwm_value3 += pulseIn(PWM_PIN3, HIGH) / nb_samples;
		pwm_value4 += pulseIn(PWM_PIN4, HIGH) / nb_samples;
	}

#ifdef demo_mode
	// Display the results
	Serial.print("A1 value is ");
	Serial.println(pwm_value1);
	Serial.print("A2 value is ");
	Serial.println(pwm_value2);
	Serial.print("A3 value is ");
	Serial.println(pwm_value3);
	Serial.print("A4 value is ");
	Serial.println(pwm_value4);
	Serial.println("\n --------------");
#endif

#ifndef demo_mode
	// Return the read values to the computer 
	// as one chain of characters.
	Serial.print(pwm_value1);
	Serial.print(" ");
	Serial.print(pwm_value2);
	Serial.print(" ");
	Serial.print(pwm_value3);
	Serial.print(" ");
	Serial.print(pwm_value4);
	Serial.flush();
#endif
	delay(200);
}
