#ifndef __I2C_H__
#define __I2C_H__

extern void bsp_i2c_init();
extern uint8_t bsp_i2c_BytesRead(uint8_t devAddr, uint8_t addr, uint8_t* buffer, uint8_t size);
extern void bsp_i2c_ByteRead(uint8_t devAddr, uint8_t addr, uint8_t *ch);
extern uint8_t bsp_i2c_BytesWrite(uint8_t devAddr, uint8_t addr, uint8_t *buffer, uint8_t size);
extern uint8_t bsp_i2c_ByteWrite(uint8_t devAddr, uint8_t addr, uint8_t ch);

#endif
