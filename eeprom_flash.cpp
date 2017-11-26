#include "mbed.h"
#include "eeprom_flash.h"

void _FLASH_PageErase(uint32_t PageAddress)
{
    /* Proceed to erase the page */
    SET_BIT(FLASH->CR, FLASH_CR_PER);
    while (FLASH->SR & FLASH_SR_BSY);
    WRITE_REG(FLASH->AR, PageAddress);
    SET_BIT(FLASH->CR, FLASH_CR_STRT);
    while (FLASH->SR & FLASH_SR_BSY);
    CLEAR_BIT(FLASH->CR, FLASH_CR_PER);
}

/*
 * Must call this first to enable writing
 */
void enableEEPROMWriting() {
    HAL_FLASH_Unlock();
    _FLASH_PageErase(EEPROM_START_ADDRESS);
}

void disableEEPROMWriting() {
    HAL_FLASH_Lock();
}

/*
 * Writing functions
 * Must call enableEEPROMWriting() first
 */
HAL_StatusTypeDef writeEEPROMHalfWord(uint32_t address, uint16_t data) {
    HAL_StatusTypeDef status;
    address = address + EEPROM_START_ADDRESS;
    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address, data);
    return status;
}

HAL_StatusTypeDef writeEEPROMWord(uint32_t address, uint32_t data) {
    HAL_StatusTypeDef status;
    address = address + EEPROM_START_ADDRESS;
    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, data);
    return status;
}

/*
 * Reading functions
 */
uint16_t readEEPROMHalfWord(uint32_t address) {
    uint16_t val = 0;
    address = address + EEPROM_START_ADDRESS;
    val = *(__IO uint16_t*)address;
    return val;
}

uint32_t readEEPROMWord(uint32_t address) {
    uint32_t val = 0;
    address = address + EEPROM_START_ADDRESS;
    val = *(__IO uint32_t*)address;
    return val;
}
