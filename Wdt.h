#ifndef WDT_H_
#define WDT_H_

class Wdt {
public:
	Wdt();
	void enterSleep();
	bool isSleep();
private:
	void setupWdt();
};

#endif /* WDT_H_ */
