#pragma once

#define UNIT_MAX_HEALTH			100 
#define UNIT_HEALING_TRIGGER	45

#define GROUP_FRIENDLY			1 

#define MESSAGE_TO_ALL			0


#define COMMAND_ATTACK			2
#define COMMAND_HEAL			3 
#define COMMAND_FOLLOW			4
#define COMMAND_STATUS			5
#define COMMAND_STATUS_TOWER	7



typedef void(*CallbackOnAttack)(IRMessage);
typedef void(*CallbackOnStatus)(IRMessage);
typedef void(*CallbackOnHeal)(IRMessage);
typedef void(*CallbackOnStatusTimer)(); 


class RobotLifeCycle {

private:

	unsigned long _lastStatusEvent;
	short _statusIntervalDelay; 
	IRMessage _message; 

	RobotModel		*	_robotModel; 
	RobotController *	_robotController; 
	IRMessaging		*	_irMessaging; 

	CallbackOnStatusTimer _callbackOnStatusTimer;
	CallbackOnAttack	_callbackOnAttack;
	CallbackOnStatus	_callbackOnStatus;
	CallbackOnHeal		_callbackOnHeal;


	void _handleStatusTimer(); 
	void _checkForIRMessage(); 

public:
	
	void tick();

	
	void onStatus(CallbackOnStatus callback);
	void onHeal(CallbackOnHeal callback);
	void onAttack(CallbackOnAttack callback);
	
	void onStatusTimer(CallbackOnStatusTimer callback); 
	void setStatusTiming(short interval); 

	
	 





	RobotLifeCycle(); 


	void handleMessage(IRMessage message); 
	void attachRobotModel(RobotModel &robotModel); 
	void attachRobotController(RobotController &robotController );  
	void attachIRMessaging(IRMessaging &irMessaging); 


	
	
};

