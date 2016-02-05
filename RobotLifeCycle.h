#pragma once

#define STATUS_INVERVAL_DELAY		200
#define STATUS_INTERVAL_RANDOM_FIX	25

#define UNIT_MAX_HEALTH			15 
#define UNIT_HEALING_TRIGGER	5

#define GROUP_FRIENDLY			1 
#define MESSAGE_TO_ALL			0


/// admin stuff here 

#define ADMIN_SET_ID			10 
#define ADMIN_SET_GROUP			11 
#define ADMIN_SET_HEALTH		12
#define ADMIN_SET_HIT_POINTS	13
#define ADMIN_GET_STATUS		14

#define SENDER_ADMIN			15

/// general commands 

#define COMMAND_ATTACK			2
#define COMMAND_HEAL			3 
#define COMMAND_FOLLOW			4
#define COMMAND_STATUS			5
#define COMMAND_STATUS_TOWER	7

#define LEDRGB_TIMOUT			250 


typedef void(*CallbackOnAttack)(IRMessage);
typedef void(*CallbackOnStatus)(IRMessage);
typedef void(*CallbackOnHeal)(IRMessage);
typedef void(*CallbackOnStatusTimer)(); 


class RobotLifeCycle {

private:

	unsigned long _lastStatusEvent;
	unsigned long _rgbStatusTimer; 

	short _statusIntervalDelay; 
	IRMessage _message; 

	RobotModel		*	_robotModel; 
	RobotController *	_robotController; 
	IRMessaging		*	_irMessaging; 
	LedRGBIndicator *	_ledRGB; 

	CallbackOnStatusTimer _callbackOnStatusTimer;
	CallbackOnAttack	_callbackOnAttack;
	CallbackOnStatus	_callbackOnStatus;
	CallbackOnHeal		_callbackOnHeal;


	void _handleTimers(); 
	void _checkForIRMessage(); 

public:
	
	void tick();

	
	void onStatus(CallbackOnStatus callback);
	void onHeal(CallbackOnHeal callback);
	void onAttack(CallbackOnAttack callback);
	
	void onStatusTimer(CallbackOnStatusTimer callback); 
	void setStatusTiming(short interval); 

	
	 





	RobotLifeCycle(); 


	
	void attachRobotModel(RobotModel &robotModel); 
	void attachRobotController(RobotController &robotController );  
	void attachIRMessaging(IRMessaging &irMessaging); 
	void attachLedRGB(LedRGBIndicator &ledRGB); 

	
	
};

