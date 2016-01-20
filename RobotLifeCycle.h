#pragma once

#define UNIT_MAX_HEALTH			100 
#define UNIT_HEALING_TRIGGER	45

#define GROUP_FRIENDLY			1 



#define COMMAND_ATTACK			2
#define COMMAND_HEAL			3 
#define COMMAND_FOLLOW			4
#define COMMAND_STATUS			5
#define COMMAND_STATUS_TOWER	7

typedef int(*CallbackType)(int);

class RobotLifeCycle {

private:

	IRMessage messages[4]; 

	RobotModel *_robotModel; 
	RobotController *_robotController; 


	CallbackType _callback; 


public:

	
	void onInit(CallbackType callback); 
	void test();


	/*void tick();
	void setStatusTiming(byte interval); 

	void onMessage(); 
	void onStatus(); 
	void onHeal();
	void onAttack(); */ 
	 





	RobotLifeCycle(); 


	void handleMessage(IRMessage message); 
	void attachRobotModel(RobotModel &robotModel); 
	void attachRobotController(RobotController &robotController );  



	
	
};

