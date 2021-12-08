#include "bsp.h"
#include "stm32g0xx.h"
#include "string.h"

/*
void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
*/
void BSP_led_init(void){
    /* Enable GPIOC clock */
    RCC -> IOPENR |= (1U << 2);

    /* Setup PC6 as output */
    GPIOC -> MODER &= ~(3U << 2 * 6);
    GPIOC -> MODER |= (1U << 2 * 6);

    /* Turn on LED */
    GPIOC -> BRR |= (1U << 6);
}

void BSP_button_init(){
	/* Enable GPIOF clock */
	RCC -> IOPENR |= (1U << 5);

	/* Setup PF2 as output */
	GPIOF -> MODER &= ~(3U << 2 * 2);
}

int BSP_button_read(){
	int button_value = ((GPIOF -> IDR >> 2) & 0x0001);
	if(button_value) return 0;
	else return 1;
}

void BSP_system_init(){
	SystemCoreClockUpdate();
	BSP_led_init();
	BSP_button_init();
	SysTick_Config(SystemCoreClock / 1000);
}

void init_timer1(){
	RCC -> APBENR2 |= (1U << 11); //Enable TIM1 module clock

	TIM1 -> CR1 = 0; //Zero out the control register just in case
	TIM1 -> CR1 |= (1 << 7); //ARPE
	TIM1 -> CNT = 0; //Zero out counter

	//1 Second Interrupt
	TIM1 -> PSC = 999;
	TIM1 -> ARR = 16000;

	TIM1 -> DIER |= (1 << 0); //Update interrupt enable
	TIM1 -> CR1 |= (1 << 0); //TIM1 Enable

	NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 1);
	NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
}

void BSP_led_set(void){
    GPIOC -> ODR |= (1U << 6);
}

void BSP_led_reset(void){
    GPIOC -> BRR |= (1U << 6);
}

void BSP_led_toggle(void){
    GPIOC->ODR ^= (1U << 6);
}

void BSP_SetSSD(char *pin){
	char pinNumber = pin[1];
	char type = pin[0];

	BSP_SetDigitalPins(pinNumber);

	/*
	//char *p = &type;
	//BSP_SetDigitalPins(pinNumber);

	//char pinName = 'D';
	//char *ptr = &pinName;
	//int cmp = strcmp(p,ptr);
	if(type == 'D'){
		BSP_SetDigitalPins(pinNumber);
	}
	else{
		BSP_SetAnalogPins(pinNumber);
	}
	*/
}

void BSP_SetDigitalPins(char pinNumber){
	int pinNumberInt = atoi(pinNumber);
	if(pinNumberInt == 2 | pinNumberInt == 4 | pinNumberInt == 5 | pinNumberInt == 9){
		RCC->IOPENR |= (1U << 0);
		GPIOA->MODER &= ~(3U << 2*pinNumberInt);
		GPIOA->MODER |=  (1U << 2*pinNumberInt);
	}
	else {
		RCC->IOPENR |= (1U << 1);
		GPIOB->MODER &= ~(3U << 2*pinNumberInt);
		GPIOB->MODER |=  (1U << 2*pinNumberInt);
	}
}

void BSP_SetAnalogPins(char pinNumber){

}

void BSP_DisplaySSD(struct ssdPin){
	switch(displayChar){
	case '0':

	}
}
