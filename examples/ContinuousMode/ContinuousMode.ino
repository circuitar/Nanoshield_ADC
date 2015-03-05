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
Nanoshield_ADC16 adc;

// Use channel 0 (input A0)
int channel = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("ADC Nanoshield - Continuous Mode");
  adc.begin();
  
  // Set sample rate. Possible values are:
  //   - 12-bit (Nanoshield_ADC12): 128, 250, 490, 920, 1600, 2400, 3300
  //   - 16-bit (Nanoshield_ADC16): 8, 16, 32, 64, 128, 250, 475, 860 
  // If not one of the above, the closest lower value will be selected.
  adc.setSampleRate(860);
  
  // Enter continuous mode reading channel 0 (input A0)
  adc.setContinuous(true);
  adc.readADC_SingleEnded(channel);
  
  Serial.print("Configured sample rate: ");
  Serial.print(adc.getSampleRate());
  Serial.println(" SPS");
  Serial.println("The actual sample rate will be lower because of I2C communication time");
}

void loop()
{
  unsigned int count = 0;      // Sample count
  unsigned long sum = 0;       // ADC value sum
  unsigned long t0 = millis(); // Sampling start time

  // Sample continuously during one second
  while (millis() - t0 < 1000) {
    // Wait for conversion. This is optional as adc.readNext() already does
    //   it, but it can be used in a non-blocking way to check the ADC status
    //   periodically and do something else the conversion is being done.
    while (!adc.conversionDone());
    
    // Read ADC value
    sum += adc.readNext();
    count++;
  }
  
  Serial.print(count);
  Serial.print(" SPS, avg value = ");
  Serial.println(sum / count);
}
