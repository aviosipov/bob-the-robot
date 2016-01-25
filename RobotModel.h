class RobotModel {
    
    private:
    
        byte _health ; 
		byte _hitPoints ;
		byte _id;
		byte _group;

		int _hitDelay;
		unsigned long _lastShootTime;        
    
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
    
        void shoot() ;
        void takeHit(byte hitPoints) ;
        
    
         
    
} ; 
