#include "RobotModel.h" 
#include "Arduino.h" 

RobotModel::RobotModel()
{
}

RobotModel::RobotModel(int id, int group) {

	_id = id;
	_group = group; 	

    _health = 150 ;  
    _hitPoints = 20 ; 
    _hitDelay = 2000 ; 
    _lastShootTime = 0 ; 

}


void RobotModel::shoot() {

	unsigned long currentTime = millis() ; 

	if ((currentTime - _lastShootTime) >= _hitDelay) {
			
		Serial.println("shoot!");
		_lastShootTime = millis(); 

	}
	else {

		Serial.print(currentTime - _lastShootTime); 
		Serial.print(" ");
		Serial.println("no shoot"); 

	}



		
}



void RobotModel::takeHit(int points) {
    
} 


int RobotModel::getHealth() {
    return this->_health ; 
}
