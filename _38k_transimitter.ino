#include <NewTone.h>
#include <IRremote.h>
#include <IRremoteInt.h>


#include "RobotModel.h"
#include "RobotController.h" 
#include "IRMessaging.h" 
#include "LedStatusBar.h"
#include "SoundPlayer.h" 
#include "IRMessage.h"
#include "LedRGBIndicator.h"
#include "RobotLifeCycle.h"
#include "RobotAdmin.h"

RobotController robotController; 
RobotModel robotModel(1,7);
LedStatusBar ledBar; 
SoundPlayer soundPlayer(8); 
IRMessaging irMessaging(3, 2); 

IRMessage message;
IRMessage shootMessage; 

LedRGBIndicator ledRGB; 
RobotLifeCycle lifeCycleManager; 
RobotAdmin robotAdmin; 



void onAttack(IRMessage message) {
	Serial.println("we're under attack"); 
}

void onHeal(IRMessage message) {
}


void onStatus(IRMessage message) {

	/// message received 

	Serial.print("group : ");
	Serial.print(message.group);

	Serial.print(" , sender : ");
	Serial.print(message.sender);

	Serial.print(" , command : ");
	Serial.print(message.command);

	Serial.print(" , param : ");
	Serial.print(message.param);

	Serial.print(" , receiver : ");
	Serial.print(message.receiver);

	Serial.print(" , id : ");
	Serial.println(message.id);


	/// handle message 

	if (message.group == robotModel.getGroup()) {

		/// this is a friendly unit 

	} else {

		/// this is not a freindly unit, prepare attack command
		/// if attack is possible 

		if (robotModel.canShoot() == ROBOT_CAN_SHOOT) {

			robotModel.shoot(); 			

			shootMessage.group = robotModel.getGroup();
			shootMessage.sender = robotModel.getID();
			shootMessage.command = COMMAND_ATTACK;
			shootMessage.param = robotModel.getHitPoints(); 
			shootMessage.receiver = message.sender;
			shootMessage.id = shootMessage.getID(); 

			irMessaging.sendIRMessage(message);

//			ledBar.shootAnimation(); 			
	//		Serial.println("shoot!"); 

		} 
			
		



	}








}

void onStatusTimer() {

	message.group = robotModel.getGroup();
	message.sender = robotModel.getID();
	message.command = COMMAND_STATUS; 
	message.param = robotModel.getHealth(); 
	message.receiver = MESSAGE_TO_ALL; 
	message.id = message.getID(); 
	
	irMessaging.sendIRMessage(message); 
	
}


void setup() {

	

	Serial.begin(19200);
	Serial.println("Program Started");
	
	ledBar.init(A0, A1, A2); 
	ledBar.animate(); 

	ledRGB.init(6, 5, 4); 
	ledRGB.animate();

	soundPlayer.playCoin();

	ledBar.setStatus(1, 1, 1); 

	lifeCycleManager.attachRobotModel(robotModel); 
	lifeCycleManager.attachRobotController(robotController); 
	lifeCycleManager.attachIRMessaging(irMessaging); 
	lifeCycleManager.attachLedRGB(ledRGB); 

	lifeCycleManager.setStatusTiming(250);

	lifeCycleManager.onStatusTimer(&onStatusTimer);
	lifeCycleManager.onStatus(&onStatus); 
	lifeCycleManager.onAttack(&onAttack); 
	lifeCycleManager.onHeal(&onHeal); 

	robotAdmin.attachRobotModel(robotModel);
	robotAdmin.attachLedRGB(ledRGB);
  
}



void loop() {

	lifeCycleManager.tick(); 
	robotAdmin.checkForSerialData(); 




}

