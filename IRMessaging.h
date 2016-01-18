#include <IRremote.h>

class IRMessaging {
    
    private:
    
        int _txPin; 
		int _rxPin;
        
		IRrecv *irRecv;  
		decode_results results;

    
    public:
    
        IRMessaging(int txPin, int rxPin) ;

		void enableRX();
		void initTX(); 
        
        unsigned long getIRMessage() ; 
        void sendIRMessage(int message) ; 
    


         
    
} ; 
