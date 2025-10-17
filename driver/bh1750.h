#ifndef BH1750_H
#define BH1750_H

#include <stdint.h>

/* BH1750 Addresses */
#define BH1750_ADDR_LOW   0x23
#define BH1750_ADDR_HIGH  0x5C


/* BH1750 Commands */ 
#define BH1750_POWER_DOWN               0x00    //No active state.
#define BH1750_POWER_ON                 0x01    //Waiting for measurement command.
#define BH1750_RESET                    0x07    //Reset data register value. Not acceptable in Power Down Mode

#define BH1750_CONT_H_RES_MODE          0x10    // Continuous measurement, 1lx resolution, 120ms typical time
#define BH1750_CONT_H_RES_MODE_2        0x11    // Continuous measurement, 0.5lx resolution, 120ms typical time

#define BH1750_CONT_L_RES_MODE          0x13    // Continuous measurement, 4lx resolution, 16ms typical time

#define BH1750_ONE_TIME_H_RES_MODE      0x20    // One time measurement, 1lx resolution, 120ms typical time
#define BH1750_ONE_TIME_H_RES_MODE_2    0x21    // One time measurement, 0.5lx resolution, 120ms typical time

#define BH1750_ONE_TIME_L_RES_MODE      0x23    // One time measurement, 4lx resolution, 16ms typical time

#define BH1750_CHANGE_MEAS_TIME_HIGH(b7,b6,b5)       (0x40 | (b7 << 2) | (b6 << 1) | b5)
#define BH1750_CHANGE_MEAS_TIME_LOW(b4,b3,b2,b1,b0)  (0x60 | (b4 << 4) | (b3 << 3) | (b2 << 2) | (b1 << 1) | b0)


typedef enum 
{
    BH1750_OK,
    BH1750_ERROR

} BH1750_Status_t;


BH1750_Status_t BH1750_init(uint8_t addr);

BH1750_Status_t BH1750_powerOn(void);

BH1750_Status_t BH1750_powerDown(void);

BH1750_Status_t BH1750_reset(void);

BH1750_Status_t BH1750_set_mode(uint8_t mode);

/*
 * BH1750_ReadLux
 * ----------------------------
 * Reads light level in lux from BH1750.
 *
 * Returns lux value as 16-bit integer.
 */
BH1750_Status_t BH1750_read_lux(float *lux);



#endif
