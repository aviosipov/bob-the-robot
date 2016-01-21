#include "Arduino.h" 
#include "RobotModel.h" 


RobotModel::RobotModel()
{
	_id = 25; 
	_group = 1; 
}

RobotModel::RobotModel(byte id, byte group) {

	_id = id;
	_group = group; 	

    _health = 100 ;  
    _hitPoints = 20 ; 
    _hitDelay = 2000 ; 
    _lastShootTime = 0 ; 

}

byte RobotModel::getGroup()
{
	return _group; 
}

byte RobotModel::getID()
{
	return _id; 
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



void RobotModel::takeHit(byte hitPoints) {

	if (_health >= hitPoints)
		_health -= hitPoints;
    
} 


int RobotModel::getHealth() {
    return this->_health ; 
}
