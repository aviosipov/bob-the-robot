#include "Arduino.h"
#include "IRMessage.h"
#include "RobotController.h"
#include "RobotModel.h"
#include "RobotLifeCycle.h"




RobotLifeCycle::RobotLifeCycle() {
	
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




