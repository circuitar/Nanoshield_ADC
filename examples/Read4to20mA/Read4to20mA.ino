/**
 * Read a 4-20mA sensor.
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
  Serial.print("16-bit ADC Nanoshield Test - Read 4-20mA sensor (channel A");
  Serial.print(channel);
  Serial.println(")");
  adc.begin();

  // Adjust gain to two (2.048V range) to get maximum resolution for 4-20mA range
  adc.setGain(GAIN_TWO);
}

void loop()
{
  Serial.print(adc.read4to20mA(channel), 6);
  Serial.println("mA");
  
  delay(1000);
}