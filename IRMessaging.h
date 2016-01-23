#include "IRMessage.h"
#include <IRremote.h>

class IRMessaging {
    
    private:
    
        byte _txPin; 
		byte _rxPin;
        
		IRrecv *_irRecv;  
		IRsend _irSend;

		IRMessage _message;

		decode_results results;


    

    public:
    
        IRMessaging(byte txPin, byte rxPin) ;

		void enableRX();
        
        IRMessage getIRMessage() ; 
        void sendIRMessage(IRMessage message) ;
    


         
    
} ; 
