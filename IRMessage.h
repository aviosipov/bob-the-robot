#pragma once

#define validMessageCodeMin 268435456  // min in hex 10000000 ( 1st group ) 
#define validMessageCodeMax 805306367  // max in hex 2FFFFFFF ( 2nd group )



class IRMessage
{

private:

	bool _isValid; 
	


public:

	byte group; 
	byte sender; 
	byte command; 
	byte param; 
	byte receiver;  
	byte id; 
	
	unsigned int hexToDec(String str); 

	bool isValid(); 
	IRMessage(); 	
	void decode(unsigned long message); 
	
};

