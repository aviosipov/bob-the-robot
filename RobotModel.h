#define SHOOT_TIMER_DELAY			1000
#define SHOOT_MODE_DELAY			350 

#define ROBOT_MODE_NORMAL			1
#define ROBOT_MODE_ATTACK			2
#define ROBOT_MODE_HEAL				4

#define ROBOT_CANNOT_SHOOT			0
#define ROBOT_CAN_SHOOT				1

#define ROBOT_IS_ACTIVE_LEVEL		10
#define ROBOT_ACTIVE				1
#define ROBOT_NOT_ACTIVE			0



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
        RobotModel(byte id) ;

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


		byte isActive(); 

    
        void shoot() ;
        void takeHit(byte hitPoints) ;
        
    
         
    
} ; 
