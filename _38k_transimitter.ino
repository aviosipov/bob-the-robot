#include <Wire.h>
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

/// nrf24 radio stuff ///////////////////////////

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8);
const byte rxAddr[6] = "00001";
int msg[1];



/////////////////////////////////////////////////



RobotController robotController;
RobotModel robotModel(random(8,15));
LedStatusBar ledBar;
SoundPlayer soundPlayer(8);
IRMessaging irMessaging(3, 2);

IRMessage message;

LedRGBIndicator ledRGB;
RobotLifeCycle lifeCycleManager;
RobotAdmin robotAdmin;


String prepareMessage(String attr , String value) {

	String  sender = "bob" +  String(robotModel.getID()) + ".";
	return sender + attr + "," + value ;

}


void sendRFMessage(String attr , String value ) {

	String theMessage = prepareMessage( attr , value );
	int messageSize = theMessage.length();

	for (int i = 0; i < messageSize; i++) {
		int charToSend[1];
		charToSend[0] = theMessage.charAt(i);
		radio.write(charToSend, 1);
	}

	msg[0] = 2;
	radio.write(msg, 1);

}


void onAttack(IRMessage message) {

	sendRFMessage("mode", "hit");

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

		/// this is not a friendly unit, prepare attack command
		/// if attack is possible 

		if (robotModel.canShoot() == ROBOT_CAN_SHOOT) {

			robotModel.shoot();			

			Wire.beginTransmission(9); // transmit to device #9
			Wire.write(5);              // sends 5 - shoot command 
			Wire.endTransmission();    // stop transmitting

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


		sendRFMessage("mode", "ok");
		sendRFMessage("health", String(robotModel.getHealth())); 


	}
	else if (robotModel.isAttackMode() == ROBOT_MODE_ATTACK) {

		message.command = COMMAND_ATTACK;
		message.param = robotModel.getHitPoints();
		
		sendRFMessage("mode", "atk");

	}
	
	irMessaging.sendIRMessage(message);


	


}


void setup() {

	/// setup wrire ////////////////////////////////////////

	Wire.begin();


	/// setup rf24 radio  //////////////////////////////////

	radio.begin();
	radio.setPALevel(RF24_PA_MIN);
	radio.setDataRate(RF24_1MBPS);
	radio.setRetries(15, 15);
	radio.openWritingPipe(rxAddr);
	radio.stopListening();

	////////////////////////////////////////////////////////



	/// prepare robots


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

