/**
 * Reads a voltage above high threshold using interruption.
 * 
 * To use this example the alert jumper on Nanoshield ADC must be closed.
 * 
 * Copyright (c) 2015 Circuitar
 * All rights reserved.
 * 
 * This software is released under a BSD license. See the attached LICENSE
 * file for details.
 */
#include <Wire.h>
#include <Nanoshield_ADC.h>

void adcComparatorHandler();

Nanoshield_ADC16 adc;
int channel = 2;
int16_t hthreshold = 15000;
int16_t lthreshold = 10000;
int alertPin = 3;
int int1 = 1;
int interruption = 0;
long lastExecution = 0;

void setup() {
  // Set alertPin as INPUT
  pinMode(alertPin, INPUT);

  // Start serial connection.
  Serial.begin(9600);
  Serial.print("16-bit ADC Nanoshield Test - Comparator (channel A");
  Serial.print(channel);
  Serial.println(")\n");

  adc.begin();  // Start Nanoshield_ADC library
  adc.setSampleRate(860);    // Set a sample rate of 64Hz.
  adc.setContinuous(true);  // Enter coninuous mode.
  adc.setComparator(channel, hthreshold, lthreshold);  // Set comparator mode
  adc.readADC_SingleEnded(channel); // Set channel to read

  // Register interruption handler
  attachInterrupt(int1, adcComparatorHandler, FALLING);

  lastExecution = millis();
}

void loop() {

  // Asynchronous delay
  if(millis() - lastExecution > 1000) {
    lastExecution = millis();
    
    // Reading data from Nanoshield ADC
    int16_t adcReading = adc.readNext();
    Serial.print("Value: ");
    Serial.println(adcReading);
    Serial.print("Alert: ");

    int alert = digitalRead(alertPin);
    if(alert == HIGH) {
      Serial.println("HIGH\n");
    } else {
      Serial.println("LOW\n");
    }
  }
  
  // Process interruption flag.
  if(interruption == 1) {
    Serial.println("Interruption triggered!\n");
    interruption = 0;
  }
}

void adcComparatorHandler() {
  // Set interruption flag
  interruption = 1;
}