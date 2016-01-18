#include "RobotModel.h" 
#include "Arduino.h" 

RobotModel::RobotModel() {
    health = 150 ;  
    hitPoints = 20 ; 
    hitDelay = 2000 ; 
    lastShootTime = 0 ; 
}


void RobotModel::shoot() {

	unsigned long currentTime = millis() ; 

	if ((currentTime - lastShootTime) >= hitDelay) {
			
		Serial.println("shoot!");
		lastShootTime = millis(); 

	}
	else {

		Serial.print(currentTime - lastShootTime); 
		Serial.print(" ");
		Serial.println("no shoot"); 

	}



		
}



void RobotModel::takeHit(int points) {
    
} 


int RobotModel::getHealth() {
    return this->health ; 
}
