#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

#include "christmas-candle.h"
#include "LowPower.h"

#define DEBUG

const int ON = 1;
const int OFF = 0;

const int _10min = 75 * 8;
const int _hour = 6 * _10min;

const int MAX_NIGHT_COUNT = 6 * _hour;
const unsigned int MAX_PAUSE_COUNT =  12 * _hour;

uint8_t led1 = 7;
uint8_t led2 = 6;
uint8_t led3 = 5;
uint8_t led4 = 8;
uint8_t led5 = 4;
uint8_t led6 = 9;
uint8_t led7 = 10;
uint8_t led8 = 11;
uint8_t led9 = 12;

uint8_t candles[] = { led1, led2, led3, led4, led5, led6, led7, led8, led9 };

int night_count;
unsigned int pause_count;

void setup() {
	Serial.begin(9600);
	Serial.println("Initializing...");

	delay(100);
	pinMode(LED_BUILTIN, OUTPUT);

	digitalWrite(LED_BUILTIN, LOW);

	for (int i = 0; i < sizeof(candles); i++) {
		pinMode(candles[i], OUTPUT);
	}

	night_count = 0;
	pause_count = MAX_PAUSE_COUNT;

	Serial.println("Initialization complete.");

	delay(100);
}

void loop() {

	LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);

	int val = analogRead(SENSOR_PIN);

#ifdef DEBUG_
	Serial.print("sensor: ");
	Serial.print(val);
	Serial.print("  night: ");
	Serial.print(night_count);
	Serial.print("/");
	Serial.print(MAX_NIGHT_COUNT);
	Serial.print("   pause: ");
	Serial.print(pause_count);
	Serial.print("/");
	Serial.println(MAX_PAUSE_COUNT);
#endif

	if (pause_count == MAX_PAUSE_COUNT) {
		if (val > 700) {
			if (digitalRead(led1) == OFF) {
				swith(ON);
			}

			night_count++;

			if (night_count == MAX_NIGHT_COUNT) {
				swith(OFF);
				pause_count = 0;
			}
		} else {
			swith(OFF);
		}
	} else {
		if (++pause_count == MAX_PAUSE_COUNT) {
			night_count = 0; // can be switch on
		}
	}
#ifdef DEBUG
	delay(200);
#endif
}

void swith(int val) {
	for (int i = 0; i < sizeof(candles); i++) {
		delay(30);
		digitalWrite(candles[i], val);
	}
}

