#include "Arduino.h" 
#include "LedRGBIndicator.h"

void LedRGBIndicator::init(byte rPin, byte gPin, byte bPin)
{
	_rPin = rPin; 
	_gPin = gPin;
	_bPin = bPin;

	pinMode(_rPin, OUTPUT);
	pinMode(_gPin, OUTPUT);
	pinMode(_bPin, OUTPUT);
}

void LedRGBIndicator::allOff()
{

	digitalWrite(_rPin, LOW);
	digitalWrite(_gPin, LOW);
	digitalWrite(_bPin, LOW);

}

void LedRGBIndicator::red()
{

	allOff(); 
	digitalWrite(_rPin, HIGH); 
}

void LedRGBIndicator::green()
{
	allOff();
	digitalWrite(_gPin, HIGH);
}

void LedRGBIndicator::blue()
{
	allOff();
	digitalWrite(_bPin, HIGH);
}

void LedRGBIndicator::animate()
{
	allOff(); 

	for (int i = 0; i <= 3 ; i++) {

		red();
		delay(100);
		allOff();
		delay(20);

		green();
		delay(100);
		allOff();
		delay(20);

		blue();
		delay(100);
		allOff();
		delay(20);

	}


	allOff(); 


}
