#include <Arduino.h>
#ifndef CHRISTMAS_CANDLE_H_
#define CHRISTMAS_CANDLE_H_

#define SENSOR_PIN (14)

void say_hello();

void enterSleep(void);

void setupWatchDogTimer();

void blink(int time) {
	digitalWrite(LED_BUILTIN, HIGH);
	delay(time);
	digitalWrite(LED_BUILTIN, LOW);
}

#endif /* CHRISTMAS_CANDLE_H_ */
