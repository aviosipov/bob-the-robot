#pragma once
class LedRGBIndicator {

#define PIN_RED		0
#define PIN_GREEN	1
#define PIN_BLUE	2

private:
	byte _rPin;
	byte _gPin;
	byte _bPin; 
		 
public:

	void init(byte rPin, byte gPin, byte bPin );

	void allOff();
	void red(); 
	void green(); 
	void blue(); 

	void blink(byte pin);

	void animate(); 

	
};

