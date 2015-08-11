/**
 * Display the voltage measured at four 16-bit channels.
 *
 * Copyright (c) 2014 Circuitar
 * All rights reserved.
 *
 * This software is released under a BSD license. See the attached LICENSE file for details.
 */
#include <Wire.h>
#include <Nanoshield_ADC.h>

Nanoshield_ADC adc[4] = { 0x48, 0x49, 0x4A, 0x4B };

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
    Serial.print(adc[i/4].readVoltage(i%4));
    Serial.println("V");
  }
  Serial.println();
  
  delay(1000);
}
