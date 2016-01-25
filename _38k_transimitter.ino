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


RobotController robotController; 
RobotModel robotModel(1,7);
LedStatusBar ledBar; 
SoundPlayer soundPlayer(8); 
IRMessaging irMessaging(3, 2); 

IRMessage message;
IRMessage adminMessage; 

LedRGBIndicator ledRGB; 
RobotLifeCycle lifeCycleManager; 

String incomingData ;   // for incoming serial data




void onStatus(IRMessage message) {



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

	lifeCycleManager.setStatusTiming(220);

	lifeCycleManager.onStatusTimer(&onStatusTimer);
	lifeCycleManager.onStatus(&onStatus); 
	
	
  
}



void loop() {

	lifeCycleManager.tick(); 

	/// read serial, for robot programming. later this will be implemented 
	/// via rf or other protocol. 

	if (Serial.available() > 0) {
		
		incomingData = Serial.readString();

		if (incomingData == "st") {

			Serial.println("robot status");
			Serial.println("-------------------------");


			Serial.print("group : ");
			Serial.print(robotModel.getGroup());

			Serial.print(" , id : ");
			Serial.print(robotModel.getID()); 

			Serial.print(" , health : ");
			Serial.print(robotModel.getHealth());

			Serial.print(" , hit points: ");
			Serial.println(robotModel.getHitPoints());


		} else {

			/// try to decode command 
			
			String	command		= incomingData.substring(0, 2);
			byte	param		= incomingData.substring(3, 6).toInt(); 

			if (command == "gr") {

				robotModel.setGroup(param); 

			} else if (command == "id") {

				robotModel.setID(param); 

			} else if (command == "hl") {
				robotModel.setHealth(param);
			} else if (command == "hp") {
				robotModel.setHitPoints(param);
			}
			else if (command == "??") {
				Serial.println("format : [command,param] or [command param]");
				Serial.println("command list : st , gr , ip , hl , hp , ??"); 
			}
			
			ledRGB.blink(PIN_BLUE);
			Serial.println("ok"); 
		




		}
		
/*		adminMessage.decode(adminMessage.hexToDec(incomingData)); 
		
		Serial.println(adminMessage.group);
		Serial.println(adminMessage.id);
*/		
		

	}

}

