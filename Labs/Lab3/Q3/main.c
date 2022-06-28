//main.c
//
//Author: Alperen Arslan
//Description: Changes the mode of the LED by pressing the button.
//At the same time, it shows which mode it is in with a 7-segment display.
//External Interrupt Used

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
void EXTI2_3_IRQHandler(int mode);

int main(void) {
    // Enable GPIOB clock
    RCC->IOPENR |= (1U << 1);

    // Setup PB0, PB1, ... PB8 (except PB3) as output and PB3 as input
    GPIOB->MODER &= 0xFFF55515;
    GPIOB->PUPDR |= (2U << 2*3);

    //Enum for change between modes
    enum changeMode {mode0, mode1, mode2, mode3, mode4, mode5}mode;
    mode = mode0;

    EXTI->IMR1 |= (1U << 3); //Mask for PB3
    EXTI->RTSR1 |= (1U << 3); //Rising Edge PB3
    EXTI->EXTICR[0] |= (1U << 8*3); //PB3 0 Mux
    NVIC_SetPriority(EXTI2_3_IRQn, 0);
    NVIC_EnableIRQ(EXTI2_3_IRQn);

    while(1){
    	switch(mode){
    		case mode0:
    			display0mode(); //Display current mode to see mode at the 7 segment
    		    noToggleLedOff(mode); //Set mode
    		    break;
    		case mode1:
    			display1mode();
    			Toggle2s(mode);
    		    break;
    		case mode2:
    			display2mode();
    			Toggle1s(mode);
    			break;
    		case mode3:
    			display3mode();
    			Toggle05s(mode);
    		    break;
    		case mode4:
    			display4mode();
    			Toggle01s(mode);
    		    break;
    		case mode5:
    			display5mode();
    			noToggleLedOn(mode);
    			break;
    	}
    	delay(600000); //Delay for getting hand back from button
    }
}

void EXTI2_3_IRQHandler(int mode){
	//If code at the last mode, change to first mode
	GPIOB->ODR |= (1U << 9);
	if(mode == 5)
		mode = 0;
	else
		mode ++; //Change mode
	EXTI->RPR1 |= (1U << 3);
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
	GPIOB->ODR |= 0x0137;
}

void display1mode(){
	GPIOB->ODR &= 0x0000;
	GPIOB->ODR |= 0x0006;
}

void display2mode(){
	GPIOB->ODR &= 0x0000;
	GPIOB->ODR |= 0x0153;
}

void display3mode(){
	GPIOB->ODR &= 0x0000;
	GPIOB->ODR |= 0x0147;
}

void display4mode(){
	GPIOB->ODR &= 0x0000;
	GPIOB->ODR |= 0x0066;
}

void display5mode(){
	GPIOB->ODR &= 0x0000;
	GPIOB->ODR |= 0x0165;
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
