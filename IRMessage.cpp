#include "Arduino.h"
#include "WString.h"; 
#include "IRMessage.h"
 

unsigned long IRMessage::hexToDec(String hexString)
{

	/*
	
	This method/service is used to decode IR messages and decode message
	attributes. 

	IR message is 8 bit hex string, with the follwoing format [ group , sender , command , param , receiver , id ] 
	for example : 1A7154F0

	1  - group 
	A  - sender id 
	7  - command
	15 - param 
	4  - receiver id 
	F0 - id ( random generated number )	
	
	*/


	unsigned long decValue = 0;
	int nextInt;
	
	for (int i = 0; i < hexString.length(); i++) {

		nextInt = int(hexString.charAt(i));
		if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);
		if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);
		if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);
		nextInt = constrain(nextInt, 0, 15);

		decValue = (decValue * 16) + nextInt;
	} 

	return decValue;
}

String IRMessage::decToHex(byte decValue, byte desiredStringLength)
{
	String hexString = String(decValue, HEX);
	while (hexString.length() < desiredStringLength) hexString = "0" + hexString;

	return hexString;
}


bool IRMessage::isValid()
{

	return _isValid; 
}

unsigned long IRMessage::getRawData()
{
	return _rawData;
}

IRMessage::IRMessage()
{
	_rawData = 0; 

	group = 0; 
	sender = 0;
	command = 0;
	param = 0;
	receiver = 0;
	id = 0;

}


void IRMessage::decode(unsigned long message)
{

	_rawData = message; 

	if (message >= validMessageCodeMin && message <= validMessageCodeMax) {

		String tmp = String(message, HEX);

		group = hexToDec((String)tmp.charAt(0));
		sender = hexToDec((String)tmp.charAt(1));
		command = hexToDec((String)tmp.charAt(2));
		param = hexToDec(tmp.substring(3, 5));
		receiver = hexToDec((String)tmp.charAt(5));
		id = hexToDec(tmp.substring(6, 8));

		_isValid = true; 

	}
	else {

		_isValid = false;

	}


}

unsigned long IRMessage::encode()
{

	String s = decToHex(group, 1) + decToHex(sender, 1) + decToHex(command, 1) + decToHex(param, 2) + decToHex(receiver, 1) + decToHex(id, 2); 
	return hexToDec(s); 

}


