#include <NewTone.h>
#include <IRremote.h>
#include <IRremoteInt.h>


#include "RobotModel.h"
#include "RobotController.h" 
#include "IRMessaging.h" 
#include "LedStatusBar.h"
#include "SoundPlayer.h" 
#include "IRMessage.h"

RobotModel robotModel; 
LedStatusBar ledBar; 
SoundPlayer soundPlayer(8); 
IRMessaging irMessaging(2, 2); 
IRMessage message;

unsigned long irMessage;






void setup() {

	irMessaging.enableRX(); 	

	ledBar.init(A0, A1, A2); 
	ledBar.animate(); 
	soundPlayer.playCoin();
		
	Serial.begin(9600);

	
	message.decode(443634928); 
	Serial.println(message.id); 
	 

	
	
  
}



void loop() {

 
	irMessage = irMessaging.getIRMessage(); 

	if (irMessage > 0) {		
		Serial.println(irMessage, HEX);
	}

	/// now, process ir message 

  

}

