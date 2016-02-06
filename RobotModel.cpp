#include "Arduino.h" 
#include "RobotModel.h" 


RobotModel::RobotModel()
{
	_id = random(0,7); 
	_group = 1; 
}

RobotModel::RobotModel(byte id) {

	setID(id); 

    _health = 100 ;  
    _hitPoints = 1 ;     

    _lastShootTimer = 0 ; 
	_shootModeTimer = 0;

}

void RobotModel::setGroup(byte group)
{
	_group = group; 
}

void RobotModel::setID(byte id)
{
	_id = id; 

	if (id <= 7) setGroup(1);
	else setGroup(2); 
	
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

	if ((currentTime - _lastShootTimer) >= SHOOT_TIMER_DELAY && isActive() == ROBOT_ACTIVE  ) {
		return ROBOT_CAN_SHOOT;
	}
	else {
		return ROBOT_CANNOT_SHOOT;
	}

}

byte RobotModel::isAttackMode()
{
	unsigned long currentTime = millis();

	if ((currentTime - _shootModeTimer) < SHOOT_MODE_DELAY && isActive() == ROBOT_ACTIVE ) {
		return ROBOT_MODE_ATTACK;
	}
	else {
		return ROBOT_MODE_NORMAL; 
	}

}

byte RobotModel::isActive()
{

	if (_health >= ROBOT_IS_ACTIVE_LEVEL) return ROBOT_ACTIVE; 
	else return ROBOT_NOT_ACTIVE; 

}


void RobotModel::shoot() {

	if (canShoot() == ROBOT_CAN_SHOOT && isActive() == ROBOT_ACTIVE  ) {

		_lastShootTimer = millis();		
		_shootModeTimer = millis();

	}
	
	
		
}



void RobotModel::takeHit(byte hitPoints) {

	if (_health >= hitPoints  && isActive() == ROBOT_ACTIVE ) {
		_health -= hitPoints;
	}
		
    
} 


int RobotModel::getHealth() {
    return this->_health ; 
}
