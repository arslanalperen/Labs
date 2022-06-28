/*
 * main.c
 *
 * author: Alican Bayındır
 *
 * Problem 3 [20 pts].Implement the same state machine in Problem 2,
 * but this time use external interrupts to detect button press, and
 * use the handler to change the state.Questions:●What is the difference
 * between Problem 2 and Problem 3 in terms of scalability, clarityand
 * responsiveness?Compare the oscilloscope outputs for both of them and explain.
 *
 *
 */


/*****************************************
 * * * * * * * LIBRARIES * * * * * * * * *
*****************************************/
#include "stm32g0xx.h"

/*****************************************
 * * * * * * * CONSTANTS * * * * * * * * *
*****************************************/
#define LEDDELAY    1600000

/*****************************************
 * * * * FUNCTION DEFINITIONS * * * * * *
*****************************************/
void delay(volatile uint32_t);
void led_blink(int32_t change);
void led_off();

/*****************************************
 * * * * * * * * ENUM * * * * * * * * * *
*****************************************/
enum states{
	mode_0,
	mode_1,
	mode_2,
	mode_3,
	mode_4,
	mode_5,
} mode;

int mode_counter = 0;

/*****************************************
 * * * * * * * INTERRUPT * * * * * * * * *
*****************************************/
void EXTI2_3_IRQHandler(void){
	/* Checks if button pressed or not if pressed make button_pressed = 1*/
	/* If button pressed then increase mode and counter +1*/
	mode ++;

	/* if mode is more than 6 then make mode = mode_0 if not then stay same*/
	mode = (mode == 6) ?  mode_0 : mode_counter;

	/* if mode_counter is more than 6 then reset it if not then stay same */
	mode_counter = (mode == 6) ? 0 : mode_counter;

	EXTI -> RPR1 |= (1U << 3);
}

/*****************************************
 * * * * * * * MAIN FUNC * * * * * * * * *
*****************************************/
int main(void) {
	/* Enable GPIOB clock */
	RCC -> IOPENR |= (2U);

	GPIOB->MODER &= ~(3U << 2*3);
	GPIOB->PUPDR &= (2U << 2*3);
	GPIOB->MODER &= ~(3U << 2*7);
	GPIOB->MODER |= (1U << 2*7);

	/*****************************************
	 * * * * * * * MODE INIT * * * * * * * * *
	*****************************************/
	mode = mode_0;

	/*****************************************
	 * * * * * * * INTERRUPT * * * * * * * * *
	*****************************************/
	EXTI->EXTICR[0] |= (1U << 8*3); //PB8 3. Mux
	EXTI->RTSR1 |= (1U << 3); //Rising Edge PB8
	EXTI->IMR1 |= (1U << 3); //Mask for PB8
	NVIC_SetPriority(EXTI2_3_IRQn, 0);
	NVIC_EnableIRQ(EXTI2_3_IRQn);

	while(1){
			/* taking action according to modes*/
			switch(mode){
				case mode_0:
					led_off();
					break;
				case mode_1:
					led_blink(1600000);
					break;
				case mode_2:
					led_blink(0);
					break;
				case mode_3:
					led_blink(-800000);
					break;
				case mode_4:
					led_blink(-1300000);
					break;
				case mode_5:
					led_blink(-1600000);
					break;
			}
		}

	return 0;
}

void led_blink(int32_t change){
	// There is a warning which will occur if change > LEDDELAY const
	delay(LEDDELAY + change);
	if(change >= -1500000)
		GPIOB -> ODR ^= (1U<<7);
	else
	/* To prevent toggling we should the code below when change = LEDDELAY */
		GPIOB -> ODR = (1U<<7);
}

void led_off(){
	GPIOB -> ODR =(0U);
}

void delay(volatile uint32_t s) {
	for(; s>0; s--);
}
