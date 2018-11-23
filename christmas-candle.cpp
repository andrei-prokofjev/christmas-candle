#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

#include "christmas-candle.h"
#include "Wdt.h"

volatile int f_wdt = 1;

Wdt wdt;

int cadles[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

ISR(WDT_vect) {
	if (f_wdt == 0) {
		f_wdt = 1;
	}
}

void setup() {
	Serial.begin(9600);
	Serial.println("Initializing...");
	delay(100);
	pinMode(LED_BUILTIN, OUTPUT);

	Serial.println("Initialization complete.");
	delay(100);
}

void loop() {
	if (f_wdt != 1) {
		return;
	}

	blink(20);

	int val = analogRead(SENSOR_PIN);
	Serial.println(val);

	f_wdt = 0;

	wdt.enterSleep();
}





void say_hello() {


}

