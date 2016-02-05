#include "Arduino.h"
#include <NewTone.h>
#include "SoundPlayer.h"
	


SoundPlayer::SoundPlayer(byte speakerPin)
{
	_speakerPin = speakerPin; 
}

void SoundPlayer::playGun()
{
	
	noise(NOTE_E6, 100, 20);
	noise(NOTE_G6, 100, 50);
	
}

void SoundPlayer::playCoin()
{
	delay(100);
	NewTone(_speakerPin, NOTE_E6, 250);
	delay(100);
	noNewTone(_speakerPin);
}

void SoundPlayer::play1UP()
{
	NewTone(_speakerPin, NOTE_E6, 60);
	//delay(85);
	NewTone(_speakerPin, NOTE_G6, 60);
	//delay(85);
	NewTone(_speakerPin, NOTE_E7, 60);
	//delay(85);
	NewTone(_speakerPin, NOTE_C7, 60);
	//delay(85);
	NewTone(_speakerPin, NOTE_D7, 60);
	//delay(85);
	NewTone(_speakerPin, NOTE_G7, 60);
	//delay(85);
	noNewTone(_speakerPin);
}

void SoundPlayer::explosion()
{
	noise(700, 40, 20);
	noise(450, 30, 15);
	noise(300, 20, 10);
	noise(250, 20, 10);
	noise(120, 30, 80);
	noise(100, 40, 80);

}

void SoundPlayer::noise(int freq, int var, int duration)
{
	
	int low = freq - var;
	int high = freq + var;

	unsigned long time = millis();

	while (millis() - time <= duration) {

		NewTone(_speakerPin, random(low, high));		
		
	}
	noNewTone(_speakerPin);
	

}





