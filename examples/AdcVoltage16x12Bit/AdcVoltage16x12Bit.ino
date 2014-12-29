/**
 * Display the voltage measured at four 16-bit channels.
 */
#include <Wire.h>
#include <Nanoshield_ADC.h>

#define ADC_VREF 6.144

Nanoshield_ADC12 adc[4] = { 0x48, 0x49, 0x4A, 0x4B };

void setup()
{
  Serial.begin(9600);
  Serial.println("ADC Nanoshield Test - Voltage Measurement - 16 x 12-bit");
  Serial.println("");

  for (int i = 0; i < 4; i++) {
    adc[i].begin();
  }
}

void loop()
{
  for (int i = 0; i < 16; i++) {
    Serial.print("A");
    Serial.print(i%4);
    Serial.print(" (");
    Serial.print(i/4);
    Serial.print(") voltage: ");
    Serial.print(adc2volts(adc[i/4].readADC_SingleEnded(i%4), ADC_VREF));
    Serial.println("V");
  }
  Serial.println();
  
  delay(1000);
}

float adc2volts(float adc, float vref)
{
  return adc * vref / 2047;
}
