#include "Constants.h"
#include "Arduino.h"
#include "LedStatusBar.h"


void LedStatusBar::init(byte pin0, byte pin1, byte pin2)
{
	_pin0 = pin0;
	_pin1 = pin1;
	_pin2 = pin2;

	pinMode(pin0, OUTPUT);
	pinMode(pin1, OUTPUT);
	pinMode(pin2, OUTPUT);

}

void LedStatusBar::blink()
{
	setStatus(0, 0, 0); 	
	setStatus(1, 1, 1);
	delay(BLINK_DELAY); 
	setStatus(0, 0, 0);

}

void LedStatusBar::shootAnimation()
{
	blink();
	delay(25);
	blink();
	delay(25); 
	blink(); 

}

void LedStatusBar::animate()
{

	setStatus(0, 0, 0);	
	delay(150);
	setStatus(0, 0, 1);
	delay(150);
	setStatus(0, 1, 0);
	delay(150);
	setStatus(1, 0, 0);
	delay(150);
	setStatus(0, 1, 0);
	delay(150);
	setStatus(0, 0, 1);
	delay(150);
	setStatus(0, 0, 0);

}

void LedStatusBar::setStatus(byte pin0, byte pin1, byte pin2)
{
	digitalWrite(_pin0, pin0); 
	digitalWrite(_pin1, pin1);
	digitalWrite(_pin2, pin2);

}
