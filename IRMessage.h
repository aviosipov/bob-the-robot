#pragma once

#define validMessageCodeMin 4096  // min in hex 1000 
#define validMessageCodeMax 65535  // max in hex FFFF



class IRMessage
{

private:

	bool _isValid; 
	unsigned long _rawData; 


	byte _messageLength; 
	


public:

	byte group; 
	byte sender; 
	byte command; 
	byte param; 
	byte receiver;  
	byte id; 

	byte getMessageLength(); 

	byte getID(); 
	
	unsigned long hexToDec(String str); 
	String decToHex(byte decValue, byte desiredStringLength); 

	bool isValid();  
	unsigned long getRawData(); 

	IRMessage(); 	

	void decode(unsigned long message); 
	unsigned long encode();

	
};

