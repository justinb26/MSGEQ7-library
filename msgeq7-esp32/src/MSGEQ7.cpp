// MSGEQ7.cpp
// ESP32 Arduino port of the MSGEQ7 Audio Spectrum Analyzer library.
// Original Arduino library: https://github.com/justinb26/msgeq7-library
// Credit to J Skoba (http://nuewire.com/info-archive/msgeq7-by-j-skoba/)
// for the original implementation.

#include "MSGEQ7.h"

MSGEQ7::MSGEQ7()
{
  // Sensible ESP32 defaults: GPIO36 (ADC1_CH0 / "VP") for the analog input,
  // and two ordinary GPIOs for strobe and reset.
  analogPin = 36;
  strobePin = 18;
  resetPin = 19;
  settleMicros = 36; // datasheet output settle time
}

void MSGEQ7::init(int analogPin, int strobePin, int resetPin)
{
  this->analogPin = analogPin;
  this->strobePin = strobePin;
  this->resetPin = resetPin;

  pinMode(this->strobePin, OUTPUT);
  pinMode(this->resetPin, OUTPUT);

  // Configure the ESP32 ADC. Unlike the AVR core there is no
  // analogReference(DEFAULT); resolution and attenuation are set explicitly.
  analogReadResolution(12); // 0-4095 full scale

#if defined(ESP32)
  // 11dB attenuation gives the widest input range (~0-3.1V) on the ADC pin.
  analogSetPinAttenuation(this->analogPin, ADC_11db);
#endif

  // Idle state: reset low, strobe high.
  digitalWrite(this->resetPin, LOW);
  digitalWrite(this->strobePin, HIGH);
}

void MSGEQ7::poll()
{
  // Pulse reset to start the read at the first (63Hz) band.
  digitalWrite(this->resetPin, HIGH);
  digitalWrite(this->resetPin, LOW);

  for (int i = 0; i < 7; i++)
  {
    digitalWrite(this->strobePin, LOW);
    delayMicroseconds(this->settleMicros); // allow the output to settle
    this->spectrumValues[i] = analogRead(this->analogPin);
    digitalWrite(this->strobePin, HIGH);
  }

  digitalWrite(this->resetPin, LOW);
  digitalWrite(this->strobePin, HIGH);
}

int MSGEQ7::getValue(int index)
{
  return this->spectrumValues[index];
}

int MSGEQ7::getValue(FREQ freq)
{
  return this->spectrumValues[freq];
}

void MSGEQ7::setResolution(int bits)
{
  analogReadResolution(bits);
}

void MSGEQ7::setSettleTime(unsigned int settleMicros)
{
  this->settleMicros = settleMicros;
}
