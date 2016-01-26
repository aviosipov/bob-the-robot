#pragma once
class RobotAdmin {
private:
	String _incomingData;

	RobotModel		*	_robotModel;
	LedRGBIndicator *	_ledRGB;


public:
	RobotAdmin();
	void checkForSerialData(); 

	void attachRobotModel(RobotModel &robotModel);
	void attachLedRGB(LedRGBIndicator &ledRGB);
	
};

