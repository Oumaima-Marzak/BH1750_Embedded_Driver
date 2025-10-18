/**
 * @author Oumaima Marzak
 * @date Oct 2025
 * @file bh1750.h
 * @brief Driver for BH1750 digital ambient light sensor (I²C)
 *
 * Provides initialization, power control, mode setting, and lux reading
 * functions for the BH1750 light intensity sensor.
 *
 * The sensor outputs direct lux values over I²C, no calibration required.
 */

#ifndef BH1750_H
#define BH1750_H

#include <stdint.h>

/* =========================================================================
 *  I2C Addresses
 * =========================================================================
 *  The BH1750 address depends on the ADDR pin:
 *  - Floating or LOW → 0x23
 *  - HIGH → 0x5C
 */
#define BH1750_ADDR_LOW   0x23
#define BH1750_ADDR_HIGH  0x5C


/* =========================================================================
 *  Command Set (from datasheet)
 * =========================================================================
 */
#define BH1750_POWER_DOWN               0x00    //No active state.
#define BH1750_POWER_ON                 0x01    //Waiting for measurement command.
#define BH1750_RESET                    0x07    //Reset data register value. Not acceptable in Power Down Mode

#define BH1750_CONT_H_RES_MODE          0x10    // Continuous measurement, 1lx resolution, 120ms typical time
#define BH1750_CONT_H_RES_MODE_2        0x11    // Continuous measurement, 0.5lx resolution, 120ms typical time

#define BH1750_CONT_L_RES_MODE          0x13    // Continuous measurement, 4lx resolution, 16ms typical time

#define BH1750_ONE_TIME_H_RES_MODE      0x20    // One time measurement, 1lx resolution, 120ms typical time
#define BH1750_ONE_TIME_H_RES_MODE_2    0x21    // One time measurement, 0.5lx resolution, 120ms typical time

#define BH1750_ONE_TIME_L_RES_MODE      0x23    // One time measurement, 4lx resolution, 16ms typical time

/* Change Measurement Time Commands */
#define BH1750_CHANGE_MEAS_TIME_HIGH(b7,b6,b5)       (0x40 | (b7 << 2) | (b6 << 1) | b5)
#define BH1750_CHANGE_MEAS_TIME_LOW(b4,b3,b2,b1,b0)  (0x60 | (b4 << 4) | (b3 << 3) | (b2 << 2) | (b1 << 1) | b0)

/**
 * @brief BH1750 driver status codes
 */
typedef enum 
{
    BH1750_OK,
    BH1750_POWER_ON_ERROR,
    BH1750_POWER_DOWN_ERROR,
    BH1750_RESET_ERROR,
    BH1750_SET_MODE_ERROR,
    BH1750_READ_LUX_ERROR

} BH1750_Status_t;

/* =========================================================================
 *  Function Prototypes
 * =========================================================================
 */

/**
 * @brief Initialize BH1750 sensor and set default mode.
 * @param addr  I²C address (BH1750_ADDR_LOW or BH1750_ADDR_HIGH)
 * @return Status of initialization
 */
BH1750_Status_t BH1750_init(uint8_t addr);

/**
 * @brief Power on the BH1750 (exit power-down state).
 */
BH1750_Status_t BH1750_powerOn(void);

/**
 * @brief Power down the BH1750 (low-power mode).
 */
BH1750_Status_t BH1750_powerDown(void);

/**
 * @brief Reset internal data register (only when powered on).
 */
BH1750_Status_t BH1750_reset(void);

/**
 * @brief Set the measurement mode (continuous or one-time).
 * @param mode  One of BH1750_CONT_* or BH1750_ONE_TIME_* constants
 */
BH1750_Status_t BH1750_set_mode(uint8_t mode);

/**
 * @brief Read current light intensity from the sensor.
 * @param lux Pointer to store the measured lux value.
 */
BH1750_Status_t BH1750_read_lux(uint16_t *lux);



#endif
