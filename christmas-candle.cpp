#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

#include "christmas-candle.h"
#include "Wdt.h"

Wdt wdt;

uint8_t led1 = 1;
uint8_t led2 = 1;
uint8_t led3 = 1;
uint8_t led4 = 1;
uint8_t led5 = 1;
uint8_t led6 = 1;
uint8_t led7 = 1;
uint8_t led8 = 1;
uint8_t led9 = 1;

uint8_t candles[] = { led1, led2, led3, led4, led5, led6, led7, led8, led9 };

void setup() {
	Serial.begin(9600);
	Serial.println("Initializing...");
	delay(100);
	pinMode(LED_BUILTIN, OUTPUT);

	for (int i = 0; i < sizeof(candles); i++) {
		pinMode(candles[i], OUTPUT);
		analogWrite(candles[i], 0);
	}

	Serial.println("Initialization complete.");
	delay(100);

	say_hello();
}

void loop() {
	if (wdt.isSleep()) {
		return;
	}

	blink(20);

	int val = analogRead(SENSOR_PIN);
	Serial.println(val);

	wdt.enterSleep();
}

void say_hello() {

}

