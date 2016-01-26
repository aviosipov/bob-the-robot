#include "Arduino.h"
#include "RobotModel.h"
#include "LedRGBIndicator.h"
#include "RobotAdmin.h"



RobotAdmin::RobotAdmin()
{
}

void RobotAdmin::checkForSerialData()
{


	if (Serial.available() > 0) {

		_incomingData = Serial.readString();

		if (_incomingData == "st") {

			Serial.println("robot status");
			Serial.println("-------------------------");


			Serial.print("group : ");
			Serial.print(_robotModel->getGroup());

			Serial.print(" , id : ");
			Serial.print(_robotModel->getID());

			Serial.print(" , health : ");
			Serial.print(_robotModel->getHealth());

			Serial.print(" , hit points: ");
			Serial.println(_robotModel->getHitPoints());


		}
		else {

			/// try to decode command 

			String	command = _incomingData.substring(0, 2);
			byte	param = _incomingData.substring(3, 6).toInt();

			if (command == "gr") {
				
				_robotModel->setGroup(param);

			}
			else if (command == "id") {

				_robotModel->setID(param);

			}
			else if (command == "hl") {
				_robotModel->setHealth(param);
			}
			else if (command == "hp") {
				_robotModel->setHitPoints(param);
			}
			else if (command == "??") {
				Serial.println("format : [command,param] or [command param]");
				Serial.println("command list : st , gr , ip , hl , hp , ??");
			}

			_ledRGB->blink(PIN_BLUE);
			Serial.println("ok");


		}


	}


}

void RobotAdmin::attachRobotModel(RobotModel & robotModel)
{
	_robotModel = &robotModel;
}

void RobotAdmin::attachLedRGB(LedRGBIndicator & ledRGB)
{
	_ledRGB = &ledRGB;
}


