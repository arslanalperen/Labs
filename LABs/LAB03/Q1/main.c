// main.c
// Author: Alperen Arslan

#include "stm32g0xx.h"

#define LEDDELAY 1600000 //In 1 second, MCU process 16 mHz

void delay(volatile uint32_t);

int main(void) {

    // Enable GPIOB clock
    RCC->IOPENR |= 2U;

    // Setup PB4 as output
    GPIOB->MODER = 0xDFF;

    // Turn on LED
    GPIOB->ODR |= (1U << 4);

    while(1) {
        delay(LEDDELAY);
        GPIOB->ODR ^= (1U << 4); // Toggle LED
    }
    return 0;
}

void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
