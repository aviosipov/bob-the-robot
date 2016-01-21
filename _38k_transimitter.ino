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
RobotModel robotModel(7,1); 
LedStatusBar ledBar; 
SoundPlayer soundPlayer(8); 
IRMessaging irMessaging(2, 2); 
IRMessage message;
LedRGBIndicator ledRGB; 
RobotLifeCycle lifeCycleManager; 

unsigned long irMessage;



void onStatusTimer() {

	message.group = robotModel.getGroup();
	message.sender = robotModel.getID();
	message.command = COMMAND_STATUS; 
	message.param = robotModel.getHealth(); 
	message.receiver = MESSAGE_TO_ALL; 
	
	irMessaging.sendIRMessage(message); 
	
	ledBar.blink();

}


void setup() {

	Serial.begin(9600);
	Serial.println("Program Started");
	
	irMessaging.enableRX(); 	

	ledBar.init(A0, A1, A2); 
	ledBar.animate(); 

	ledRGB.init(4, 5, 6); 
	ledRGB.animate();

	soundPlayer.playCoin();

	lifeCycleManager.attachRobotModel(robotModel); 
	lifeCycleManager.attachRobotController(robotController); 
	lifeCycleManager.setStatusTiming(1500);

	
	lifeCycleManager.onStatusTimer(&onStatusTimer);
	
	

	/*
	message.decode(443634928); 
	Serial.println(message.id); 
	*/ 
	
  
}



void loop() {

	lifeCycleManager.tick(); 


	/*
	message.decode(irMessaging.getIRMessage()); 

	if (message.isValid())
		lifeCycleManager.handleMessage(message); 
  */ 

}

