// Poll_MSGEQ7 (ESP32)
// Reads the seven MSGEQ7 bands and prints them to the Serial monitor.
//
// Wiring (defaults below):
//   MSGEQ7 OUT    -> GPIO36 (ADC1_CH0 / VP)   [scale to 0-3.3V if powered at 5V]
//   MSGEQ7 STROBE -> GPIO18
//   MSGEQ7 RESET  -> GPIO19
//
// Use an ADC1 pin (GPIO 32-39) so the ADC keeps working while Wi-Fi is on.

#include <MSGEQ7.h>

MSGEQ7 msgeq7;

void setup()
{
  Serial.begin(115200);
  msgeq7.init(36, 18, 19); // analog, strobe, reset
}

void loop()
{
  msgeq7.poll(); // Update values from MSGEQ7
  showValues();  // Print the current EQ values to Serial
  delay(50);
}

void showValues()
{
  Serial.print("Current values - ");

  Serial.print("63HZ: ");
  Serial.print(msgeq7.getValue(HZ_63));

  Serial.print(" 160HZ: ");
  Serial.print(msgeq7.getValue(HZ_160));

  Serial.print(" 400HZ: ");
  Serial.print(msgeq7.getValue(HZ_400));

  Serial.print(" 1000HZ: ");
  Serial.print(msgeq7.getValue(HZ_1000));

  Serial.print(" 2500HZ: ");
  Serial.print(msgeq7.getValue(HZ_2500));

  Serial.print(" 6250HZ: ");
  Serial.print(msgeq7.getValue(HZ_6250));

  Serial.print(" 16000HZ: ");
  Serial.print(msgeq7.getValue(HZ_16000));

  Serial.println();
}
