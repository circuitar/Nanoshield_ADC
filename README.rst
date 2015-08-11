Nanoshield_ADC
==============

This is the Arduino software library to access the ADC Nanoshield (ADS1x15 IC) from Texas Instruments.

* Source code: https://github.com/circuitar/Nanoshield_ADC
* Documentation: http://nanoshield-adc.readthedocs.org/
* Reference board: `ADC Nanoshield`_ from Circuitar

Library features include:

* Analog to digital conversion with 16 bits resolution.
* Continuous mode to capture measures with a given sample rate.
* Gain adjust to pair the signal magnitude with the resolution.
* Differential voltage measurements.
* High threshold setting to trigger interruptions.

To install, just click **Download ZIP** and install it using **Sketch > Include Library... > Add .ZIP Library** in the Arduino IDE.

This library is based on the [Adafruit_ADS1X15](https://github.com/adafruit/Adafruit_ADS1X15) library from Adafruit.

---

The following examples_ are provided:

- Voltage_ read a voltage in single-ended mode.
- VoltageWithHighGain_ read a voltage in single-ended mode with a high gain. Increasing the gain allows reading smaller voltages with increased resolution.
- Voltage4Ch16Bit_ read four voltages in a single 16-bit ADC Nanoshield.
- DifferentialVoltage_ read a differential voltage between inputs 2 (+) and 3 (-). The channels can be easily changed to 0 (+) and 1 (-).
- Read4to20mA_ how to read data from industrial 4-20mA sensors (or 4-20mA "transmistters"). Make sure that ADC Nanoshield being used is factory configured for this type of operation.
- ContinuousMode_ read data in continuous mode to achieve high sample rates.
- ContinuousMode4Ch_ read multiple channels in continuous mode.

.. _`ADC Nanoshield`: https://www.circuitar.com.br/nanoshields/modulos/adc/
.. _examples: https://github.com/circuitar/Nanoshield_ADC/tree/master/examples
.. _Voltage: https://github.com/circuitar/Nanoshield_ADC/blob/master/examples/Voltage/Voltage.ino
.. _VoltageWithHighGain: https://github.com/circuitar/Nanoshield_ADC/blob/master/examples/VoltageWithHighGain/VoltageWithHighGain.ino
.. _Voltage4Ch16Bit: https://github.com/circuitar/Nanoshield_ADC/blob/master/examples/Voltage4Ch16Bit/Voltage4Ch16Bit.ino
.. _DifferentialVoltage: https://github.com/circuitar/Nanoshield_ADC/blob/master/examples/DifferentialVoltage/DifferentialVoltage.ino
.. _Read4to20mA: https://github.com/circuitar/Nanoshield_ADC/blob/master/examples/Read4to20mA/Read4to20mA.ino
.. _ContinuousMode: https://github.com/circuitar/Nanoshield_ADC/blob/master/examples/ContinuousMode/ContinuousMode.ino
.. _ContinuousMode4Ch: https://github.com/circuitar/Nanoshield_ADC/blob/master/examples/ContinuousMode4Ch/ContinuousMode4Ch.ino

----

Original work Copyright (c) 2012, Adafruit Industries  
Modified work Copyright (c) 2014 Circuitar  
All rights reserved.

This software is released under a BSD license. See the attached LICENSE file for details.
