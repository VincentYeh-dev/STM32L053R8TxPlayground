#include "max7219.h"

GPIO_TypeDef *port_din;
uint16_t pin_din;

GPIO_TypeDef *port_cs;
uint16_t pin_cs;

GPIO_TypeDef *port_clk;
uint16_t pin_clk;

void setDinPin(GPIO_TypeDef *port,uint16_t pin){
	port_din=port;
	pin_din=pin;
}

void setCSPin(GPIO_TypeDef *port,uint16_t pin){
	port_cs=port;
	pin_cs=pin;
}

void setCLKPin(GPIO_TypeDef *port,uint16_t pin){
	port_clk=port;
	pin_clk=pin;
}

void MAX7219_Init(void)
{	
	HAL_GPIO_WritePin(port_din,pin_din,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(port_cs,pin_cs,GPIO_PIN_SET);
	HAL_GPIO_WritePin(port_clk,pin_clk,GPIO_PIN_RESET);
	
	
	displayTest(1);
	HAL_Delay(200);
	displayTest(0);
	
  shutdown(1);
	
	setDecodeMode(0);
	clear();
	setIntensity(0x00);
	setScanLimit(0x07);
	shutdown(0);
	
}

void set_all_register(uint16_t data){
	pullCSDown();
	char i=0;
	for(i=0;i<MAX7219_NUMBER;i++){
		shiftOut(data);
	}
	pullCSUp();
}

void set_single_register(uint8_t index,uint16_t data){
	pullCSDown();
	for(int i=MAX7219_NUMBER-1;i>=0;i--){
		if(i==index){
			shiftOut(data);
		}else{
			shiftOut(0);
		}
	}
	
	pullCSUp();
}

void clear(void){
	uint8_t i=0;
	for(;i<8;i++){
		set_all_register(MAX7219_ADRR_DIGIT(i));
	}
}

void shiftOut(uint16_t data){
	uint8_t i=0;
	_Bool d=0;
	
	for(;i<16;i++){
		d=((data&0x8000)!=0);
		if(d){
			HAL_GPIO_WritePin(port_din,pin_din,GPIO_PIN_SET);
		}else{
			HAL_GPIO_WritePin(port_din,pin_din,GPIO_PIN_RESET);
		}
		
		HAL_GPIO_WritePin(port_clk,pin_clk,GPIO_PIN_SET);
		
		HAL_GPIO_WritePin(port_clk,pin_clk,GPIO_PIN_RESET);
		
		data=((data<<1)&0xffff);
	}
		HAL_GPIO_WritePin(port_din,pin_din,GPIO_PIN_RESET);
}

void setDigit(uint8_t index,uint8_t digit,uint8_t data){
	set_single_register(index,MAX7219_ADRR_DIGIT(digit)|data);
}

void shutdown(_Bool enable){
	set_all_register(MAX7219_ADRR_SHUTDOWN|!enable);
}

void displayTest(_Bool enable){
	set_all_register(MAX7219_ADRR_DISPLAY_TEST|enable);
}

void setDecodeMode(uint8_t decode){
	set_all_register(MAX7219_ADRR_DECODE_MODE|decode);
}

void setIntensity(uint8_t intensity){
	set_all_register(MAX7219_ADRR_INTENSITY|intensity);
}

void setScanLimit(uint8_t limit){
	set_all_register(MAX7219_ADRR_SCAN_LIMIT|limit);
}

void pullCSDown(void){
	HAL_GPIO_WritePin(port_cs,pin_cs,GPIO_PIN_RESET);
}

void pullCSUp(void){
	HAL_GPIO_WritePin(port_cs,pin_cs,GPIO_PIN_SET);
}