#include "Arduino.h"
#include "IRMessage.h"
#include "IRMessaging.h" 
#include <IRremote.h>



IRMessaging::IRMessaging(byte txPin, byte rxPin) {

	_txPin = txPin; 
	_rxPin = rxPin; 

	_irRecv = new IRrecv(_rxPin);

}

void IRMessaging::enableRX()
{	
	_irRecv->enableIRIn();	
}



IRMessage IRMessaging::getIRMessage() {

	
	if (_irRecv->decode(&results)) {		

		_message.decode(results.value); 
		_irRecv->resume(); 

	} else {

		_message.decode(0); /// trigger invalid message 
		
	}

	return _message;
    
    
    
} 

void IRMessaging::sendIRMessage(IRMessage message) {

	_irSend.sendSony(message.encode(), 32);			
	enableRX();	
	
} 
