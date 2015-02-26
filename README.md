Nanoshield_ADC
==============

This is the Arduino software library to access the ADC Nanoshield (ADS1x15 IC).

The ADC Nanoshield offers a solution for applications that need analog to digital conversion with higher resolution or when the number of analog inputs of your MCU isn't enough.

To install, just copy it under &lt;arduinosketchfolder&gt;/libraries/

This library is based on the [Adafruit_ADS1X15](https://github.com/adafruit/Adafruit_ADS1X15) library from Adafruit.

---

The following examples are provided:

- **Voltage**: read a voltage in single-ended mode (16-bit version).
- **VoltageWithHighGain**: read a voltage in single-ended mode with a high gain (16-bit version). Increasing the gain allows reading smaller voltages with increased resolution.
- **Voltage4Ch16Bit**: read four voltages in a single 16-bit ADC Nanoshield.
- **Voltage16Ch12Bit**: using multiple boards. Read sixteen voltages across four units of the 12-bit ADC Nanoshield. Make sure that the solder jumpers for the I2C address are properly configured to support this example.
- **DifferentialVoltage**: read a differential voltage between inputs 2 (+) and 3 (-) (16-bit version). The channels can be easily changed to 0 (+) and 1 (-).
- **Read4to20mA**: how to read data from industrial 4-20mA sensors (or 4-20mA "transmistters"). Make sure that ADC Nanoshield being used is factory configured for this type of operation.

Most examples are provided for the 16-bit version of the ADC Nanoshield, but can be easily modified to support the 12-bit version by changing the type of the `adc` variable from `Nanoshield_ADC16` to `Nanoshield_ADC12`.

---
Original work Copyright (c) 2012, Adafruit Industries  
Modified work Copyright (c) 2014 Circuitar  
All rights reserved.

This software is released under a BSD license. See the attached LICENSE file for details.
