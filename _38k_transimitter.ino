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
RobotModel robotModel(5);
LedStatusBar ledBar;
SoundPlayer soundPlayer(8);
IRMessaging irMessaging(3, 2);

IRMessage message;

LedRGBIndicator ledRGB;
RobotLifeCycle lifeCycleManager;
RobotAdmin robotAdmin;



void onAttack(IRMessage message) {

	//soundPlayer.explosion(); 

	Serial.println("_ht");
	robotModel.takeHit(message.param); 
	
	/// update health led bar 

	if (robotModel.getHealth() >= 85) {
		ledBar.setStatus(1, 1, 1); 

	} 	else if (robotModel.getHealth() >= 50) {

		ledBar.setStatus(0, 1, 1);

	} 	else if (robotModel.getHealth() >= 20) {

		ledBar.setStatus(0, 0, 1);
	}
	else {
		ledBar.setStatus(0, 0, 0);
	}

}

void onHeal(IRMessage message) {
}


void onStatus(IRMessage message) {

	/// message received 

	
	Serial.print(message.group);
	Serial.print("/");
	Serial.print(message.sender);

	Serial.print(" ");
	Serial.print(message.command);

	Serial.print("/");
	Serial.print(message.param);

//	Serial.print(" , rcv:");
//	Serial.print(message.receiver);

	Serial.print(" ");
	Serial.println(random(0,255));


	/// handle message 

	if (message.group == robotModel.getGroup()) {

		/// this is a friendly unit 

	} else {

		/// this is not a freindly unit, prepare attack command
		/// if attack is possible 

		if (robotModel.canShoot() == ROBOT_CAN_SHOOT) {

			robotModel.shoot();						
//			soundPlayer.playGun(); 

//			Serial.println("_sht"); 

		} 

	}



}

void onStatusTimer() {


	message.group = robotModel.getGroup();
	message.sender = robotModel.getID();
	message.id = message.getID();


	if (robotModel.isAttackMode() == ROBOT_MODE_NORMAL) {

		message.command = COMMAND_STATUS;
		message.param = robotModel.getHealth();
		message.receiver = MESSAGE_TO_ALL;


	}
	else if (robotModel.isAttackMode() == ROBOT_MODE_ATTACK) {

		message.command = COMMAND_ATTACK;
		message.param = robotModel.getHitPoints();
		

	}
	
	irMessaging.sendIRMessage(message);

	Serial.print(message.command);
	Serial.print("/");
	Serial.println(message.param); 


}


void setup() {



	Serial.begin(9600);
	Serial.println("Program Started");

	ledBar.init(A0, A1, A2);
	ledBar.animate();

	ledRGB.init(6, 5, 4);
		
	
	soundPlayer.playGun();
	ledBar.setStatus(1, 1, 1);

	lifeCycleManager.attachRobotModel(robotModel);
	lifeCycleManager.attachRobotController(robotController);
	lifeCycleManager.attachIRMessaging(irMessaging);
	lifeCycleManager.attachLedRGB(ledRGB);

	

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

