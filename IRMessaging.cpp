#include "IRMessaging.h" 
#include <IRremote.h>


IRMessaging::IRMessaging(int txPin, int rxPin) {

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

unsigned long IRMessaging::getIRMessage() {


	if (irRecv->decode(&results)) {

		irRecv->resume(); 
		return results.value;  

	}
	else {

		return 0;

	}
    
    
    
} 

void IRMessaging::sendIRMessage(int message) {
    
} 
