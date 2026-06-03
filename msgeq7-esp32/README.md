# MSGEQ7-ESP32

ESP32 Arduino library for the [MSGEQ7](https://www.sparkfun.com/products/10468)
audio spectrum analyzer chip. This is an ESP32 port of the original
[msgeq7-library](https://github.com/justinb26/msgeq7-library) and still uses the
Arduino toolchain (Arduino IDE / arduino-cli with the
[arduino-esp32](https://github.com/espressif/arduino-esp32) core).

Credit to J Skoba (http://nuewire.com/info-archive/msgeq7-by-j-skoba/) for the
original implementation.

## What changed for the ESP32

- **12-bit ADC.** `analogRead()` returns `0-4095` on the ESP32 (vs. `0-1023` on
  classic AVR Arduinos). `getValue()` returns the raw reading, so scale
  accordingly. Resolution is configurable via `setResolution()`.
- **No `analogReference()`.** The AVR `analogReference(DEFAULT)` call is replaced
  by `analogReadResolution()` and ADC attenuation. The library sets `ADC_11db`
  attenuation on the analog pin for the widest input range (~0-3.1V).
- **3.3V logic.** The ESP32 is a 3.3V part. When the MSGEQ7 is powered from 5V
  its analog output can exceed the ESP32's safe input range — power the MSGEQ7
  from 3.3V or scale the output down to 0-3.3V.
- **ADC1 pins.** Use an ADC1 channel (GPIO 32-39) for the analog input; ADC2
  pins are unavailable while Wi-Fi is active.
- Dropped the invalid `#define 63HZ 0` from the original header (identifiers
  cannot begin with a digit).

## Installation

Copy this folder into your Arduino `libraries/` directory (or install via the
Library Manager once published), then restart the Arduino IDE.

## Wiring (example defaults)

| MSGEQ7 pin | ESP32 pin            |
|------------|----------------------|
| OUT        | GPIO36 (ADC1_CH0/VP) |
| STROBE     | GPIO18               |
| RESET      | GPIO19               |

## Usage

```cpp
#include <MSGEQ7.h>

MSGEQ7 msgeq7;

void setup() {
  Serial.begin(115200);
  msgeq7.init(36, 18, 19); // analog, strobe, reset
}

void loop() {
  msgeq7.poll();
  Serial.println(msgeq7.getValue(HZ_1000)); // raw 0-4095
  delay(50);
}
```

## API

| Method | Description |
|--------|-------------|
| `void init(int analogPin, int strobePin, int resetPin)` | Configure pins and initialise the ADC. |
| `void poll()` | Read all seven bands into the internal buffer. |
| `int getValue(int index)` | Get the last polled value for band `0-6`. |
| `int getValue(FREQ freq)` | Get the last polled value by `FREQ` enum. |
| `void setResolution(int bits)` | Set ADC resolution (9-12, default 12). |
| `void setSettleTime(unsigned int us)` | Output settle time after each strobe (default 36µs). |

The `FREQ` enum: `HZ_63`, `HZ_160`, `HZ_400`, `HZ_1000`, `HZ_2500`, `HZ_6250`,
`HZ_16000`.

## Examples

- **Poll_MSGEQ7** — prints all seven bands to the Serial monitor.
- **SerialPlotter** — tab-separated output for the Arduino IDE Serial Plotter.
