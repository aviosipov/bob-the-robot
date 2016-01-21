#include "IRMessage.h"
#include <IRremote.h>

class IRMessaging {
    
    private:
    
        byte _txPin; 
		byte _rxPin;
        
		IRrecv *irRecv;  
		decode_results results;

    

    public:
    
        IRMessaging(byte txPin, byte rxPin) ;

		void enableRX();
		void initTX(); 
        
        IRMessage getIRMessage() ; 
        void sendIRMessage(IRMessage message) ;
    


         
    
} ; 
