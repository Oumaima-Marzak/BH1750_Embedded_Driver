





#include "bh1750.h"
#include "bh1750_i2c_interface.h"


static uint8_t bh1750_addr = BH1750_ADDR_LOW;
static uint8_t bh1750_mode = BH1750_CONT_H_RES_MODE;

BH1750_Status_t BH1750_init(uint8_t addr)
{
    if(BH1750_powerOn()!= BH1750_OK)
        return BH1750_POWER_ON_ERROR;

    if(BH1750_reset()!= BH1750_OK)
        return BH1750_RESET_ERROR;

    if(BH1750_set_mode(bh1750_mode)!= BH1750_OK)
        return BH1750_SET_MODE_ERROR;

    return BH1750_OK;
}

BH1750_Status_t BH1750_powerOn(void)
{
    uint8_t command = BH1750_POWER_ON;

    if(I2C_write_bytes(bh1750_addr, &command, 1) != I2C_OK)
        return BH1750_POWER_ON_ERROR;
    
    return BH1750_OK;
}

BH1750_Status_t BH1750_powerDown(void)
{
    uint8_t command = BH1750_POWER_DOWN;

    if(I2C_write_bytes(bh1750_addr, &command, 1) != I2C_OK)
        return BH1750_POWER_DOWN_ERROR;
    
    return BH1750_OK;
}

BH1750_Status_t BH1750_reset(void)
{
    uint8_t command = BH1750_RESET;

    if(I2C_write_bytes(bh1750_addr, &command, 1) != I2C_OK)
        return BH1750_RESET_ERROR;
    
    return BH1750_OK;
}

BH1750_Status_t BH1750_set_mode(uint8_t mode)
{
    bh1750_mode = mode;

    if(I2C_write_bytes(bh1750_addr, &mode, 1) != I2C_OK)
        return BH1750_SET_MODE_ERROR;
    
    return BH1750_OK;
}

BH1750_Status_t BH1750_read_lux(uint16_t *lux) 
{
    uint8_t data[2];

    if (I2C_read_bytes(bh1750_addr, data, 2) != I2C_OK) 
        return BH1750_READ_LUX_ERROR;

    uint16_t raw = ((uint16_t)data[0] << 8) | data[1];

    // Convert 16-bit raw sensor data to Lux using datasheet factor (1 lx = raw / 1.2)
    *lux = (uint16_t)((float)raw )/ 1.2f;

    return BH1750_OK;
}

