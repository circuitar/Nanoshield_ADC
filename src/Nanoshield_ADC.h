/**
 * @file Nanoshield_ADC.h
 * 
 * This is the library to use the ADC Nanoshield.
 * 
 * This library is based on the Adafruit_ADS1X15 library from Adafruit (https://github.com/adafruit/Adafruit_ADS1X15).
 * 
 * Original work Copyright (c) 2012, Adafruit Industries
 * Modified work Copyright (c) 2014 Circuitar
 * All rights reserved.
 * 
 * This software is released under a BSD license. See the attached LICENSE file for details.
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

/**
 * Possible gain values.
 * 
 * Voltages over the gain limit will saturate the conversion (i.e. converted 
 * value will be the same of the gain limit).
 * Never use input voltages greater than 5V.
 */
typedef enum {
  GAIN_TWOTHIRDS    = ADS1015_REG_CONFIG_PGA_6_144V, /// Reads voltages up to 6.144V.
  GAIN_ONE          = ADS1015_REG_CONFIG_PGA_4_096V, /// Reads voltages up to 4.096V.
  GAIN_TWO          = ADS1015_REG_CONFIG_PGA_2_048V, /// Reads voltages up to 2.048V.
  GAIN_FOUR         = ADS1015_REG_CONFIG_PGA_1_024V, /// Reads voltages up to 1.024V.
  GAIN_EIGHT        = ADS1015_REG_CONFIG_PGA_0_512V, /// Reads voltages up to 0.512V.
  GAIN_SIXTEEN      = ADS1015_REG_CONFIG_PGA_0_256V  /// Reads voltages up to 0.256V.
} Gain_t;

class Nanoshield_ADC {
  public:
    /**
     * @brief Constructor
     * 
     * Instantiates an object to control the ADC Nanoshield converter.
     * 
     * @param i2cAddress The nanoshield I2C address on the bus.
     * 
     * @see begin()
     */
    Nanoshield_ADC(uint8_t i2cAddress = ADS1X15_ADDRESS);

    /**
     * @brief Initializes the module.
     */
    void begin();

    /**
     * @brief Read an ADC Nanoshield register.
     * 
     * @param i2cAddress I2C address of the ADC Nanoshield.
     * @param reg Register address to read.
     * 
     * @return The value of the addressed register.
     */
    uint16_t readRegister(uint8_t, uint8_t);

    /**
     * @brief Writes to Nanoshield ADC config register.
     * 
     * @param i2cAddress I2C address of the Nanoshield ADC.
     * @param reg Config register address to write.
     * @param value Value to write.
     */
    void writeRegister(uint8_t, uint8_t, uint16_t);

    /**
     * @brief Checks if there is data available to read.
     * 
     * @return True if no conversion is being done and the value is ready to be
     *         read. Otherwise, false.
     */
    bool conversionDone();

    /**
     * @brief Reads the binary voltage requested when it is ready.
     * 
     * To use when in continuous mode. Same as readNext().
     * 
     * @return The binary voltage representation.
     * 
     * @see readNext()
     */
    int16_t getLastConversionResults();

    /**
     * @brief Reads the binary voltage requested when it is ready.
     * 
     * To use when in continuous mode.
     * 
     * @return The binary voltage representation.
     */
    int16_t readNext();

    /**
     * @brief Reads channel binary voltage.
     * 
     * @param  channel Channel to read. Must be in 0, 1, 2 or 3.
     * @return Binary representation of the voltage in the channel.
     */
    int16_t readADC_SingleEnded(uint8_t);

    /**
     * @brief Reads differential voltage in binary mode between channels 0(+) 
     *        and 1(-).
     * 
     * Reads 16 or 12 bits representation of the difference between the voltage
     * in channels 0(+) and 1(-).
     * 
     * @return Binary representation of the differential voltage.
     */
    int16_t readADC_Differential_0_1();

    /**
     * @brief Reads differential voltage in binary mode between channels 2(+) 
     *        and 3(-).
     * 
     * Reads 16 or 12 bits representation of the difference between the voltage
     * in channels 2(+) and 3(-).
     * 
     * @return Binary representation of the differential voltage.
     */
    int16_t readADC_Differential_2_3();

    /**
     * @brief Sets the Nanoshield ADC in comparator mode.
     * 
     * In comparator mode, the Nanoshield sets the ALERT/RDY pin to LOW
     * when the voltage read exceed a high threshold. This pin is set to HIGH
     * again when the voltage read falls below a low threshold. The ALERT/RDY
     * pin is connected to arduino D3 pin.
     * 
     * @param channel The channel to compare.
     * @param highThreshold The high threshold.
     * @param lowThreshold The low threshold.
     */
    void setComparator(uint8_t, int16_t, int16_t);

    /**
     * @brief Turns comparator mode off.
     * 
     * Note that comparator mode needs the continuous mode. So when comparator
     * mode is unset, continuous mode still set. Unset continuous mode too if
     * necessary.
     * 
     * @see setContinuous()
     */
    void setNotComparator();

    /**
     * @brief Checks if in comparator mode.
     * @return True if comparator mode is active. False if not.
     */
    bool isComparator();

    /**
     * @brief Sets the high threshold value to comparator mode.
     * 
     * The ADS1115 has a interrupt signal connected to arduino ALERT/RDY pin
     * (D3) to notify voltages over a high threshold. To use this feature, the
     * alert jumper on arduino must be closed and a interrupt handler must be
     * set with attachinterrupt(6, <interruptHandler>, LOW), where 
     * <interruptHandler> is the function to be called on interrupt signal.
     * 
     * @param channel The channel to keep track of value. Must be in 0, 1, 2 or 3.
     * @param highThreshold The high threshold set ALERT/RDY pin LOW.
     * @param lowThreshold The low threshold to set ALERT/RDY pin HIGH.
     */
    void startComparator_SingleEnded(uint8_t, int16_t, int16_t);

    /**
     * @brief Sets the library to work on continuous mode.
     * 
     * In continuous mode, the library will reads the voltage value based on a
     * sample rate. For example, if reading at 860Hz, then 860 measures will be
     * done in a second.
     * 
     * @param c True to activate continuous mode, false to deactivate 
     *          continuous mode.
     * 
     * @see setSampleRate()
     * @see getSampleRate()
     * @see readNext()
     * @see conversionDone()
     */
    void setContinuous(bool c);

    /**
     * @brief Checks if in continuous mode.
     * 
     * @return Ture if in continuous mode, false if not.
     */
    bool isContinuous();

    /**
     * @brief Sets the input gain.
     * 
     * The input gain is used to adjust the converter resolution to the signal
     * magnitude. Greater gains adjusts lower voltages over the resolution.
     * 
     * @param gain A available gain from the Gain_t enumerator.
     * 
     * @see Gain_t
     */
    void setGain(Gain_t);

    /**
     * @brief Gets the gain set on the Nanoshield ADC.
     * 
     * @return A value from Gain_t enumerator.
     * 
     * @see Gain_t
     * @see setGain()
     */
    Gain_t getGain();

    /**
     * @brief [brief description]
     * @details [long description]
     * @return [description]
     */
    float getRange();

    /**
     * @brief Sets the conversor sample rate on continuous mode
     * 
     * @param sps Sample rate. Possible values are:
     *            - If using Nanoshield_ADC12 (12 bits): 128, 250, 490, 920, 1600, 2400, 3300
     *            - If using Nanoshield_ADC (16 bits): 8, 16, 32, 64, 128, 250, 475, 860
     *            If no one of the above, the closest lower value will be selected.
     *            
     * @see setContiuous()
     */
    virtual void setSampleRate(uint16_t sps = 128);

    /**
     * @brief Gets actual Nanoshield_ADC sample rate.
     *
     * @return Actual sample rate set.
     */
    virtual uint16_t getSampleRate();

    /**
     * @brief Reads channel current from 4mA to 20mA.
     * 
     * @param  channel Channel to read. Must be one of 0, 1, 2 or 3.
     * @return The current on channel from 4mA to 20mA.
     */
    float read4to20mA(uint8_t);

    /**
     * @brief Reads channel voltage.
     * 
     * @param  channel Channel to read. Must be one of 0, 1, 2 or 3.
     * @return The voltage read up to 5V.
     */
    float readVoltage(uint8_t);

    /**
     * @brief Reads voltage in differential mode between channels 0(+) and 1(-).
     * 
     * Reads the difference between voltages in channel 0(+) and 1(-). For
     * example, if the voltage in both channels is the same, then the 
     * differential voltage is zero. Notice that the voltage margin in channels
     * still 0V to 5V in relation to GND.
     * 
     * @return The difference between the voltages in channel 0(+) and 1(-).
     */
    float readDifferentialVoltage01();

    /**
     * @brief Reads voltage in differential mode between channels 2(+) and 3(-).
     * 
     * Reads the difference between voltages in channel 2(+) and 3(-). For
     * example, if the voltage in both channels is the same, then the 
     * differential voltage is zero. Notice that the voltage margin in channels
     * still 0V to 5V in relation to GND.
     * 
     * @return The difference between the voltages in channel 2(+) and 3(-).
     */
    float readDifferentialVoltage23();

  private:
    uint8_t m_i2cAddress;
    Gain_t m_gain;
    float m_range;
    uint16_t m_spsMask;
    uint32_t m_nextReadingTime;
    bool m_continuous;
    bool m_comparator;
    uint16_t getConfig();
    uint32_t getNextReadingTime();
};

#endif
