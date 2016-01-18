#pragma once
class LedStatusBar {

private:

	int _pin0; 
	int _pin1; 
	int _pin2; 


public:

	void init(int pin0, int pin1, int pin2);

	void blink(); 
	void animate();  
	void setStatus(int pin0, int pin1, int pin2);




	



};
