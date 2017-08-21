#ifndef __FLASH_H__
#define __FLASH_H__

#define FLASH_ADDR_START        (FLASH_DATA_EEPROM_START_PHYSICAL_ADDRESS + ((uint16_t)BLOCK_OPERATION * (uint16_t)FLASH_BLOCK_SIZE))
#define FLASH_ADDR_SIZE         256 //((uint16_t)FLASH_BLOCK_SIZE)
#define FLASH_ADDR_END          (FLASH_ADDR_START + FLASH_ADDR_SIZE)

#define FLASH_DATA_END          FLASH_PROGRAM_END_PHYSICAL_ADDRESS

extern int fw_flash_init();
extern char fw_flash_readByte(unsigned long addr);
extern void fw_flash_writeByte(unsigned long addr, char b);
extern unsigned int fw_flash_read(unsigned long addr, char *buf, unsigned int size);
extern unsigned int fw_flash_write(unsigned long addr, char *buf, unsigned int size);
extern void fw_flash_erase(unsigned long addr, char ch, unsigned int size);

#endif
