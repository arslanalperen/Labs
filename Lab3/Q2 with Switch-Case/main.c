//main.c
//
//Author: Alperen Arslan
//Description: Changes the mode of the LED by pressing the button.
//At the same time, it shows which mode it is in with a 7-segment display.

#include "stm32g0xx.h"

#define WHILEDELAY 600000
#define TWOSLEDDELAY 3200000
#define ONESLEDDELAY 1600000
#define DOTFIVELEDDELAY 800000
#define DOTONELEDDELAY 160000

int counter = 0;
void delay(volatile uint32_t);
void noToggleLedOff();
void noToggleLedOn();
void Toggle2s();
void Toggle1s();
void Toggle05s();
void Toggle01s();
void display0Mode();
void display1Mode();
void display2Mode();
void display3Mode();
void display4Mode();
void display5Mode();

int main(void) {
    // Enable GPIOB clock
	RCC->IOPENR |= (1U << 1);

    //Setup PA9, PA10, PA15, PB0, PB1, PB4, PB6, PB7  as output and PB5 as input
    GPIOB->MODER &= 0xFFFC5555;

    while(1){
    int value = GPIOB->IDR &= (1U << 8); //Getting button value
    if (value == 0x100){
    	switch(counter){
    		case 0:
    			display0Mode(); //Display current mode to see mode at the 7 segment
    			counter ++; //Change mode
    			noToggleLedOff(); //Set Mode
    			break;
    		case 1:
    			display1Mode();
    			counter ++;
    			noToggleLedOn();
    			break;
    		case 2:
    			display2Mode();
    			counter ++;
    			Toggle2s();
    		    break;
    		case 3:
    			display3Mode();
    		    counter ++;
    		    Toggle1s();
    		    break;
    		case 4:
    			display4Mode();
    			counter ++;
    		    Toggle05s();
    		    break;
    		case 5:
    			display5Mode();
    		    counter = 0;
    		    Toggle01s();
    		    break;
    	}
    }
    delay(WHILEDELAY); //Delay for getting hand back from button
    }
}

void noToggleLedOff(){
	GPIOB->ODR &= ~(1U << 7);
}

void noToggleLedOn(){
	GPIOB->ODR |= (1U << 7);
}

void Toggle2s(){
	int value;
	delay(WHILEDELAY);
	while(1){
		value = GPIOB->IDR &= (1U << 8);
		if(value == 0x100)
			break;
		GPIOB->ODR |= (1U << 7);
		delay(TWOSLEDDELAY);
		GPIOB->ODR &= ~(1U << 7);
		delay(TWOSLEDDELAY);
	}
}

void Toggle1s(){
	int value;
	delay(WHILEDELAY);
	while(1){
		value = GPIOB->IDR &= (1U << 8);
		if(value == 0x100)
			break;
		GPIOB->ODR |= (1U << 7);
		delay(ONESLEDDELAY);
		GPIOB->ODR &= ~(1U << 7);
		delay(ONESLEDDELAY);
	}
}

void Toggle05s(){
	int value;
	delay(WHILEDELAY);
	while(1){
		value = GPIOB->IDR &= (1U << 8);
		if(value == 0x100)
			break;
		GPIOB->ODR |= (1U << 7);
		delay(DOTFIVELEDDELAY);
		GPIOB->ODR &= ~(1U << 7);
		delay(DOTFIVELEDDELAY);
	}
}

void Toggle01s(){
	int value;
	delay(WHILEDELAY);
	while(1){
		value = GPIOB->IDR &= (1U << 8);
		if(value == 0x100)
			break;
		GPIOB->ODR |= (1U << 7);
		delay(DOTONELEDDELAY);
		GPIOB->ODR &= ~(1U << 7);
		delay(DOTONELEDDELAY);
	}
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}

void display0Mode(){
	GPIOB->ODR &= 0x0000;
	GPIOB->ODR |= 0x003F;
}

void display1Mode(){
	GPIOB->ODR &= 0x0000;
	GPIOB->ODR |= 0x0006;
}

void display2Mode(){
	GPIOB->ODR &= 0x0000;
	GPIOB->ODR |= 0x005B;
}

void display3Mode(){
	GPIOB->ODR &= 0x0000;
	GPIOB->ODR |= 0x004F;
}

void display4Mode(){
	GPIOB->ODR &= 0x0000;
	GPIOB->ODR |= 0x0066;
}

void display5Mode(){
	GPIOB->ODR &= 0x0000;
	GPIOB->ODR |= 0x006D;
}
