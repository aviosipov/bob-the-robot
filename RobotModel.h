#define SHOOT_TIMER_DELAY			800
#define SHOOT_MODE_DELAY			750 

#define ROBOT_MODE_NORMAL			1
#define ROBOT_MODE_ATTACK			2
#define ROBOT_MODE_HEAL				4

#define ROBOT_CANNOT_SHOOT		0
#define ROBOT_CAN_SHOOT			1


class RobotModel {
    
    private:
    
        byte _health ; 
		byte _hitPoints ;
		byte _id;
		byte _group;
		
		unsigned long _lastShootTimer;        
		unsigned long _shootModeTimer;
    
    public:
    
		RobotModel(); 
        RobotModel(byte group, byte id) ;

		void setGroup(byte group);
		void setID(byte id);
		void setHealth(byte health); 
		void setHitPoints(byte hitPoints);


		byte getGroup(); 
		byte getID(); 
		int getHealth();
		byte getHitPoints(); 


		byte canShoot();
		byte isAttackMode(); 

    
        void shoot() ;
        void takeHit(byte hitPoints) ;
        
    
         
    
} ; 
