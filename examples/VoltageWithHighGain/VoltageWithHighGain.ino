/**
 * Read a voltage with a high gain.
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
  Serial.print("16-bit ADC Nanoshield Test - Read voltage with high gain (channel A");
  Serial.print(channel);
  Serial.println(")");
  adc.begin();
  
  // Adjust gain to four. Possible values are:
  //   GAIN_TWOTHIRDS = 6.144V range
  //   GAIN_ONE       = 4.096V range
  //   GAIN_TWO       = 2.048V range
  //   GAIN_FOUR      = 1.024V range
  //   GAIN_EIGHT     = 0.512V range
  //   GAIN_SIXTEEN   = 0.256V range
  adc.setGain(GAIN_FOUR);
}

void loop()
{
  Serial.print(adc.readVoltage(channel), 3);
  Serial.println("V");
  
  delay(1000);
}
