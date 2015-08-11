/**
 * Use continuous mode to run averages on multiple channels.
 *
 * See example "ContinuousMode" to learn more details about the continuous mode.
 *
 * Copyright (c) 2014 Circuitar
 * All rights reserved.
 *
 * This software is released under a BSD license. See the attached LICENSE file for details.
 */
#include <Wire.h>
#include <Nanoshield_ADC.h>

// Sampling time per channel, in milliseconds
#define SAMPLING_TIME 200

Nanoshield_ADC adc;

// Current channel
int channel = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("ADC Nanoshield - Continuous Mode - Multi-Channel Averaging");
  adc.begin();
  
  // Set sample rate
  adc.setSampleRate(860);
  
  // Enter continuous mode
  adc.setContinuous(true);
  
  Serial.print("Configured sample rate: ");
  Serial.print(adc.getSampleRate());
  Serial.println(" SPS");
  Serial.println("The actual sample rate will be lower because of I2C communications");
  Serial.println();
}

void loop()
{
  unsigned int count = 0;      // Sample count
  unsigned long sum = 0;       // ADC value sum
  unsigned long t0 = millis(); // Sampling start time

  // Start reading the current channel
  adc.readADC_SingleEnded(channel);

  // Average during the time defined in SAMPLING_TIME
  while (millis() - t0 < SAMPLING_TIME) {
    while (!adc.conversionDone());
    sum += adc.readNext();
    count++;
  }

  Serial.print("Channel ");
  Serial.print(channel);
  Serial.print(": ");
  Serial.print(count);
  Serial.print(" samples, avg = ");
  Serial.println(sum / count);
  
  // Select the next channel
  channel++;
  if (channel >= 4) {
    channel = 0;
    Serial.println();
  }
}

