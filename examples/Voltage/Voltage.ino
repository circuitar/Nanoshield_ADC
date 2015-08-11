/**
 * Read a voltage.
 *
 * Copyright (c) 2014 Circuitar
 * All rights reserved.
 *
 * This software is released under a BSD license. See the attached LICENSE file for details.
 */
#include <Wire.h>
#include <Nanoshield_ADC.h>

Nanoshield_ADC adc;
int channel = 0;

void setup()
{
  Serial.begin(9600);
  Serial.print("16-bit ADC Nanoshield Test - Read voltage (channel A");
  Serial.print(channel);
  Serial.println(")");
  adc.begin();
}

void loop()
{
  Serial.print(adc.readVoltage(channel));
  Serial.println("V");
  
  delay(1000);
}
