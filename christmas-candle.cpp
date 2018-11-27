#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

#include "christmas-candle.h"
#include "Wdt.h"

#define ON 0x1
#define OFF 0x0

#define MAX_NIGHT_COUNT 4 // 6h
#define MAX_PAUSE_COUNT 4 // 12h

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

int night_count = 0;
int pause_count = MAX_PAUSE_COUNT;

void setup() {
	Serial.begin(115200);
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

	int val = analogRead(SENSOR_PIN);
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


	if (pause_count == MAX_PAUSE_COUNT) {
		if (val > 700) {
			if (night_count == 0){
				swith(ON);
			}

			night_count++;

			if (night_count % 6 == 0) {
				say_hello();
			}

			if (night_count == MAX_NIGHT_COUNT) {
				swith(OFF);
				pause_count = 0;
			}
		}
	} else {
		if (++pause_count == MAX_PAUSE_COUNT) {
			Serial.println("pause complete");
			night_count = 0; // can be switch on
		}
	}

	delay(50);

	wdt.enterSleep();
}

bool isNightNow() {
	return night_count < MAX_NIGHT_COUNT;
}

bool isPause() {
	return pause_count < MAX_PAUSE_COUNT;
}

void say_hello() {
	swith(ON);
	delay(100);
	swith(OFF);
}

void swith(int val) {
	for (int i = 0; i < sizeof(candles); i++) {
		delay(30);
		digitalWrite(candles[i], val);
	}
}

