/*!
 * @file Adafruit_INA219.cpp
 *
 * @mainpage Adafruit INA219 current/power monitor IC
 *
 * @section intro_sec Introduction
 *
 *  Driver for the INA219 current sensor
 *
 *  This is a library for the Adafruit INA219 breakout
 *  ----> https://www.adafruit.com/products/904
 *
 *  Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing
 *  products from Adafruit!
 *
 * @section author Author
 *
 * Written by Kevin "KTOWN" Townsend for Adafruit Industries.
 *
 * @section license License
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */

#include "Adafruit_INA219.h"
#include <iostream>

/**************************************************************************/
/*!
    @brief  Sends a single command byte over I2C
*/
/**************************************************************************/
void Adafruit_INA219::wireWriteRegister(uint8_t reg, uint16_t value)
{

    /* if(_i2c->Write(reg,(value >> 8) & 0xFF)){
        std::cout<<"i2c MSBy write error \n";
    }       // Upper 8-bits
    else{
        std::cout<<"i2c MSBy write success \n";
    }
    if(_i2c->Write(reg,value & 0xFF)){
        std::cout<<"i2c LSBy write error \n";
    } 
    else{
        std::cout<<"i2c LSBy write success \n";
    }             // Lower 8-bits

    */

    //go lower level. The write method DOES NOT WORK
    uint8_t data[3];
    data[0] = reg;
    data[1] = (value >> 8) & 0xFF;
    data[2] = (value & 0xFF);
    uint8_t received[2];
    this->_i2c->Transaction(data, 3, received, 2);
    //debug:
    std::cout << std::hex << ((received[0] << 8) | received[1]) << '\n';
}

/**************************************************************************/
/*!
    @brief  Reads a 16 bit values over I2C
*/
/**************************************************************************/
void Adafruit_INA219::wireReadRegister(uint8_t reg, uint16_t *value)
{
    uint8_t buffer[2];
    this->_i2c->Read(reg, 2, buffer); // Register
    //stitch back the 2 bytes
    *value = (buffer[0] << 8) | buffer[1];
}

/**************************************************************************/
/*!
    @brief set device to alibration which uses the highest precision for
      current measurement (0.1mA), at the expense of
      only supporting 16V at 400mA max.
*/
/**************************************************************************/
void Adafruit_INA219::setCalibration_16V_400mA(void)
{

    // Calibration which uses the highest precision for
    // current measurement (0.1mA), at the expense of
    // only supporting 16V at 400mA max.

    // VBUS_MAX = 16V
    // VSHUNT_MAX = 0.04          (Assumes Gain 1, 40mV)
    // RSHUNT = 0.1               (Resistor value in ohms)

    // 1. Determine max possible current
    // MaxPossible_I = VSHUNT_MAX / RSHUNT
    // MaxPossible_I = 0.4A

    // 2. Determine max expected current
    // MaxExpected_I = 0.4A

    // 3. Calculate possible range of LSBs (Min = 15-bit, Max = 12-bit)
    // MinimumLSB = MaxExpected_I/32767
    // MinimumLSB = 0.0000122              (12uA per bit)
    // MaximumLSB = MaxExpected_I/4096
    // MaximumLSB = 0.0000977              (98uA per bit)

    // 4. Choose an LSB between the min and max values
    //    (Preferrably a roundish number close to MinLSB)
    // CurrentLSB = 0.00005 (50uA per bit)

    // 5. Compute the calibration register
    // Cal = trunc (0.04096 / (Current_LSB * RSHUNT))
    // Cal = 8192 (0x2000)

    ina219_calValue = 0x2000;

    // 6. Calculate the power LSB
    // PowerLSB = 20 * CurrentLSB
    // PowerLSB = 0.001 (1mW per bit)

    // 7. Compute the maximum current and shunt voltage values before overflow
    //
    // Max_Current = Current_LSB * 32767
    // Max_Current = 1.63835A before overflow
    //
    // If Max_Current > Max_Possible_I then
    //    Max_Current_Before_Overflow = MaxPossible_I
    // Else
    //    Max_Current_Before_Overflow = Max_Current
    // End If
    //
    // Max_Current_Before_Overflow = MaxPossible_I
    // Max_Current_Before_Overflow = 0.4
    //
    // Max_ShuntVoltage = Max_Current_Before_Overflow * RSHUNT
    // Max_ShuntVoltage = 0.04V
    //
    // If Max_ShuntVoltage >= VSHUNT_MAX
    //    Max_ShuntVoltage_Before_Overflow = VSHUNT_MAX
    // Else
    //    Max_ShuntVoltage_Before_Overflow = Max_ShuntVoltage
    // End If
    //
    // Max_ShuntVoltage_Before_Overflow = VSHUNT_MAX
    // Max_ShuntVoltage_Before_Overflow = 0.04V

    // 8. Compute the Maximum Power
    // MaximumPower = Max_Current_Before_Overflow * VBUS_MAX
    // MaximumPower = 0.4 * 16V
    // MaximumPower = 6.4W

    // Set multipliers to convert raw current/power values
    ina219_currentDivider_mA = 20;    // Current LSB = 50uA per bit (1000/50 = 20)
    ina219_powerMultiplier_mW = 1.0f; // Power LSB = 1mW per bit

    // Set Calibration register to 'Cal' calculated above
    wireWriteRegister(INA219_REG_CALIBRATION, ina219_calValue);

    // Set Config register to take into account the settings above
    uint16_t config = INA219_CONFIG_BVOLTAGERANGE_16V |
                      INA219_CONFIG_GAIN_1_40MV |
                      INA219_CONFIG_BADCRES_12BIT |
                      INA219_CONFIG_SADCRES_12BIT_1S_532US |
                      INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;
    wireWriteRegister(INA219_REG_CONFIG, config);
}

/**************************************************************************/
/*!
    @brief  Instantiates a new INA219 class
    @param addr the I2C address the device can be found on. Default is 0x40
*/
/**************************************************************************/
Adafruit_INA219::Adafruit_INA219(frc::I2C::Port port, uint8_t addr)
{
    this->ina219_i2caddr = addr;
    this->_i2c = new frc::I2C(port, addr);
    this->ina219_currentDivider_mA = 0;
    this->ina219_powerMultiplier_mW = 0.0f;

    setCalibration_16V_400mA();
}

/**************************************************************************/
/*!
    @brief  Gets the raw bus voltage (16-bit signed integer, so +-32767)
    @return the raw bus voltage reading
*/
/**************************************************************************/
int16_t Adafruit_INA219::getBusVoltage_raw()
{
    uint16_t value;
    wireReadRegister(INA219_REG_BUSVOLTAGE, &value);

    // Shift to the right 3 to drop CNVR and OVF and multiply by LSB
    return (int16_t)((value >> 3) * 4);
}

/**************************************************************************/
/*!
    @brief  Gets the raw shunt voltage (16-bit signed integer, so +-32767)
    @return the raw shunt voltage reading
*/
/**************************************************************************/
int16_t Adafruit_INA219::getShuntVoltage_raw()
{
    uint16_t value;
    wireReadRegister(INA219_REG_SHUNTVOLTAGE, &value);
    return (int16_t)value;
}

/**************************************************************************/
/*!
    @brief  Gets the raw current value (16-bit signed integer, so +-32767)
    @return the raw current reading
*/
/**************************************************************************/
int16_t Adafruit_INA219::getCurrent_raw()
{
    uint16_t value;

    // Sometimes a sharp load will reset the INA219, which will
    // reset the cal register, meaning CURRENT and POWER will
    // not be available ... avoid this by always setting a cal
    // value even if it's an unfortunate extra step
    wireWriteRegister(INA219_REG_CALIBRATION, ina219_calValue);

    // Now we can safely read the CURRENT register!
    wireReadRegister(INA219_REG_CURRENT, &value);

    return (int16_t)value;
}

/**************************************************************************/
/*!
    @brief  Gets the raw power value (16-bit signed integer, so +-32767)
    @return raw power reading
*/
/**************************************************************************/
int16_t Adafruit_INA219::getPower_raw()
{
    uint16_t value;

    // Sometimes a sharp load will reset the INA219, which will
    // reset the cal register, meaning CURRENT and POWER will
    // not be available ... avoid this by always setting a cal
    // value even if it's an unfortunate extra step
    wireWriteRegister(INA219_REG_CALIBRATION, ina219_calValue);

    // Now we can safely read the POWER register!
    wireReadRegister(INA219_REG_POWER, &value);

    return (int16_t)value;
}

/**************************************************************************/
/*!
    @brief  Gets the shunt voltage in mV (so +-327mV)
    @return the shunt voltage converted to millivolts
*/
/**************************************************************************/
double Adafruit_INA219::getShuntVoltage_mV()
{
    int16_t value;
    value = getShuntVoltage_raw();
    return value * 0.01;
}

/**************************************************************************/
/*!
    @brief  Gets the shunt voltage in volts
    @return the bus voltage converted to volts
*/
/**************************************************************************/
double Adafruit_INA219::getBusVoltage_V()
{
    int16_t value = getBusVoltage_raw();
    return value * 0.001;
}

/**************************************************************************/
/*!
    @brief  Gets the current value in mA, taking into account the
            config settings and current LSB
    @return the current reading convereted to milliamps
*/
/**************************************************************************/
double Adafruit_INA219::getCurrent_mA()
{
    double valueDec = getCurrent_raw();
    valueDec /= ina219_currentDivider_mA;
    return valueDec;
}

/**************************************************************************/
/*!
    @brief  Gets the power value in mW, taking into account the
            config settings and current LSB
    @return power reading converted to milliwatts
*/
/**************************************************************************/
double Adafruit_INA219::getPower_mW()
{
    double valueDec = getPower_raw();
    valueDec *= ina219_powerMultiplier_mW;
    return valueDec;
}
