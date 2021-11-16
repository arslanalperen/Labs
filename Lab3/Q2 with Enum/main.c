//main.c
//
//Author: Alperen Arslan
//Description: Changes the mode of the LED by pressing the button.
//At the same time, it shows which mode it is in with a 7-segment display.

#include "stm32g0xx.h"

void delay(volatile uint32_t);
void noToggleLedOff();
void noToggleLedOn();
void Toggle2s();
void Toggle1s();
void Toggle05s();
void Toggle01s();
void display0mode();
void display1mode();
void display2mode();
void display3mode();
void display4mode();
void display5mode();

int main(void) {
    // Enable GPIOB clock
    RCC->IOPENR |= (1U << 1);

    // Setup PA9, PA10, PA15, PB0, PB1, PB4, PB6, PB7  as output and PB5 as input
    GPIOB->MODER &= 0xFFFC5555;

    //Enum for change between modes
    enum changemode {mode0, mode1, mode2, mode3, mode4, mode5}mode;
    mode = mode0;

    while(1){
    	int value = GPIOB->IDR &= (1U << 8);
    	    if (value == 0x100){
    			if(mode == mode5) //If code at the last mode, change to first mode
    				mode = mode0;
    			else
    				mode ++; //Change mode
    		}
    	switch(mode){
    		case mode0:
    			display0mode(); //Display current mode to see mode at the 7 segment
    			noToggleLedOff(mode); //Set mode
    			break;
    		case mode1:
    			display1mode();
    			noToggleLedOn(mode);
    			break;
    		case mode2:
    			display2mode();
    			Toggle2s(mode);
    			break;
    		case mode3:
    			display3mode();
    			Toggle1s(mode);
    			break;
    		case mode4:
    			display4mode();
    			Toggle05s(mode);
    			break;
    		case mode5:
    			display5mode();
    			Toggle01s(mode);
    			break;
    	}
    	delay(600000); //Delay for getting hand back from button
    }
}

void noToggleLedOff(){
	GPIOB->ODR &= ~(1U << 7);
}

void noToggleLedOn(){
	GPIOB->ODR |= (1U << 7);
}

void Toggle2s(){
	GPIOB->ODR |= (1U << 7);
	delay(3200000);
	GPIOB->ODR &= ~(1U << 7);
	delay(3200000);
}

void Toggle1s(){
	GPIOB->ODR |= (1U << 7);
	delay(1600000);
	GPIOB->ODR &= ~(1U << 7);
	delay(1600000);
}

void Toggle05s(){
	GPIOB->ODR |= (1U << 7);
	delay(800000);
	GPIOB->ODR &= ~(1U << 7);
	delay(800000);
}

void Toggle01s(){
	GPIOB->ODR |= (1U << 7);
	delay(160000);
	GPIOB->ODR &= ~(1U << 7);
	delay(160000);
}

void display0mode(){
	GPIOB->ODR &= 0x0000;
	GPIOB->ODR |= 0x003F;
}

void display1mode(){
	GPIOB->ODR &= 0x0000;
	GPIOB->ODR |= 0x0006;
}

void display2mode(){
	GPIOB->ODR &= 0x0000;
	GPIOB->ODR |= 0x005B;
}

void display3mode(){
	GPIOB->ODR &= 0x0000;
	GPIOB->ODR |= 0x004F;
}

void display4mode(){
	GPIOB->ODR &= 0x0000;
	GPIOB->ODR |= 0x0066;
}

void display5mode(){
	GPIOB->ODR &= 0x0000;
	GPIOB->ODR |= 0x006D;
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
