#ifndef BH1750_I2C_INTERFACE_H_
#define BH1750_I2C_INTERFACE_H_

#include <stdint.h>

typedef enum {
    I2C_OK,
    I2C_ERROR
} I2C_Status_t;


I2C_Status_t I2C_init(void);

I2C_Status_t I2C_write_bytes(uint8_t addr, uint8_t *data, uint8_t len);

I2C_Status_t I2C_read_bytes(uint8_t addr, uint8_t *data, uint8_t len);



#endif
