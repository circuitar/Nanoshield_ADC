/**
 * Read a differential voltage between channels 2 (+) and 3 (-).
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
  Serial.println("16-bit ADC Nanoshield Test - Read differential voltage between channels 2 (+) and 3 (-)");
  adc.begin();
}

void loop()
{
  // To read between channels 0 (+) and 1 (-), use adc.readDifferentialVoltage01() instead
  Serial.print(adc.readDifferentialVoltage23());
  Serial.println("V");
  
  delay(1000);
}
