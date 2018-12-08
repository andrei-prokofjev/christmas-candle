#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

#include "christmas-candle.h"
#include "LowPower.h"
#include "pins_candle.h"


#define DEBUG


const int _10min = 75;
const int _hour = 6 * _10min;

const int MAX_NIGHT_COUNT = 6 * _hour;
const int MAX_PAUSE_COUNT =  12 * _hour;


uint8_t candles[] = { LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7, LED_8, LED_9 };

int night_count;
int pause_count;

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

#ifdef DEBUG
	printState(val);
#endif

	if (pause_count == MAX_PAUSE_COUNT) {
		if (val > 750) {
			if (digitalRead(LED_1) == LOW) {
				swith(HIGH);
			}

			if (++night_count == MAX_NIGHT_COUNT) {
				swith(LOW);
				pause_count = 0;
			}
		} else {
			swith(LOW);
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

void printState(int val) {
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
}

