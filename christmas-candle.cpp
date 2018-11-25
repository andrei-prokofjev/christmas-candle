#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

#include "christmas-candle.h"
#include "Wdt.h"

Wdt wdt;

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

int count_high = 0;
int count_low = 0;

void setup() {
	Serial.begin(57600);
	Serial.println("Initializing...");
	delay(100);
	pinMode(LED_BUILTIN, OUTPUT);

	digitalWrite(LED_BUILTIN, LOW);

	for (int i = 0; i < sizeof(candles); i++) {
		pinMode(candles[i], OUTPUT);
	}

	Serial.println("Initialization complete.");
	delay(100);
}

void loop() {

	if (wdt.isSleep()) {
		return;
	}

//	blink(20);

	int val = analogRead(SENSOR_PIN);

	// check each 10 min
	if (val > 700) {
		if (count_high < 36) { // 6h
			if (count_high == 0) {
				swith(HIGH);
			}
			count_high++;
		} else {
			swith(LOW);
			count_low = 0;
		}
	} else {
		if (count_high > 0) {
			count_low++;
			if (count_low > 60) {
				count_high = 0;
			}
		}
	}

	Serial.print(val);
	Serial.println();

	wdt.enterSleep();
}

void say_hello() {
	swith(HIGH);
	delay(100);
	swith(LOW);
}

void swith(int val) {
	for (int i = 0; i < sizeof(candles); i++) {
		delay(30);
		digitalWrite(candles[i], val);
	}
}

