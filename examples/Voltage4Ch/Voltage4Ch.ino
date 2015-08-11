/**
 * Display the voltage measured at four channels.
 *
 * Copyright (c) 2014 Circuitar
 * All rights reserved.
 *
 * This software is released under a BSD license. See the attached LICENSE file for details.
 */
#include <Wire.h>
#include <Nanoshield_ADC.h>

Nanoshield_ADC adc;

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
    Serial.print(adc.readVoltage(i));
    Serial.println("V");
  }
  Serial.println();
  
  delay(1000);
}
