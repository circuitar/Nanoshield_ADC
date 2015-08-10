/*
This is the library to use the ADC Nanoshield.

This library is based on the Adafruit_ADS1X15 library from Adafruit (https://github.com/adafruit/Adafruit_ADS1X15).

Original work Copyright (c) 2012, Adafruit Industries
Modified work Copyright (c) 2014 Circuitar
All rights reserved.

This software is released under a BSD license. See the attached LICENSE file for details.
*/

#include "Nanoshield_ADC.h"

#ifndef __AVR__
#define TWI_FREQ 100000
#else
#include "utility/twi.h"
#endif

// Time it takes to write a register in the I2C bus, in microseconds
//  2 x 4 bytes x 9 bits x bit time
//  Bit time = 1000000 us / I2C frequency
#define I2C_WRITE_REGISTER_TIME (2 * 4 * 10 * 1000000 / TWI_FREQ)

Nanoshield_ADC12::Nanoshield_ADC12(uint8_t i2cAddress) {
  m_i2cAddress = i2cAddress;
  m_bitShift = 4;
  m_gain = GAIN_TWOTHIRDS; /* +/- 6.144V range (limited to VDD +0.3V max!) */
  m_range = 6.144;
  m_spsMask = ADS1015_REG_CONFIG_DR_1600SPS;
  m_nextReadingTime = 0;
  m_continuous = false;
  m_comparator = false;
}

Nanoshield_ADC16::Nanoshield_ADC16(uint8_t i2cAddress) {
  m_i2cAddress = i2cAddress;
  m_bitShift = 0;
  m_gain = GAIN_TWOTHIRDS; /* +/- 6.144V range (limited to VDD +0.3V max!) */
  m_range = 6.144;
  m_spsMask = ADS1115_REG_CONFIG_DR_128SPS;
  m_nextReadingTime = 0;
  m_continuous = false;
  m_comparator = false;
}

void Nanoshield_ADC12::begin() {
  Wire.begin();
}

uint16_t Nanoshield_ADC12::getConfig() {
  // Build default config
  return ADS1015_REG_CONFIG_CPOL_ACTVLOW | // Alert/Rdy active low   (default val)
         ADS1015_REG_CONFIG_CMODE_TRAD   | // Traditional comparator (default val)
         ADS1015_REG_CONFIG_CLAT_NONLAT   | // Latches ALERT/RDY until conversion data is read
         m_spsMask                       | // Samples per second
                                           // Mode: single shot or continuous
         (m_continuous ? ADS1015_REG_CONFIG_MODE_CONTIN : ADS1015_REG_CONFIG_MODE_SINGLE) |
                                           // Mode: comparator or not.
         (m_comparator ? ADS1015_REG_CONFIG_CQUE_1CONV : ADS1015_REG_CONFIG_CQUE_NONE) |
         m_gain;                           // PGA/voltage range
}

uint32_t Nanoshield_ADC12::getNextReadingTime() {
  // Mark the time to read the next sample:
  //  - Continuous mode: current time + time for two conversions + time for I2C communication
  //  - Single-shot mode: current time + time for one conversion + time for I2C communication
  if (m_continuous) {
    return micros() + 2 * 1000000L / getSampleRate() + I2C_WRITE_REGISTER_TIME;
  }
  return micros() + 1000000L / getSampleRate() + I2C_WRITE_REGISTER_TIME;
}

void Nanoshield_ADC12::setGain(Gain_t gain) {
  m_gain = gain;
  
  if (gain) {
    m_range = 4.096 / (1 << ((gain >> 9) - 1));
  } else {
    m_range = 6.144;
  }
}

Gain_t Nanoshield_ADC12::getGain() {
  return m_gain;
}

float Nanoshield_ADC12::getRange() {
  return m_range;
}

void Nanoshield_ADC12::setContinuous(bool c) {
  m_continuous = c;
}

bool Nanoshield_ADC12::isContinuous() {
  return m_continuous;
}

void Nanoshield_ADC12::setSampleRate(uint16_t sps) {
  if (sps >= 3300) {
    m_spsMask = ADS1015_REG_CONFIG_DR_3300SPS;
  } else if (sps >= 2400) {
    m_spsMask = ADS1015_REG_CONFIG_DR_2400SPS;
  } else if (sps >= 1600) {
    m_spsMask = ADS1015_REG_CONFIG_DR_1600SPS;
  } else if (sps >= 920) {
    m_spsMask = ADS1015_REG_CONFIG_DR_920SPS;
  } else if (sps >= 490) {
    m_spsMask = ADS1015_REG_CONFIG_DR_490SPS;
  } else if (sps >= 250) {
    m_spsMask = ADS1015_REG_CONFIG_DR_250SPS;
  } else {
    m_spsMask = ADS1015_REG_CONFIG_DR_128SPS;
  }
}

uint16_t Nanoshield_ADC12::getSampleRate() {
  switch (m_spsMask) {
    case ADS1015_REG_CONFIG_DR_3300SPS:
      return 3300;
    case ADS1015_REG_CONFIG_DR_2400SPS:
      return 2400;
    case ADS1015_REG_CONFIG_DR_1600SPS:
      return 1600;
    case ADS1015_REG_CONFIG_DR_920SPS:
      return 920;
    case ADS1015_REG_CONFIG_DR_490SPS:
      return 490;
    case ADS1015_REG_CONFIG_DR_250SPS:
      return 250;
    default:
      return 128;
  }
}

void Nanoshield_ADC16::setSampleRate(uint16_t sps) {
  if (sps >= 860) {
    m_spsMask = ADS1115_REG_CONFIG_DR_860SPS;
  } else if (sps >= 475) {
    m_spsMask = ADS1115_REG_CONFIG_DR_475SPS;
  } else if (sps >= 250) {
    m_spsMask = ADS1115_REG_CONFIG_DR_250SPS;
  } else if (sps >= 128) {
    m_spsMask = ADS1115_REG_CONFIG_DR_128SPS;
  } else if (sps >= 64) {
    m_spsMask = ADS1115_REG_CONFIG_DR_64SPS;
  } else if (sps >= 32) {
    m_spsMask = ADS1115_REG_CONFIG_DR_32SPS;
  } else if (sps >= 16) {
    m_spsMask = ADS1115_REG_CONFIG_DR_16SPS;
  } else {
    m_spsMask = ADS1115_REG_CONFIG_DR_8SPS;
  }
}

uint16_t Nanoshield_ADC16::getSampleRate() {
  switch (m_spsMask) {
    case ADS1115_REG_CONFIG_DR_860SPS:
      return 860;
    case ADS1115_REG_CONFIG_DR_475SPS:
      return 475;
    case ADS1115_REG_CONFIG_DR_250SPS:
      return 250;
    case ADS1115_REG_CONFIG_DR_128SPS:
      return 128;
    case ADS1115_REG_CONFIG_DR_64SPS:
      return 64;
    case ADS1115_REG_CONFIG_DR_32SPS:
      return 32;
    case ADS1115_REG_CONFIG_DR_16SPS:
      return 16;
    default:
      return 8;
  }
}



int16_t Nanoshield_ADC12::readADC_SingleEnded(uint8_t channel) {
  uint16_t config = getConfig();

  if (channel > 3) {
    return 0;
  }
  
  // Set single-ended input channel
  switch (channel)
  {
    case (0):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_0;
      break;
    case (1):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_1;
      break;
    case (2):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_2;
      break;
    case (3):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_3;
      break;
  }

  // Set 'start single-conversion' bit
  config |= ADS1015_REG_CONFIG_OS_SINGLE;

  // Write config register to the ADC
  writeRegister(m_i2cAddress, ADS1015_REG_POINTER_CONFIG, config);
  
  // Update next reading time
  m_nextReadingTime = getNextReadingTime();
  
  // If in continuous mode, return immediately, otherwise wait for conversion
  return m_continuous ? 0 : readNext();
}

int16_t Nanoshield_ADC12::readADC_Differential_0_1() {
  uint16_t config = getConfig();
                    
  // Set channels
  config |= ADS1015_REG_CONFIG_MUX_DIFF_0_1;          // AIN0 = P, AIN1 = N

  // Set 'start single-conversion' bit
  config |= ADS1015_REG_CONFIG_OS_SINGLE;

  // Write config register to the ADC
  writeRegister(m_i2cAddress, ADS1015_REG_POINTER_CONFIG, config);

  // Update next reading time
  m_nextReadingTime = getNextReadingTime();
  
  // If in continuous mode, return immediately, otherwise wait for conversion
  return m_continuous ? 0 : readNext();
}


int16_t Nanoshield_ADC12::readADC_Differential_2_3() {
  uint16_t config = getConfig();

  // Set channels
  config |= ADS1015_REG_CONFIG_MUX_DIFF_2_3;          // AIN2 = P, AIN3 = N

  // Set 'start single-conversion' bit
  config |= ADS1015_REG_CONFIG_OS_SINGLE;

  // Write config register to the ADC
  writeRegister(m_i2cAddress, ADS1015_REG_POINTER_CONFIG, config);
  
  // Update next reading time
  m_nextReadingTime = getNextReadingTime();
  
  // If in continuous mode, return immediately, otherwise wait for conversion
  return m_continuous ? 0 : readNext();
}

void Nanoshield_ADC12::setComparator(uint8_t channel, int16_t highThreshold, int16_t lowThreshold) {
  startComparator_SingleEnded(channel, highThreshold, lowThreshold);
}

void Nanoshield_ADC12::setNotComparator() {
  m_comparator = false;
}

bool Nanoshield_ADC12::isComparator() {
  return m_comparator;
}

void Nanoshield_ADC12::startComparator_SingleEnded(uint8_t channel, int16_t highThreshold, int16_t lowThreshold) {
  // Comparator must be used in continuous mode
  m_comparator = true;
  m_continuous = true;

  uint16_t config = getConfig();
                    
  // Set single-ended input channel
  switch (channel)
  {
    case (0):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_0;
      break;
    case (1):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_1;
      break;
    case (2):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_2;
      break;
    case (3):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_3;
      break;
  }

  // Set the high threshold register
  // Shift 12-bit results left 4 bits for the ADS1015
  writeRegister(m_i2cAddress, ADS1015_REG_POINTER_HITHRESH, highThreshold << m_bitShift);

  // Set the low threshold register
  // Shift 12-bit results left 4 bits for the ADS1015
  writeRegister(m_i2cAddress, ADS1015_REG_POINTER_LOWTHRESH, lowThreshold << m_bitShift);  

  // Write config register to the ADC
  writeRegister(m_i2cAddress, ADS1015_REG_POINTER_CONFIG, config);

  // Update next reading time
  m_nextReadingTime = getNextReadingTime();
}

int16_t Nanoshield_ADC12::getLastConversionResults() {
  return readNext();
}

int16_t Nanoshield_ADC12::readNext() {
  // Wait until end of conversion
  while (!conversionDone());

  // Mark the time to read the next sample
  m_nextReadingTime += 1000000L / getSampleRate();

  // Read the conversion results
  uint16_t res = readRegister(m_i2cAddress, ADS1015_REG_POINTER_CONVERT) >> m_bitShift;
  if (m_bitShift == 0)
  {
    return (int16_t)res;
  }
  else
  {
    // Shift 12-bit results right 4 bits for the ADS1015,
    // making sure we keep the sign bit intact
    if (res > 0x07FF)
    {
      // negative number - extend the sign to 16th bit
      res |= 0xF000;
    }
    return (int16_t)res;
  }
}

bool Nanoshield_ADC12::conversionDone() {
  return micros() >= m_nextReadingTime;
}

void Nanoshield_ADC12::writeRegister(uint8_t i2cAddress, uint8_t reg, uint16_t value) {
  Wire.beginTransmission(i2cAddress);
#ifdef ARDUPI
  char buf[3];
  buf[0] = reg;
  buf[1] = value >> 8;
  buf[2] = value & 0xFF;
  Wire.write(buf,3);
#else
  Wire.write((uint8_t)reg);
  Wire.write((uint8_t)(value>>8));
  Wire.write((uint8_t)(value & 0xFF));
#endif
  Wire.endTransmission();  
}

uint16_t Nanoshield_ADC12::readRegister(uint8_t i2cAddress, uint8_t reg) {
  Wire.beginTransmission(i2cAddress);
  Wire.write(ADS1015_REG_POINTER_CONVERT);
  Wire.endTransmission();
  
  Wire.requestFrom(i2cAddress,(uint8_t)2);
#ifdef ARDUPI
  unsigned char *ret;
  ret = (unsigned char *)malloc(sizeof(char)*2);
  *ret = Wire.read((int)2); //read 2 bytes
  uint16_t aux = ret[0] << 8 | ret[1];
  return (uint16_t)aux;
#else
  return (Wire.read() << 8 | Wire.read());
#endif
}

float Nanoshield_ADC12::readVoltage(uint8_t channel) {
  return (m_continuous ? readNext() : readADC_SingleEnded(channel)) * m_range / 2047;
}

float Nanoshield_ADC12::readDifferentialVoltage01() {
  return (m_continuous ? readNext() : readADC_Differential_0_1()) * m_range / 2047;
}

float Nanoshield_ADC12::readDifferentialVoltage23() {
  return (m_continuous ? readNext() : readADC_Differential_2_3()) * m_range / 2047;
}

float Nanoshield_ADC12::read4to20mA(uint8_t channel) {
  return (m_continuous ? readNext() : 1000 * readVoltage(channel)) / 100;
}

float Nanoshield_ADC16::readVoltage(uint8_t channel) {
  return (m_continuous ? readNext() : readADC_SingleEnded(channel)) * m_range / 32767;
}

float Nanoshield_ADC16::readDifferentialVoltage01() {
  return (m_continuous ? readNext() : readADC_Differential_0_1()) * m_range / 32767;
}

float Nanoshield_ADC16::readDifferentialVoltage23() {
  return (m_continuous ? readNext() : readADC_Differential_2_3()) * m_range / 32767;
}
