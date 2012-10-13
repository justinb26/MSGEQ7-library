// MSGEQ7.cpp
// Library for controlling MSGEQ7 Audio Spectrum Analyzer Chip (https://www.sparkfun.com/products/10468)
// Credit to J Skoba (http://nuewire.com/info-archive/msgeq7-by-j-skoba/) for the original implementation

#include "MSGEQ7.h"

MSGEQ7::MSGEQ7() 
{
	MSGEQ7::analogPin = A0;
	MSGEQ7::strobePin = 2;
	MSGEQ7::resetPin = 3;
}

void MSGEQ7::init(int analogPin, int strobePin, int resetPin)
{
	MSGEQ7::analogPin = analogPin;
	MSGEQ7::strobePin = strobePin;
	MSGEQ7::resetPin = resetPin;

	pinMode(MSGEQ7::analogPin, INPUT);
	pinMode(MSGEQ7::strobePin, OUTPUT);
	pinMode(MSGEQ7::resetPin, OUTPUT);
	analogReference(DEFAULT);
}

void MSGEQ7::poll()
{
 digitalWrite(MSGEQ7::resetPin, HIGH);
 digitalWrite(MSGEQ7::resetPin, LOW);

 for (int i = 0; i < 7; i++)
 {
   digitalWrite(MSGEQ7::strobePin, LOW);
   delayMicroseconds(30); // to allow the output to settle
   MSGEQ7::spectrumValues[i] = analogRead(MSGEQ7::analogPin);  
   digitalWrite(MSGEQ7::strobePin, HIGH);
 }

 digitalWrite(MSGEQ7::resetPin, LOW);
 digitalWrite(MSGEQ7::strobePin, HIGH);
}

int MSGEQ7::getValue(int index)
{
	return MSGEQ7::spectrumValues[index];
}

int MSGEQ7::getValue(FREQ freq)
{
	return MSGEQ7::spectrumValues[freq];
}