class RobotModel {
    
    private:
    
        int _health ; 
        int _hitPoints ; 
        int _hitDelay ;       
        
		int _id; 
		int _group;

		unsigned long _lastShootTime;

         
    
    public:
    
        RobotModel(int id, int group) ; 
    
        void shoot() ;
        void takeHit(int points) ;
        int getHealth() ;   
    
         
    
} ; 
