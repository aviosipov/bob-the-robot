#pragma once

#define validMessageCodeMin 65536  // min in hex 10000 
#define validMessageCodeMax 1048575  // max in hex FFFFF



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

