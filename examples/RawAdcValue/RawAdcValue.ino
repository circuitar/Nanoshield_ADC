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
  Serial.print("16-bit ADC Nanoshield Test - Read raw ADC value (channel A");
  Serial.print(channel);
  Serial.println(")");
  adc.begin();
}

void loop()
{
  Serial.println(adc.readADC_SingleEnded(channel));
  
  delay(1000);
}
