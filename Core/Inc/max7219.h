#ifndef __MAX7219
#define __MAX7219

#include "stm32l0xx_hal.h"


#define MAX7219_NUMBER 2
#define MAX7219_ADRR_DIGIT(d) ((d+1)<<8)
#define MAX7219_ADRR_DECODE_MODE 0x0900
#define MAX7219_ADRR_INTENSITY 0x0a00
#define MAX7219_ADRR_SCAN_LIMIT 0x0b00
#define MAX7219_ADRR_SHUTDOWN 0x0C00
#define MAX7219_ADRR_DISPLAY_TEST 0x0f00

#define MAX7219_PIN_DIN 
#define MAX7219_PORT_DIN

#define MAX7219_PIN_CS
#define MAX7219_PORT_CS

#define MAX7219_PIN_CLK
#define MAX7219_PORT_CLK


void setDinPin(GPIO_TypeDef *port,uint16_t pin);
void setCSPin(GPIO_TypeDef *port,uint16_t pin);
void setCLKPin(GPIO_TypeDef *port,uint16_t pin);


void MAX7219_Init(void);
void set_all_register(uint16_t);
void set_single_register(uint8_t,uint16_t);
void clear(void);
void shiftOut(uint16_t);

void shutdown(_Bool enable);
void displayTest(_Bool enable);
void setDecodeMode(uint8_t decode);
void setIntensity(uint8_t intensity);
void setScanLimit(uint8_t limit);
void setDigit(uint8_t index,uint8_t digit,uint8_t data);

void pullCSDown(void);
void pullCSUp(void);
#endif