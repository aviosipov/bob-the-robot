#include "Arduino.h"
#include "IRMessage.h"
#include "IRMessaging.h" 
#include "RobotController.h"
#include "RobotModel.h"
#include "LedRGBIndicator.h"
#include "RobotLifeCycle.h"


RobotLifeCycle::RobotLifeCycle() {

	_lastStatusEvent = 0; 
	_statusIntervalDelay = STATUS_INVERVAL_DELAY ;
	_rgbStatusTimer = 0; 
}

void RobotLifeCycle::_handleTimers()
{
	unsigned long currentTime = millis();

	if ((currentTime - _lastStatusEvent ) >= _statusIntervalDelay) {
		
		_statusIntervalDelay = STATUS_INVERVAL_DELAY + random(0, STATUS_INTERVAL_RANDOM_FIX);
		_lastStatusEvent = currentTime; 

		_callbackOnStatusTimer(); 

	}

	if ((currentTime - _rgbStatusTimer) > LEDRGB_TIMOUT && _rgbStatusTimer > 0 ) {

		_rgbStatusTimer = 0; 
		_ledRGB->allOff(); 

	}
}

void RobotLifeCycle::_checkForIRMessage()
{
		
	_message = _irMessaging->getIRMessage() ;

	if (_message.isValid()) {		

		if (_message.group == _robotModel->getGroup()) {
			_ledRGB->green(); 
		}
		else {
			_ledRGB->red(); 
		}

		_rgbStatusTimer = millis(); 

		if (_message.command == COMMAND_STATUS) 
			_callbackOnStatus(_message);


		if (_message.command == COMMAND_ATTACK)
			_callbackOnAttack(_message); 


		if (_message.command == COMMAND_HEAL)
			_callbackOnHeal(_message); 


/*		if (_message.command != COMMAND_STATUS) {

			Serial.println("?");
			Serial.println(_message.command);

		} */

	}


		


}

void RobotLifeCycle::tick()
{

	_checkForIRMessage();
	_handleTimers(); 

	

}

void RobotLifeCycle::onStatus(CallbackOnStatus callback)
{
	_callbackOnStatus = callback; 
}

void RobotLifeCycle::onHeal(CallbackOnHeal callback)
{
	_callbackOnHeal = callback; 
}

void RobotLifeCycle::onAttack(CallbackOnAttack callback)
{
	_callbackOnAttack = callback; 
}

void RobotLifeCycle::onStatusTimer(CallbackOnStatusTimer callback)
{
	_callbackOnStatusTimer = callback; 
}



void RobotLifeCycle::attachRobotModel(RobotModel &robotModel)
{
	_robotModel = &robotModel; 	
}

void RobotLifeCycle::attachRobotController(RobotController &robotController)
{
	_robotController = &robotController; 
}

void RobotLifeCycle::attachIRMessaging(IRMessaging &irMessaging)
{
	_irMessaging = &irMessaging; 
}

void RobotLifeCycle::attachLedRGB(LedRGBIndicator & ledRGB)
{
	_ledRGB = &ledRGB; 
}





