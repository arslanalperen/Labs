/*
 * main.c
 *
 * author: Alperen Arslan
 *
 * description: Blinks 1 on-board LED at roughly 1 second intervals. system
 *   clock is running from HSI which is 16 Mhz. Delay function is just a simple
 *   counter so is not accurate and the delay time will change based on the
 *   optimization flags.
 */

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

int main(void) {
    /* Enable GPIOC clock */
    RCC->IOPENR |= (1U << 1);

    /* Setup PC6 as output */
    GPIOB->MODER &= ~(3U << 2*4);
    GPIOB->MODER |= (1U << 2*4);
    GPIOB->MODER &= ~(3U << 2*9);
    GPIOB->MODER |= (1U << 2*9);
    GPIOB->MODER &= ~(3U << 2*5);

    while(1){
    GPIOB->ODR &= ~(1U << 9);
    int value = GPIOB->IDR &= (1U << 5);
    if (value == 0x20){
    	switch(counter){
    		case 0:
    			GPIOB->ODR |= (1U << 9);
    			counter ++;
    			noToggleLedOff();
    			break;
    		case 1:
    			GPIOB->ODR |= (1U << 9);
    			counter ++;
    			noToggleLedOn();
    			break;
    		case 2:
    			GPIOB->ODR |= (1U << 9);
    			counter ++;
    			Toggle2s();
    		    break;
    		case 3:
    			GPIOB->ODR |= (1U << 9);
    		    counter ++;
    		    Toggle1s();
    		    break;
    		case 4:
    			GPIOB->ODR |= (1U << 9);
    			counter ++;
    		    Toggle05s();
    		    break;
    		case 5:
    			GPIOB->ODR |= (1U << 9);
    		    counter = 0;
    		    Toggle01s();
    		    break;
    	}
    }
    delay(WHILEDELAY);
    }
}

void noToggleLedOff(){
	GPIOB->ODR &= ~(1U << 4);
}

void noToggleLedOn(){
	GPIOB->ODR |= (1U << 4);
}

void Toggle2s(){
	int value;
	delay(WHILEDELAY);
	while(1){
		value = GPIOB->IDR &= (1U << 5);
		if(value == 0x20)
			break;
		GPIOB->ODR |= (1U << 4);
		delay(TWOSLEDDELAY);
		GPIOB->ODR &= ~(1U << 4);
		delay(TWOSLEDDELAY);
	}
}

void Toggle1s(){
	int value;
	delay(WHILEDELAY);
	while(1){
		value = GPIOB->IDR &= (1U << 5);
		if(value == 0x20)
			break;
		GPIOB->ODR |= (1U << 4);
		delay(ONESLEDDELAY);
		GPIOB->ODR &= ~(1U << 4);
		delay(ONESLEDDELAY);
	}
}

void Toggle05s(){
	int value;
	delay(WHILEDELAY);
	while(1){
		value = GPIOB->IDR &= (1U << 5);
		if(value == 0x20)
			break;
		GPIOB->ODR |= (1U << 4);
		delay(DOTFIVELEDDELAY);
		GPIOB->ODR &= ~(1U << 4);
		delay(DOTFIVELEDDELAY);
	}
}

void Toggle01s(){
	int value;
	delay(WHILEDELAY);
	while(1){
		value = GPIOB->IDR &= (1U << 5);
		if(value == 0x20)
			break;
		GPIOB->ODR |= (1U << 4);
		delay(DOTONELEDDELAY);
		GPIOB->ODR &= ~(1U << 4);
		delay(DOTONELEDDELAY);
	}
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
