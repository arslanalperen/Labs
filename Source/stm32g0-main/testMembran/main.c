#include "stm32g0xx.h"
#include "system_stm32g0xx.h"

int currentKeyPressed;
static uint32_t tDelay;
void clearSSD(void);
void setSSD(int);

void clearRowsKeypad(void);
void setRowsKeypad(void);
void delay();

void init_systick(uint32_t s);
void SysTick_Handler(void);
void delay_ms(uint32_t s);

void EXTI0_1_IRQHandler(void){
	clearRowsKeypad();

	GPIOA->ODR ^= (1U << 7);
	if((GPIOA->IDR >> 0) & 1){
		currentKeyPressed = 10;
		setSSD(currentKeyPressed);
	}
	GPIOA->ODR ^= (1U << 7);

	GPIOA->ODR ^= (1U << 6);
	if((GPIOA->IDR >> 0) & 1){
		currentKeyPressed = 11;
		setSSD(currentKeyPressed);
	}
	GPIOA->ODR ^= (1U << 6);

	GPIOA->ODR ^= (1U << 11);
	if((GPIOA->IDR >> 0) & 1){
		currentKeyPressed = 12;
		setSSD(currentKeyPressed);
	}
	GPIOA->ODR ^= (1U << 11);

	GPIOA->ODR ^= (1U << 12);
	if((GPIOA->IDR >> 0) & 1){
		currentKeyPressed = 13;
		setSSD(currentKeyPressed);
	}
	GPIOA->ODR ^= (1U << 12);

	GPIOA->ODR ^= (1U << 7);
	if((GPIOA->IDR >> 1) & 1){
		currentKeyPressed = 3;
		setSSD(currentKeyPressed);
	}
	GPIOA->ODR ^= (1U << 7);

	GPIOA->ODR ^= (1U << 6);
	if((GPIOA->IDR >> 1) & 1){
		currentKeyPressed = 6;
		setSSD(currentKeyPressed);
	}
	GPIOA->ODR ^= (1U << 6);

	GPIOA->ODR ^= (1U << 11);
	if((GPIOA->IDR >> 1) & 1){
		currentKeyPressed = 9;
		setSSD(currentKeyPressed);
	}
	GPIOA->ODR ^= (1U << 11);

	GPIOA->ODR ^= (1U << 12);
	if((GPIOA->IDR >> 1) & 1){
		currentKeyPressed = 14; //#
		setSSD(currentKeyPressed);
	}
	GPIOA->ODR ^= (1U << 12);

	setRowsKeypad();
	EXTI ->RPR1 |= 0xFFF;
}

void EXTI4_15_IRQHandler(void){
	clearRowsKeypad();

	GPIOA->ODR ^= (1U << 7);
	if((GPIOA->IDR >> 4) & 1){
		currentKeyPressed = 2;
		setSSD(currentKeyPressed);
	}
	GPIOA->ODR ^= (1U << 7);

	GPIOA->ODR ^= (1U << 6);
	if((GPIOA->IDR >> 4) & 1){
		currentKeyPressed = 5;
		setSSD(currentKeyPressed);
	}
	GPIOA->ODR ^= (1U << 6);

	GPIOA->ODR ^= (1U << 11);
	if((GPIOA->IDR >> 4) & 1){
		currentKeyPressed = 8;
		setSSD(currentKeyPressed);
	}
	GPIOA->ODR ^= (1U << 11);

	GPIOA->ODR ^= (1U << 12);
	if((GPIOA->IDR >> 4) == 0x1){
		currentKeyPressed = 0;
		setSSD(currentKeyPressed);
	}
	GPIOA->ODR ^= (1U << 12);

	GPIOA->ODR ^= (1U << 7);
	if((GPIOA->IDR >> 5) & 1){
		currentKeyPressed = 1;
		setSSD(currentKeyPressed);
	}
	GPIOA->ODR ^= (1U << 7);

	GPIOA->ODR ^= (1U << 6);
	if((GPIOA->IDR >> 5) & 1){
		currentKeyPressed = 4;
		setSSD(currentKeyPressed);
	}
	GPIOA->ODR ^= (1U << 6);

	GPIOA->ODR ^= (1U << 11);
	if((GPIOA->IDR >> 5) & 1){
		currentKeyPressed = 7;
		setSSD(currentKeyPressed);
	}
	GPIOA->ODR ^= (1U << 11);

	GPIOA->ODR ^= (1U << 12);
	if((GPIOA->IDR >> 5) & 1){
		currentKeyPressed = 15; //*
		setSSD(currentKeyPressed);
	}
	GPIOA->ODR ^= (1U << 12);

	setRowsKeypad();
	EXTI ->RPR1 |= 0xFFF;
	//delay_ms(500);
}

int main(){
	//Enable GPIOA and GPIOB clocks
	RCC->IOPENR |= (3U << 0);

	//Setup PA6, PA7, PA11, and PA12 as output (rows)
	GPIOA->MODER &= ~(3U << 2*6);
	GPIOA->MODER |= (1U << 2*6);

	GPIOA->MODER &= ~(3U << 2*7);
	GPIOA->MODER |= (1U << 2*7);

	GPIOA->MODER &= ~(3U << 2*11);
	GPIOA->MODER |= (1U << 2*11);

	GPIOA->MODER &= ~(3U << 2*12);
	GPIOA->MODER |= (1U << 2*12);

	//Setup PA0, PA1, PA4, and PA5 as input (columns)
	GPIOA->MODER &= ~(3U << 2*0);
	GPIOA->PUPDR |= (2U << 2*0); //Pull-down mode

	GPIOA->MODER &= ~(3U << 2*1);
	GPIOA->PUPDR |= (2U << 2*1);

	GPIOA->MODER &= ~(3U << 2*4);
	GPIOA->PUPDR |= (2U << 2*4);

	GPIOA->MODER &= ~(3U << 2*5);
	GPIOA->PUPDR |= (2U << 2*5);

	//Setup interrupts for inputs PA0, PA1, PA4, and PA5
	EXTI->EXTICR[0] |= (0U << 8*0); //PA0
	EXTI->EXTICR[0] |= (0U << 8*1); //PA1
	EXTI->EXTICR[1] |= (0U << 8*0); //PA4
	EXTI->EXTICR[1] |= (0U << 8*1); //PA5

	//Rising Edge
	EXTI->RTSR1 |= (1U << 0);
	EXTI->RTSR1 |= (1U << 1);
	EXTI->RTSR1 |= (1U << 4);
	EXTI->RTSR1 |= (1U << 5);

	//Mask
	EXTI->IMR1 |= (1U << 0);
	EXTI->IMR1 |= (1U << 1);
	EXTI->IMR1 |= (1U << 4);
	EXTI->IMR1 |= (1U << 5);

	//NVIC
	NVIC_SetPriority(EXTI0_1_IRQn,0);
	NVIC_EnableIRQ(EXTI0_1_IRQn);

	NVIC_SetPriority(EXTI2_3_IRQn,0);
	NVIC_EnableIRQ(EXTI2_3_IRQn);

	NVIC_SetPriority(EXTI4_15_IRQn,0);
	NVIC_EnableIRQ(EXTI4_15_IRQn);

	//Set led as output PB8
	GPIOA->MODER &= ~(3U << 2*15);
	GPIOA->MODER |= (1U << 2*15);
	GPIOB->MODER &= ~(3U << 2*0);
	GPIOB->MODER |= (1U << 2*0);
	GPIOB->MODER &= ~(3U << 2*1);
	GPIOB->MODER |= (1U << 2*1);
	GPIOB->MODER &= ~(3U << 2*2);
	GPIOB->MODER |= (1U << 2*2);
	GPIOB->MODER &= ~(3U << 2*3);
	GPIOB->MODER |= (1U << 2*3);
	GPIOB->MODER &= ~(3U << 2*4);
	GPIOB->MODER |= (1U << 2*4);
	GPIOB->MODER &= ~(3U << 2*5);
	GPIOB->MODER |= (1U << 2*5);
	GPIOB->MODER &= ~(3U << 2*6);
	GPIOB->MODER |= (1U << 2*6);
	GPIOB->MODER &= ~(3U << 2*7);
	GPIOB->MODER |= (1U << 2*7);

	//Set all rows
	GPIOA->ODR |= (1U << 6);
	GPIOA->ODR |= (1U << 7);
	GPIOA->ODR |= (1U << 11);
	GPIOA->ODR |= (1U << 12);

	while(1){
	}
	return 0 ;
}

void clearRowsKeypad(void){
	//Clear the rows here
	GPIOA->ODR &= ~(1U << 6);
	GPIOA->ODR &= ~(1U << 7);
	GPIOA->ODR &= ~(1U << 11);
	GPIOA->ODR &= ~(1U << 12);
}

void setRowsKeypad(void){
	//Setting the rows here
	GPIOA->ODR |= (1U << 6);
	GPIOA->ODR |= (1U << 7);
	GPIOA->ODR |= (1U << 11);
	GPIOA->ODR |= (1U << 12);
}

void delay(uint32_t time){
	while(time--);
}

void clearSSD(){
	GPIOB->ODR &= (0U << 0);
	GPIOB->ODR &= (0U << 1);
	GPIOB->ODR &= (0U << 2);
	GPIOB->ODR &= (0U << 3);
	GPIOB->ODR &= (0U << 4);
	GPIOB->ODR &= (0U << 5);
	GPIOB->ODR &= (0U << 6);
	GPIOB->ODR &= (0U << 7);
}

void setSSD(int x){
	clearSSD();
	switch(x){
		case 0:
			GPIOB->ODR |= (1U << 1);
			GPIOB->ODR |= (1U << 2);
			GPIOB->ODR |= (1U << 3);
			GPIOB->ODR |= (1U << 4);
			GPIOB->ODR |= (1U << 5);
			GPIOB->ODR |= (1U << 6);
			break;
		case 1:
			GPIOB->ODR |= (1U << 2);
			GPIOB->ODR |= (1U << 3);
			break;
		case 2:
			GPIOB->ODR |= (1U << 1);
			GPIOB->ODR |= (1U << 2);
			GPIOB->ODR |= (1U << 7);
			GPIOB->ODR |= (1U << 5);
			GPIOB->ODR |= (1U << 4);
			break;
		case 3:
			GPIOB->ODR |= (1U << 1);
			GPIOB->ODR |= (1U << 2);
			GPIOB->ODR |= (1U << 3);
			GPIOB->ODR |= (1U << 4);
			GPIOB->ODR |= (1U << 7);
			break;
		case 4:
			GPIOB->ODR |= (1U << 6);
			GPIOB->ODR |= (1U << 2);
			GPIOB->ODR |= (1U << 7);
			GPIOB->ODR |= (1U << 3);
			break;
		case 5:
			GPIOB->ODR |= (1U << 1);
			GPIOB->ODR |= (1U << 6);
			GPIOB->ODR |= (1U << 7);
			GPIOB->ODR |= (1U << 3);
			GPIOB->ODR |= (1U << 4);
			break;
		case 6:
			GPIOB->ODR |= (1U << 1);
			GPIOB->ODR |= (1U << 6);
			GPIOB->ODR |= (1U << 7);
			GPIOB->ODR |= (1U << 3);
			GPIOB->ODR |= (1U << 4);
			GPIOB->ODR |= (1U << 5);
			break;
		case 7:
			GPIOB->ODR |= (1U << 1);
			GPIOB->ODR |= (1U << 2);
			GPIOB->ODR |= (1U << 3);
			break;
		case 8:
			GPIOB->ODR |= (1U << 1);
			GPIOB->ODR |= (1U << 2);
			GPIOB->ODR |= (1U << 3);
			GPIOB->ODR |= (1U << 4);
			GPIOB->ODR |= (1U << 5);
			GPIOB->ODR |= (1U << 6);
			GPIOB->ODR |= (1U << 7);
			break;
		case 9:
			GPIOB->ODR |= (1U << 1);
			GPIOB->ODR |= (1U << 2);
			GPIOB->ODR |= (1U << 3);
			GPIOB->ODR |= (1U << 4);
			GPIOB->ODR |= (1U << 6);
			GPIOB->ODR |= (1U << 7);
			break;
		case 10:
			GPIOB->ODR |= (1U << 1);
			GPIOB->ODR |= (1U << 2);
			GPIOB->ODR |= (1U << 3);
			GPIOB->ODR |= (1U << 5);
			GPIOB->ODR |= (1U << 6);
			GPIOB->ODR |= (1U << 7);
			break;
		case 11:
			GPIOB->ODR |= (1U << 3);
			GPIOB->ODR |= (1U << 4);
			GPIOB->ODR |= (1U << 5);
			GPIOB->ODR |= (1U << 6);
			GPIOB->ODR |= (1U << 7);
			break;
		case 12:
			GPIOB->ODR |= (1U << 1);
			GPIOB->ODR |= (1U << 4);
			GPIOB->ODR |= (1U << 5);
			GPIOB->ODR |= (1U << 6);
			break;
		case 13:
			GPIOB->ODR |= (1U << 2);
			GPIOB->ODR |= (1U << 3);
			GPIOB->ODR |= (1U << 4);
			GPIOB->ODR |= (1U << 5);
			GPIOB->ODR |= (1U << 7);
			break;
	}
}

/*SYSTICK functions*/

void init_systick(uint32_t s){
    // Clear CTRL register
    SysTick->CTRL = 0x00000;
    // Main clock source is running with HSI by default which is at 8 Mhz.
    // SysTick clock source can be set with CTRL register (Bit 2)
    // 0: Processor clock/8 (AHB/8)
    // 1: Processor clock (AHB)
    SysTick->CTRL |= (1 << 2);
    // Enable callback (bit 1)
    SysTick->CTRL |= (1 << 1);
    // Load the value
    SysTick->LOAD = (uint32_t)(s-1);
    // Set the current value to 0
    SysTick->VAL = 0;
    // Enable SysTick (bit 0)
    SysTick->CTRL |= (1 << 0);
}

void SysTick_Handler(void){
    if (tDelay != 0){
        tDelay--;
    }
}

void delay_ms(uint32_t s){
    tDelay = s;
    while(tDelay != 0);
}
