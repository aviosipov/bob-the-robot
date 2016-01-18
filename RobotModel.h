class RobotModel {
    
    private:
    
        int health ; 
        int hitPoints ; 
        int hitDelay ;       
        
		unsigned long lastShootTime;

         
    
    public:
    
        RobotModel() ; 
    
        void shoot() ;
        void takeHit(int points) ;
        int getHealth() ;   
    
         
    
} ; 
