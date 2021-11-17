//main.c
//
//Author: Alperen Arslan
//Description: Changes the mode of the LED by pressing the button.
//At the same time, it shows which mode it is in with a 7-segment display.
//External Interrupt Used

#include "stm32g0xx.h"

void EXTI2_3_IRQHandler();

int main(void) {
    // Enable GPIOB clock
    RCC->IOPENR |= (1U << 1);

    // Setup PA9, PA10, PA15, PB0, PB1, PB4, PB6, PB7  as output and PB5 as input
    //GPIOB->MODER &= (0U << 2*8);
    //GPIOB->PUPDR |= (2U << 2*8);
    GPIOB->MODER &= ~(3U << 2*3);
    GPIOB->MODER &= ~(3U << 2*7);
    GPIOB->MODER |= (1U << 2*7);

    EXTI->EXTICR[0] |= (1U << 8*3); //PB8 3. Mux
    EXTI->RTSR1 |= (1U << 3); //Rising Edge PB8
    EXTI->IMR1 |= (1U << 3); //Mask for PB8
    NVIC_SetPriority(EXTI2_3_IRQn, 0);
    NVIC_EnableIRQ(EXTI2_3_IRQn);

    while(1){
    }
}

void EXTI2_3_IRQHandler(){
		GPIOB->ODR ^= (1U << 7);
		EXTI->RPR1 |= (1U << 3);
}
