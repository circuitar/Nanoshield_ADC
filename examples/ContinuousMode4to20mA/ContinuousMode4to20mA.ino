/**
 * Use continuous mode to get high sample rates.
 *
 * Copyright (c) 2014 Circuitar
 * All rights reserved.
 *
 * This software is released under a BSD license. See the attached LICENSE file for details.
 */
#include <Wire.h>
#include <Nanoshield_ADC.h>

// 16-bit ADC (change to Nanoshield_ADC12 to use the 12-bit version)
Nanoshield_ADC adc;

// Use channel 0 (input A0)
int channel = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("ADC Nanoshield - Continuous Mode");
  adc.begin();
  
  // Adjust gain to two (2.048V range) to get maximum resolution for 4-20mA range
  adc.setGain(GAIN_TWO);

  // Set sample rate. Possible values are:
  //   - 16-bit (Nanoshield_ADC): 8, 16, 32, 64, 128, 250, 475, 860 
  // If not one of the above, the closest lower value will be selected.
  adc.setSampleRate(860);
  
  // Enter continuous mode and start reading channel 0 (input A0)
  adc.setContinuous(true);
  adc.readADC_SingleEnded(channel);
  
  Serial.print("Configured sample rate: ");
  Serial.print(adc.getSampleRate());
  Serial.println(" SPS");
  Serial.println("The actual sample rate will be lower because of I2C communications");
}

void loop()
{
  unsigned int count = 0;      // Sample count
  float sum = 0;               // ADC value sum
  unsigned long t0 = millis(); // Sampling start time

  // Sample continuously for one second
  while (millis() - t0 < 1000) {
    // Wait for conversion. This is optional, as adc.readNext() already does
    //   it, but it can be used to check the ADC status periodically in a non-
    //   blocking way and do something else while the conversion is being done.
    while (!adc.conversionDone());
    
    // Read ADC value
    sum += adc.read4to20mA(channel);
    count++;
  }
  
  Serial.print(count);
  Serial.print(" SPS, avg value = ");
  Serial.print(sum / count, 6);
  Serial.println("mA");
}