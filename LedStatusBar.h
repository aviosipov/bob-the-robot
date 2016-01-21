#pragma once
class LedStatusBar {

private:

	byte _pin0; 
	byte _pin1;
	byte _pin2;


public:

	void init(byte pin0, byte pin1, byte pin2);

	void blink(); 
	void animate();  
	void setStatus(byte pin0, byte pin1, byte pin2);




	



};
