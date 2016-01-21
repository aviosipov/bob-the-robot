#include "Arduino.h"
#include "IRMessage.h"
#include "IRMessaging.h" 
#include <IRremote.h>



IRMessaging::IRMessaging(byte txPin, byte rxPin) {

	_txPin = txPin; 
	_rxPin = rxPin; 

	irRecv = new IRrecv(_rxPin);
}

void IRMessaging::enableRX()
{
	
	irRecv->enableIRIn();
	
}

void IRMessaging::initTX()
{
}

IRMessage IRMessaging::getIRMessage() {

	IRMessage message;

	if (irRecv->decode(&results)) {		

		message.decode(results.value); 
		irRecv->resume(); 

	} else {

		message.decode(0); /// trigger invalid message 
		
	}

	return message;
    
    
    
} 

void IRMessaging::sendIRMessage(IRMessage message) {

	unsigned long irData = message.encode(); 
    
} 
