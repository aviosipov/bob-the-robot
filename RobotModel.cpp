#include "Arduino.h" 
#include "RobotModel.h" 


RobotModel::RobotModel()
{
	_id = 25; 
	_group = 1; 
}

RobotModel::RobotModel(byte group, byte id) {

	_id = id;
	_group = group; 	

    _health = 100 ;  
    _hitPoints = 20 ; 
    _hitDelay = 500 ; 
    _lastShootTime = 0 ; 

}

void RobotModel::setGroup(byte group)
{
	_group = group; 
}

void RobotModel::setID(byte id)
{
	_id = id; 
}

void RobotModel::setHealth(byte health)
{
	_health = health; 
}

void RobotModel::setHitPoints(byte hitPoints)
{
	_hitPoints = hitPoints; 
}

byte RobotModel::getGroup()
{
	return _group; 
}

byte RobotModel::getID()
{
	return _id; 
}

byte RobotModel::getHitPoints()
{
	return _hitPoints;
}

byte RobotModel::canShoot()
{

	unsigned long currentTime = millis();

	if ((currentTime - _lastShootTime) >= _hitDelay) {		
		return ROBOT_CAN_SHOOT; 
	}
	else {
		return ROBOT_CANNOT_SHOOT; 
	}


	
}


void RobotModel::shoot() {

	if (canShoot() == ROBOT_CAN_SHOOT) {

		_hitDelay = SHOOT_TIMER_DELAY + random(0, SHOOT_TIMER_RANDOM_FIX);
		_lastShootTime = millis();
		/// do other stuff ... 

	}
	
	
		
}



void RobotModel::takeHit(byte hitPoints) {

	if (_health >= hitPoints)
		_health -= hitPoints;
    
} 


int RobotModel::getHealth() {
    return this->_health ; 
}
