/*
This is the library to use the ADC Nanoshield.

This library is based on the Adafruit_ADS1X15 library from Adafruit (https://github.com/adafruit/Adafruit_ADS1X15).

Original work Copyright (c) 2012, Adafruit Industries
Modified work Copyright (c) 2014 Circuitar
All rights reserved.

This software is released under a BSD license. See the attached LICENSE file for details.
*/

#ifndef NANOSHIELD_ADC_H
#define NANOSHIELD_ADC_H

#ifdef ARDUPI
    #include "arduPi.h"
#else
    #include "Arduino.h"
    #include <Wire.h>
#endif

/*==========================================================================
I2C ADDRESS/BITS
----------------------------------------------------------------------------*/
#define ADS1X15_ADDRESS                 (0x48)    // 0100 1000 (ADDR = GND)
/*==========================================================================*/

/*==========================================================================
POINTER REGISTER
----------------------------------------------------------------------------*/
#define ADS1015_REG_POINTER_MASK        (0x03)
#define ADS1015_REG_POINTER_CONVERT     (0x00)
#define ADS1015_REG_POINTER_CONFIG      (0x01)
#define ADS1015_REG_POINTER_LOWTHRESH   (0x02)
#define ADS1015_REG_POINTER_HITHRESH    (0x03)
/*==========================================================================*/

/*==========================================================================
CONFIG REGISTER
----------------------------------------------------------------------------*/
#define ADS1015_REG_CONFIG_OS_MASK      (0x8000)
#define ADS1015_REG_CONFIG_OS_SINGLE    (0x8000)  // Write: Set to start a single-conversion
#define ADS1015_REG_CONFIG_OS_BUSY      (0x0000)  // Read: Bit = 0 when conversion is in progress
#define ADS1015_REG_CONFIG_OS_NOTBUSY   (0x8000)  // Read: Bit = 1 when device is not performing a conversion

#define ADS1015_REG_CONFIG_MUX_MASK     (0x7000)
#define ADS1015_REG_CONFIG_MUX_DIFF_0_1 (0x0000)  // Differential P = AIN0, N = AIN1 (default)
#define ADS1015_REG_CONFIG_MUX_DIFF_0_3 (0x1000)  // Differential P = AIN0, N = AIN3
#define ADS1015_REG_CONFIG_MUX_DIFF_1_3 (0x2000)  // Differential P = AIN1, N = AIN3
#define ADS1015_REG_CONFIG_MUX_DIFF_2_3 (0x3000)  // Differential P = AIN2, N = AIN3
#define ADS1015_REG_CONFIG_MUX_SINGLE_0 (0x4000)  // Single-ended AIN0
#define ADS1015_REG_CONFIG_MUX_SINGLE_1 (0x5000)  // Single-ended AIN1
#define ADS1015_REG_CONFIG_MUX_SINGLE_2 (0x6000)  // Single-ended AIN2
#define ADS1015_REG_CONFIG_MUX_SINGLE_3 (0x7000)  // Single-ended AIN3

#define ADS1015_REG_CONFIG_PGA_MASK     (0x0E00)
#define ADS1015_REG_CONFIG_PGA_6_144V   (0x0000)  // +/-6.144V range = Gain 2/3
#define ADS1015_REG_CONFIG_PGA_4_096V   (0x0200)  // +/-4.096V range = Gain 1
#define ADS1015_REG_CONFIG_PGA_2_048V   (0x0400)  // +/-2.048V range = Gain 2 (default)
#define ADS1015_REG_CONFIG_PGA_1_024V   (0x0600)  // +/-1.024V range = Gain 4
#define ADS1015_REG_CONFIG_PGA_0_512V   (0x0800)  // +/-0.512V range = Gain 8
#define ADS1015_REG_CONFIG_PGA_0_256V   (0x0A00)  // +/-0.256V range = Gain 16

#define ADS1015_REG_CONFIG_MODE_MASK    (0x0100)
#define ADS1015_REG_CONFIG_MODE_CONTIN  (0x0000)  // Continuous conversion mode
#define ADS1015_REG_CONFIG_MODE_SINGLE  (0x0100)  // Power-down single-shot mode (default)

#define ADS1015_REG_CONFIG_DR_MASK      (0x00E0)  
#define ADS1015_REG_CONFIG_DR_128SPS    (0x0000)  // 128 samples per second
#define ADS1015_REG_CONFIG_DR_250SPS    (0x0020)  // 250 samples per second
#define ADS1015_REG_CONFIG_DR_490SPS    (0x0040)  // 490 samples per second
#define ADS1015_REG_CONFIG_DR_920SPS    (0x0060)  // 920 samples per second
#define ADS1015_REG_CONFIG_DR_1600SPS   (0x0080)  // 1600 samples per second (default)
#define ADS1015_REG_CONFIG_DR_2400SPS   (0x00A0)  // 2400 samples per second
#define ADS1015_REG_CONFIG_DR_3300SPS   (0x00C0)  // 3300 samples per second

#define ADS1115_REG_CONFIG_DR_MASK      (0x00E0)  
#define ADS1115_REG_CONFIG_DR_8SPS      (0x0000)  // 8 samples per second
#define ADS1115_REG_CONFIG_DR_16SPS     (0x0020)  // 16 samples per second
#define ADS1115_REG_CONFIG_DR_32SPS     (0x0040)  // 32 samples per second
#define ADS1115_REG_CONFIG_DR_64SPS     (0x0060)  // 64 samples per second
#define ADS1115_REG_CONFIG_DR_128SPS    (0x0080)  // 128 samples per second (default)
#define ADS1115_REG_CONFIG_DR_250SPS    (0x00A0)  // 250 samples per second
#define ADS1115_REG_CONFIG_DR_475SPS    (0x00C0)  // 475 samples per second
#define ADS1115_REG_CONFIG_DR_860SPS    (0x00E0)  // 860 samples per second

#define ADS1015_REG_CONFIG_CMODE_MASK   (0x0010)
#define ADS1015_REG_CONFIG_CMODE_TRAD   (0x0000)  // Traditional comparator with hysteresis (default)
#define ADS1015_REG_CONFIG_CMODE_WINDOW (0x0010)  // Window comparator

#define ADS1015_REG_CONFIG_CPOL_MASK    (0x0008)
#define ADS1015_REG_CONFIG_CPOL_ACTVLOW (0x0000)  // ALERT/RDY pin is low when active (default)
#define ADS1015_REG_CONFIG_CPOL_ACTVHI  (0x0008)  // ALERT/RDY pin is high when active

#define ADS1015_REG_CONFIG_CLAT_MASK    (0x0004)  // Determines if ALERT/RDY pin latches once asserted
#define ADS1015_REG_CONFIG_CLAT_NONLAT  (0x0000)  // Non-latching comparator (default)
#define ADS1015_REG_CONFIG_CLAT_LATCH   (0x0004)  // Latching comparator

#define ADS1015_REG_CONFIG_CQUE_MASK    (0x0003)
#define ADS1015_REG_CONFIG_CQUE_1CONV   (0x0000)  // Assert ALERT/RDY after one conversions
#define ADS1015_REG_CONFIG_CQUE_2CONV   (0x0001)  // Assert ALERT/RDY after two conversions
#define ADS1015_REG_CONFIG_CQUE_4CONV   (0x0002)  // Assert ALERT/RDY after four conversions
#define ADS1015_REG_CONFIG_CQUE_NONE    (0x0003)  // Disable the comparator and put ALERT/RDY in high state (default)
/*==========================================================================*/

typedef enum {
  GAIN_TWOTHIRDS    = ADS1015_REG_CONFIG_PGA_6_144V,
  GAIN_ONE          = ADS1015_REG_CONFIG_PGA_4_096V,
  GAIN_TWO          = ADS1015_REG_CONFIG_PGA_2_048V,
  GAIN_FOUR         = ADS1015_REG_CONFIG_PGA_1_024V,
  GAIN_EIGHT        = ADS1015_REG_CONFIG_PGA_0_512V,
  GAIN_SIXTEEN      = ADS1015_REG_CONFIG_PGA_0_256V
} Gain_t;

class Nanoshield_ADC12 {
  protected:
    uint8_t m_i2cAddress;
    uint8_t m_bitShift;
    Gain_t m_gain;
    float m_range;
    uint16_t m_spsMask;
    uint32_t m_nextReadingTime;
    bool m_continuous;
    bool m_comparator;
    uint16_t getConfig();
    uint32_t getNextReadingTime();

  public:
    Nanoshield_ADC12(uint8_t i2cAddress = ADS1X15_ADDRESS);
    void writeRegister(uint8_t, uint8_t, uint16_t);
    uint16_t readRegister(uint8_t, uint8_t);
    void begin();
    int16_t readADC_SingleEnded(uint8_t);
    int16_t readADC_Differential_0_1();
    int16_t readADC_Differential_2_3();
    int16_t getLastConversionResults();
    void setComparator(uint8_t channel, int16_t highThreshold, int16_t lowThreshold);
    void setNotComparator();
    bool isComparator();
    void startComparator_SingleEnded(uint8_t, int16_t, int16_t);
    bool conversionDone();
    int16_t readNext();
    void setContinuous(bool c);
    bool isContinuous();
    void setGain(Gain_t);
    Gain_t getGain();
    float getRange();
    virtual void setSampleRate(uint16_t sps = 1600);
    virtual uint16_t getSampleRate();
    virtual float readVoltage(uint8_t);
    float read4to20mA(uint8_t);
    virtual float readDifferentialVoltage01();
    virtual float readDifferentialVoltage23();
};

class Nanoshield_ADC16 : public Nanoshield_ADC12 {
  public:
    Nanoshield_ADC16(uint8_t i2cAddress = ADS1X15_ADDRESS);
    virtual void setSampleRate(uint16_t sps = 128);
    virtual uint16_t getSampleRate();
    virtual float readVoltage(uint8_t);
    virtual float readDifferentialVoltage01();
    virtual float readDifferentialVoltage23();
};

#endif
