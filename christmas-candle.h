#include <Arduino.h>
#ifndef CHRISTMAS_CANDLE_H_
#define CHRISTMAS_CANDLE_H_

#define SENSOR_PIN (14)

void swith(int val);

void say_hello();

void enterSleep(void);

void setupWatchDogTimer();

bool isNightNow();
bool isPause();

void blink(int time) {
	digitalWrite(LED_BUILTIN, HIGH);
	delay(time);
	digitalWrite(LED_BUILTIN, LOW);
}

#endif /* CHRISTMAS_CANDLE_H_ */
