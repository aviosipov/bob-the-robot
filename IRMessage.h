#pragma once

class IRMessage
{

private:

	unsigned long _message; 
	


public:

	byte group; 
	byte sender; 
	byte command; 
	byte param; 
	byte receiver; 
	byte id; 
	
	unsigned int hexToDec(String str); 

	IRMessage(); 	
	void decode(unsigned long message); 
	
};

