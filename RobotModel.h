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
        RobotModel(byte id, byte group) ;


		byte getGroup(); 
		byte getID(); 
    
        void shoot() ;
        void takeHit(byte hitPoints) ;
        int getHealth() ;   
    
         
    
} ; 
