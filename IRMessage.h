#pragma once

#define validMessageCodeMin 268435456  // min in hex 10000000 ( 1st group ) 
#define validMessageCodeMax 805306367  // max in hex 2FFFFFFF ( 2nd group )



class IRMessage
{

private:

	bool _isValid; 
	unsigned long _rawData; 
	


public:

	byte group; 
	byte sender; 
	byte command; 
	byte param; 
	byte receiver;  
	byte id; 
	
	unsigned long hexToDec(String str); 
	String decToHex(byte decValue, byte desiredStringLength); 

	bool isValid();  
	unsigned long getRawData(); 

	IRMessage(); 	

	void decode(unsigned long message); 
	unsigned long encode();

	
};

