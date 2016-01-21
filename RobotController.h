class RobotController {
    
    private:
    
        byte motorLeft ; 
		byte motorRight;
      
         
    
    public:
    
        RobotController() ;
    
        void init() ;     
        void forward() ;
        void backward() ;
        void left() ; 
        void right() ; 
        void stop() ;    
    
    
         
    
} ; 
