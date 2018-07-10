#include <MSGEQ7.h>

MSGEQ7 msgeq7;

void setup()
{
  Serial.begin(9600);
  msgeq7.init(A0, 2, 3); // Initialize Output, Strobe, and Reset Pins
}

void loop()
{
  msgeq7.poll(); // Update values from MSGEQ7  
  showValues();  // Print the current EQ values to Serial
  delay(2);      // Let analog pin's ADC settle before next reading
}

void showValues()
{
  Serial.print("Current values - ");
  
  Serial.print("63HZ: ");
  Serial.print(msgeq7.getValue(0));
  
  Serial.print(" 160HZ: ");
  Serial.print(msgeq7.getValue(1));

  Serial.print(" 400HZ: ");
  Serial.print(msgeq7.getValue(2));

  Serial.print(" 1000HZ: ");
  Serial.print(msgeq7.getValue(3));

  Serial.print(" 4500HZ: ");
  Serial.print(msgeq7.getValue(4));

  Serial.print(" 6250HZ: ");
  Serial.print(msgeq7.getValue(5));

  Serial.print(" 16000HZ: ");
  Serial.print(msgeq7.getValue(6));

  Serial.println(); 
}
