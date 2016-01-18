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






void setup() {

	irMessaging.enableRX(); 	

	ledBar.init(A0, A1, A2); 
	ledBar.animate(); 

	ledRGB.init(4, 5, 6); 
	ledRGB.animate();


	lifeCycleManager.robotController.init(); 
	lifeCycleManager.robotModel.shoot();


	soundPlayer.playCoin();
		
	Serial.begin(9600);

	
	message.decode(443634928); 
	Serial.println(message.id); 

	message.decode(805306368); 

	if (!message.isValid())
		Serial.println("invalid message"); 

	
	
  
}



void loop() {


	message.decode(irMessaging.getIRMessage()); 

	if (message.isValid())
		lifeCycleManager.handleMessage(message); 
  

}

