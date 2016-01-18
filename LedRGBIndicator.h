#pragma once
class LedRGBIndicator {

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

	void animate(); 

	
};

