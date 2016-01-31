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
RobotModel robotModel(1, 7);
LedStatusBar ledBar;
SoundPlayer soundPlayer(8);
IRMessaging irMessaging(3, 2);

IRMessage message;

LedRGBIndicator ledRGB;
RobotLifeCycle lifeCycleManager;
RobotAdmin robotAdmin;



void onAttack(IRMessage message) {

	soundPlayer.playGun(); 

	Serial.println("_hit");
	robotModel.takeHit(message.param); 
	
	/// update health led bar 

	if (robotModel.getHealth() >= 66) {
		ledBar.setStatus(1, 1, 1); 

	} 	else if (robotModel.getHealth() >= 33) {

		ledBar.setStatus(0, 1, 1);

	} 	else if (robotModel.getHealth() >= 10) {

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

	Serial.print("g:");
	Serial.print(message.group);

	Serial.print(", s:");
	Serial.print(message.sender);

	Serial.print(", cmd:");
	Serial.print(message.command);

	Serial.print(" , prm:");
	Serial.print(message.param);

	Serial.print(" , rcv:");
	Serial.print(message.receiver);

	Serial.print(" , id:");
	Serial.println(message.id);


	/// handle message 

	if (message.group == robotModel.getGroup()) {

		/// this is a friendly unit 

	}
	else {

		/// this is not a freindly unit, prepare attack command
		/// if attack is possible 

		if (robotModel.canShoot() == ROBOT_CAN_SHOOT) {

			robotModel.shoot();			
			ledRGB.blink(PIN_BLUE); 	
			soundPlayer.playCoin();

			Serial.println("_sht"); 

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

		Serial.println("_atk");

	}


	irMessaging.sendIRMessage(message);

}


void setup() {



	Serial.begin(56000);
	Serial.println("Program Started");

	ledBar.init(A0, A1, A2);
	ledBar.animate();

	ledRGB.init(6, 5, 4);
	ledRGB.animate();


	soundPlayer.playCoin();
	//soundPlayer.playGun();

//	soundPlayer.playCoin(); delay(500);
//	soundPlayer.playGun(); delay(500);
//	soundPlayer.noise(400,400); 

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

