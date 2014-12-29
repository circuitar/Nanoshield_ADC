/**
 * Display the voltage measured at four channels.
 */
#include <Wire.h>
#include <Nanoshield_ADC.h>

#define ADC_VREF 6.144

Nanoshield_ADC16 adc; // Default I2C address = 0x48

void setup()
{
  Serial.begin(9600);
  Serial.println("ADC Nanoshield Test - Voltage Measurement - 4 x 16-bit");
  Serial.println("");
  adc.begin();
}

void loop()
{
  for (int i = 0; i < 4; i++) {
    Serial.print("A");
    Serial.print(i);
    Serial.print(" voltage: ");
    Serial.print(adc2volts(adc.readADC_SingleEnded(i), ADC_VREF));
    Serial.println("V");
  }
  Serial.println();
  
  delay(1000);
}

float adc2volts(float adc, float vref)
{
  return adc * vref / 32767;
}

