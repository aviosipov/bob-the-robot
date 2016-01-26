#include "Arduino.h"
#include "IRMessage.h"
#include "IRMessaging.h" 
#include "RobotController.h"
#include "RobotModel.h"
#include "LedRGBIndicator.h"
#include "RobotLifeCycle.h"


RobotLifeCycle::RobotLifeCycle() {

	_lastStatusEvent = 0; 
	_statusIntervalDelay = 100;
	_rgbStatusTimer = 0; 
}

void RobotLifeCycle::_handleTimers()
{
	unsigned long currentTime = millis();

	if ((currentTime - _lastStatusEvent ) >= _statusIntervalDelay) {
		
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

		if (_message.command != COMMAND_STATUS) {

			Serial.println("****");
			Serial.println(_message.command);

		}
			

		//if (_message.command == COMMAND_ATTACK && _message.group != _robotModel->getGroup())
		if (_message.command == COMMAND_ATTACK)
			_callbackOnAttack(_message); 

		//if (_message.command == COMMAND_HEAL && _message.group == _robotModel->getGroup())
		if (_message.command == COMMAND_HEAL)
			_callbackOnHeal(_message); 

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

void RobotLifeCycle::setStatusTiming(short interval)
{
	_statusIntervalDelay = interval;
}




void RobotLifeCycle::handleMessage(IRMessage message)
{

	switch (message.command) {

		case COMMAND_STATUS:

			/// friend or enemy? 
			
			if (message.group == GROUP_FRIENDLY) {

				/// this is a status from a freindly unit, check 
				/// if this unit need healing 

				if (message.param <= UNIT_HEALING_TRIGGER ) {
					
					/// 1. send healing command 
					/// 2. check that health has changed
					///
					/// * maybe pass this to another class
					///   that will take care for the healing 
					///   functionality

				}

			}
			else {

				/// well this is not a friendly unit, attack!!!
				/// attack will take place by :
				/// 1. send attack command 
				/// 2. check that the unit has been damaged 
				/// 3. decide whatever chase or run away 

			}

			break;

		case COMMAND_STATUS_TOWER:

			/// if this is a friendly tower, check whatever
			/// healing is required 



			/// this is an enemy tower, which means that i can not
			/// be passed. 


			break;
		case COMMAND_ATTACK:

			/// react to attack by taking damage 

			break; 
		case COMMAND_FOLLOW:
			break; 
		case COMMAND_HEAL:
			break; 

	}


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





