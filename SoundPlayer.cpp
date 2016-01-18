#include <NewTone.h>
#include "SoundPlayer.h"
	


SoundPlayer::SoundPlayer(short speakerPin)
{
	_speakerPin = speakerPin; 
}

void SoundPlayer::playGun()
{
	NewTone(_speakerPin, NOTE_G4, 35);
	delay(35);
	NewTone(_speakerPin, NOTE_G5, 35);
	delay(35);
	NewTone(_speakerPin, NOTE_G6, 35);
	delay(35);
	noNewTone(_speakerPin);
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
	NewTone(_speakerPin, NOTE_E6, 80);
	delay(85);
	NewTone(_speakerPin, NOTE_G6, 80);
	delay(85);
	NewTone(_speakerPin, NOTE_E7, 80);
	delay(85);
	NewTone(_speakerPin, NOTE_C7, 80);
	delay(85);
	NewTone(_speakerPin, NOTE_D7, 80);
	delay(85);
	NewTone(_speakerPin, NOTE_G7, 80);
	delay(85);
	noNewTone(_speakerPin);
}

void SoundPlayer::noise(int freq, int duration)
{
	
	int low = freq - 300;
	int high = freq + 300;

	unsigned long time = millis();
	while (millis() - time <= duration) {
		NewTone(_speakerPin, random(low, high));
	}
	noNewTone(_speakerPin);
	

}





