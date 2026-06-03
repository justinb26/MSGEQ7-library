// MSGEQ7.h
// ESP32 Arduino port of the MSGEQ7 Audio Spectrum Analyzer library.
// Original Arduino library: https://github.com/justinb26/msgeq7-library
// Credit to J Skoba (http://nuewire.com/info-archive/msgeq7-by-j-skoba/)
// for the original implementation.
//
// Notes for the ESP32 port:
//   - The ESP32 ADC is 12-bit (0-4095) by default, whereas classic AVR
//     Arduinos are 10-bit (0-1023). getValue() returns the raw ADC reading,
//     so account for the configured resolution when interpreting values.
//   - The ESP32 is a 3.3V part. The MSGEQ7 output swings relative to its own
//     supply, so when the chip is powered from 5V the analog output can exceed
//     the ESP32's safe input range. Either power the MSGEQ7 from 3.3V or scale
//     the analog output down to 0-3.3V before feeding it to an ESP32 ADC pin.
//   - Use an ADC1 pin (GPIO 32-39) for the analog input. ADC2 pins cannot be
//     used while Wi-Fi is active.

#ifndef MSGEQ7_ESP32_H
#define MSGEQ7_ESP32_H

#include "Arduino.h"

// The seven frequency bands reported by the MSGEQ7, in array order.
typedef enum {
  HZ_63,
  HZ_160,
  HZ_400,
  HZ_1000,
  HZ_2500,
  HZ_6250,
  HZ_16000
} FREQ;

class MSGEQ7
{
  public:
    MSGEQ7();

    // Configure the pins and initialise the ESP32 ADC. The analog pin should
    // be an ADC1 channel (GPIO 32-39).
    void init(int analogPin, int strobePin, int resetPin);

    // Read all seven bands from the chip into the internal buffer.
    void poll();

    // Retrieve the most recently polled value for a band (raw ADC reading).
    int getValue(int index);
    int getValue(FREQ freq);

    // ESP32 tuning helpers (optional). Call before or after init().
    // resolution: ADC bit width (9-12 on ESP32, default 12).
    void setResolution(int bits);
    // settleMicros: time to wait after each strobe pulse for the output to
    // settle before sampling (datasheet recommends ~36us, default 36).
    void setSettleTime(unsigned int settleMicros);

  private:
    int analogPin;
    int strobePin;
    int resetPin;

    int spectrumValues[7];
    unsigned int settleMicros;
};

#endif // MSGEQ7_ESP32_H
