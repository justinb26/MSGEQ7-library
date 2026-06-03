// SerialPlotter (ESP32)
// Streams the seven MSGEQ7 bands in a format suitable for the Arduino IDE
// Serial Plotter (Tools -> Serial Plotter). Each band is a separate trace.
//
// Wiring matches the Poll_MSGEQ7 example:
//   MSGEQ7 OUT    -> GPIO36 (ADC1_CH0 / VP)
//   MSGEQ7 STROBE -> GPIO18
//   MSGEQ7 RESET  -> GPIO19

#include <MSGEQ7.h>

MSGEQ7 msgeq7;

// Bands below this are treated as silence/noise floor and clamped to zero.
const int NOISE_FLOOR = 80;

void setup()
{
  Serial.begin(115200);
  msgeq7.init(36, 18, 19); // analog, strobe, reset
}

void loop()
{
  msgeq7.poll();

  for (int i = 0; i < 7; i++)
  {
    int v = msgeq7.getValue(i);
    if (v < NOISE_FLOOR) v = 0;

    Serial.print(v);
    if (i < 6) Serial.print('\t'); // tab-separated for the plotter
  }
  Serial.println();

  delay(50);
}
