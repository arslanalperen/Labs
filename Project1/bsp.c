#include "bsp.h"
bool firstSet = 0;

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

void BSP_SetSSD(char pinStatus, int pinNumber, char *ssdPin){
	if(ssdPin == "D1"){
		ssdPins.D1Status = pinStatus;
		ssdPins.D1Pin = pinNumber;
	}
	else if(ssdPin == "D2"){
		ssdPins.D2Status = pinStatus;
		ssdPins.D2Pin = pinNumber;
	}
	else if(ssdPin == "D3"){
		ssdPins.D3Status = pinStatus;
		ssdPins.D3Pin = pinNumber;
	}
	else if(ssdPin == "D4"){
		ssdPins.D4Status = pinStatus;
		ssdPins.D4Pin = pinNumber;
	}
	else if(ssdPin == "d"){
		ssdPins.dStatus = pinStatus;
		ssdPins.dPin = pinNumber;
	}
	else if(ssdPin == "A"){
		ssdPins.AStatus = pinStatus;
		ssdPins.APin = pinNumber;
	}
	else if(ssdPin == "B"){
		ssdPins.BStatus = pinStatus;
		ssdPins.BPin = pinNumber;
	}
	else if(ssdPin == "C"){
		ssdPins.CStatus = pinStatus;
		ssdPins.CPin = pinNumber;
	}
	else if(ssdPin == "D"){
		ssdPins.DStatus = pinStatus;
		ssdPins.DPin = pinNumber;
	}
	else if(ssdPin == "E"){
		ssdPins.EStatus = pinStatus;
		ssdPins.EPin = pinNumber;
	}
	else if(ssdPin == "F"){
		ssdPins.FStatus = pinStatus;
		ssdPins.FPin = pinNumber;
	}
	else if(ssdPin == "G"){
		ssdPins.GStatus = pinStatus;
		ssdPins.GPin = pinNumber;
	}

	if(pinStatus == 'D'){
		BSP_SetDigitalPins(pinNumber);
	}
	else if(pinStatus == 'A'){
		BSP_SetAnalogPins(pinNumber);
	}
}

void BSP_SetDigitalPins(int pinNumber){
	if(pinNumber == 0){
		RCC->IOPENR |= (1U << 1); //GPIOB
		GPIOB->MODER &= ~(3U << 2*7); //PB7
		GPIOB->MODER |=  (1U << 2*7); //PB7
	}
	else if(pinNumber == 1){
		RCC->IOPENR |= (1U << 1); //GPIOB
		GPIOB->MODER &= ~(3U << 2*6); //PB6
		GPIOB->MODER |=  (1U << 2*6); //PB6
	}
	else if(pinNumber == 2){
		RCC->IOPENR |= (1U << 0); //GPIOA
		GPIOA->MODER &= ~(3U << 2*15); //PA15
		GPIOA->MODER |=  (1U << 2*15); //PA15
	}
	else if(pinNumber == 3){
		RCC->IOPENR |= (1U << 1); //GPIOB
		GPIOB->MODER &= ~(3U << 2*1); //PB1
		GPIOB->MODER |=  (1U << 2*1); //PB1
	}
	else if(pinNumber == 4){
		RCC->IOPENR |= (1U << 0); //GPIOA
		GPIOA->MODER &= ~(3U << 2*10); //PA10
		GPIOA->MODER |=  (1U << 2*10); //PA10
	}
	else if(pinNumber == 5){
		RCC->IOPENR |= (1U << 0); //GPIOA
		GPIOA->MODER &= ~(3U << 2*9); //PA9
		GPIOA->MODER |=  (1U << 2*9); //PA9
	}
	else if(pinNumber == 6){
		RCC->IOPENR |= (1U << 1); //GPIOB
		GPIOB->MODER &= ~(3U << 2*0); //PB0
		GPIOB->MODER |=  (1U << 2*0); //PB0
	}
	else if(pinNumber == 7){
		RCC->IOPENR |= (1U << 1); //GPIOB
		GPIOB->MODER &= ~(3U << 2*2); //PB2
		GPIOB->MODER |=  (1U << 2*2); //PB2
	}
	else if(pinNumber == 8){
		RCC->IOPENR |= (1U << 1); //GPIOB
		GPIOB->MODER &= ~(3U << 2*8); //PB8
		GPIOB->MODER |=  (1U << 2*8); //PB8
	}
	else if(pinNumber == 9){
		RCC->IOPENR |= (1U << 0); //GPIOA
		GPIOA->MODER &= ~(3U << 2*8); //PA8
		GPIOA->MODER |=  (1U << 2*8); //PA8
	}
	else if(pinNumber == 10){
		RCC->IOPENR |= (1U << 1); //GPIOB
		GPIOB->MODER &= ~(3U << 2*9); //PB9
		GPIOB->MODER |=  (1U << 2*9); //PB9
	}
	else if(pinNumber == 11){
		RCC->IOPENR |= (1U << 1); //GPIOB
		GPIOB->MODER &= ~(3U << 2*5); //PB5
		GPIOB->MODER |=  (1U << 2*5); //PB5
	}
	else if(pinNumber == 12){
		RCC->IOPENR |= (1U << 1); //GPIOB
		GPIOB->MODER &= ~(3U << 2*4); //PB4
		GPIOB->MODER |=  (1U << 2*4); //PB4
	}
	else if(pinNumber == 13){
		RCC->IOPENR |= (1U << 1); //GPIOB
		GPIOB->MODER &= ~(3U << 2*3); //PB3
		GPIOB->MODER |=  (1U << 2*3); //PB3
	}
}

void BSP_SetAnalogPins(int pinNumber){
	if(pinNumber == 0){
		RCC->IOPENR |= (1U << 0); //GPIOA
		GPIOA->MODER &= ~(3U << 2*0); //PA0
		GPIOA->MODER |=  (1U << 2*0); //PA0
	}
	else if(pinNumber == 1){
		RCC->IOPENR |= (1U << 0); //GPIOA
		GPIOA->MODER &= ~(3U << 2*1); //PA1
		GPIOA->MODER |=  (1U << 2*1); //PA1
	}
	else if(pinNumber == 2){
		RCC->IOPENR |= (1U << 0); //GPIOA
		GPIOA->MODER &= ~(3U << 2*4); //PA4
		GPIOA->MODER |=  (1U << 2*4); //PA4
	}
	else if(pinNumber == 3){
		RCC->IOPENR |= (1U << 0); //GPIOA
		GPIOA->MODER &= ~(3U << 2*5); //PA5
		GPIOA->MODER |=  (1U << 2*5); //PA5
	}
	else if(pinNumber == 4){
		RCC->IOPENR |= (1U << 0); //GPIOA
		GPIOA->MODER &= ~(3U << 2*12); //PA12
		GPIOA->MODER |=  (1U << 2*12); //PA12
	}
	else if(pinNumber == 5){
		RCC->IOPENR |= (1U << 0); //GPIOA
		GPIOA->MODER &= ~(3U << 2*11); //PA11
		GPIOA->MODER |=  (1U << 2*11); //PA11
	}
	else if(pinNumber == 6){
		RCC->IOPENR |= (1U << 0); //GPIOA
		GPIOA->MODER &= ~(3U << 2*6); //PA6
		GPIOA->MODER |=  (1U << 2*6); //PA6
	}
	else if(pinNumber == 7){
		RCC->IOPENR |= (1U << 0); //GPIOA
		GPIOA->MODER &= ~(3U << 2*7); //PA7
		GPIOA->MODER |=  (1U << 2*7); //PA7
	}
}

void BSP_DisplaySSD(int digit, char displayChar){
	if(displayChar == '0'){
		BSP_SSDPinStatusControl('A');
		BSP_SSDPinStatusControl('B');
		BSP_SSDPinStatusControl('C');
		BSP_SSDPinStatusControl('D');
		BSP_SSDPinStatusControl('E');
		BSP_SSDPinStatusControl('F');
	}
	else if(displayChar == '1'){
		BSP_SSDPinStatusControl('B');
		BSP_SSDPinStatusControl('C');
	}
	else if(displayChar == '2'){
		BSP_SSDPinStatusControl('A');
		BSP_SSDPinStatusControl('B');
		BSP_SSDPinStatusControl('G');
		BSP_SSDPinStatusControl('E');
		BSP_SSDPinStatusControl('D');
	}
	else if(displayChar == '3'){
		BSP_SSDPinStatusControl('A');
		BSP_SSDPinStatusControl('B');
		BSP_SSDPinStatusControl('G');
		BSP_SSDPinStatusControl('C');
		BSP_SSDPinStatusControl('D');
	}
	else if(displayChar == '4'){
		BSP_SSDPinStatusControl('F');
		BSP_SSDPinStatusControl('G');
		BSP_SSDPinStatusControl('B');
		BSP_SSDPinStatusControl('C');
	}
	else if(displayChar == '5'){
		BSP_SSDPinStatusControl('A');
		BSP_SSDPinStatusControl('F');
		BSP_SSDPinStatusControl('G');
		BSP_SSDPinStatusControl('C');
		BSP_SSDPinStatusControl('D');
	}
	else if(displayChar == '6'){
		BSP_SSDPinStatusControl('A');
		BSP_SSDPinStatusControl('F');
		BSP_SSDPinStatusControl('G');
		BSP_SSDPinStatusControl('E');
		BSP_SSDPinStatusControl('D');
		BSP_SSDPinStatusControl('C');
	}
	else if(displayChar == '7'){
		BSP_SSDPinStatusControl('A');
		BSP_SSDPinStatusControl('B');
		BSP_SSDPinStatusControl('C');
	}
	else if(displayChar == '8'){
		BSP_SSDPinStatusControl('A');
		BSP_SSDPinStatusControl('B');
		BSP_SSDPinStatusControl('C');
		BSP_SSDPinStatusControl('D');
		BSP_SSDPinStatusControl('E');
		BSP_SSDPinStatusControl('F');
		BSP_SSDPinStatusControl('G');
	}
	else if(displayChar == '9'){
		BSP_SSDPinStatusControl('A');
		BSP_SSDPinStatusControl('B');
		BSP_SSDPinStatusControl('C');
		BSP_SSDPinStatusControl('D');
		BSP_SSDPinStatusControl('F');
		BSP_SSDPinStatusControl('G');
	}
	else if(displayChar == '.'){
		BSP_SSDPinStatusControl('d');
	}
}

void BSP_SSDPinStatusControl(char controlPin){
	if(controlPin == 'A'){
		if(ssdPins.AStatus == 'D'){
			if((ssdPins.APin == 2) | (ssdPins.APin == 4) | (ssdPins.APin == 5) | (ssdPins.APin == 9))
				GPIOA->ODR &= (1U << ssdPins.APin);
			else
				GPIOB->ODR &= (1U << ssdPins.APin);
		}
		else if (ssdPins.AStatus == 'A')
			GPIOA->ODR &= (1U << ssdPins.APin);
	}
	else if(controlPin == 'B'){
		if(ssdPins.BStatus == 'D'){
			if((ssdPins.BPin == 2) | (ssdPins.BPin == 4) | (ssdPins.BPin == 5) | (ssdPins.BPin == 9))
				GPIOA->ODR &= (1U << ssdPins.BPin);
			else
				GPIOB->ODR &= (1U << ssdPins.BPin);
		}
		else if (ssdPins.BStatus == 'A')
			GPIOA->ODR &= (1U << ssdPins.BPin);
	}
	else if(controlPin == 'C'){
		if(ssdPins.CStatus == 'D'){
			if((ssdPins.CPin == 2) | (ssdPins.CPin == 4) | (ssdPins.CPin == 5) | (ssdPins.CPin == 9))
				GPIOA->ODR &= (1U << ssdPins.CPin);
			else
				GPIOB->ODR &= (1U << ssdPins.CPin);
		}
		else if (ssdPins.CStatus == 'A')
			GPIOA->ODR &= (1U << ssdPins.CPin);
	}
	else if(controlPin == 'D'){
		if(ssdPins.DStatus == 'D'){
			if((ssdPins.DPin == 2) | (ssdPins.DPin == 4) | (ssdPins.DPin == 5) | (ssdPins.DPin == 9))
				GPIOA->ODR &= (1U << ssdPins.DPin);
			else
				GPIOB->ODR &= (1U << ssdPins.DPin);
		}
		else if (ssdPins.DStatus == 'A')
			GPIOA->ODR &= (1U << ssdPins.DPin);
	}
	else if(controlPin == 'E'){
		if(ssdPins.EStatus == 'D'){
			if((ssdPins.EPin == 2) | (ssdPins.EPin == 4) | (ssdPins.EPin == 5) | (ssdPins.EPin == 9))
				GPIOA->ODR &= (1U << ssdPins.EPin);
			else
				GPIOB->ODR &= (1U << ssdPins.EPin);
		}
		else if (ssdPins.EStatus == 'A')
			GPIOA->ODR &= (1U << ssdPins.EPin);
	}
	else if(controlPin == 'F'){
		if(ssdPins.FStatus == 'D'){
			if((ssdPins.FPin == 2) | (ssdPins.FPin == 4) | (ssdPins.FPin == 5) | (ssdPins.FPin == 9))
				GPIOA->ODR &= (1U << ssdPins.FPin);
			else
				GPIOB->ODR &= (1U << ssdPins.FPin);
		}
		else if (ssdPins.FStatus == 'A')
			GPIOA->ODR &= (1U << ssdPins.FPin);
	}
	else if(controlPin == 'G'){
		if(ssdPins.GStatus == 'D'){
			if((ssdPins.GPin == 2) | (ssdPins.GPin == 4) | (ssdPins.GPin == 5) | (ssdPins.GPin == 9))
				GPIOA->ODR &= (1U << ssdPins.GPin);
			else
				GPIOB->ODR &= (1U << ssdPins.GPin);
		}
		else if (ssdPins.GStatus == 'A')
			GPIOA->ODR &= (1U << ssdPins.GPin);
	}
	else if(controlPin == 'd'){
		if(ssdPins.dStatus == 'D'){
			if((ssdPins.dPin == 2) | (ssdPins.dPin == 4) | (ssdPins.dPin == 5) | (ssdPins.dPin == 9))
				GPIOA->ODR &= (1U << ssdPins.dPin);
			else
				GPIOB->ODR &= (1U << ssdPins.dPin);
		}
		else if (ssdPins.dStatus == 'A')
			GPIOA->ODR &= (1U << ssdPins.dPin);
	}
}

void BSP_DigitEnable(int digit, char *digitStatus){
	if(firstSet == 0){
		firstSet = 1;
		if(ssdPins.D1Status == 'D'){
			if((ssdPins.D1Pin == 2) | (ssdPins.D1Pin == 4) | (ssdPins.D1Pin == 5) | (ssdPins.D1Pin == 9))
				GPIOA->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D1Pin);
			else
				GPIOB->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D1Pin);
		}
		else if (ssdPins.D1Status == 'A')
			GPIOA->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D1Pin);

		if(ssdPins.D2Status == 'D'){
			if((ssdPins.D2Pin == 2) | (ssdPins.D2Pin == 4) | (ssdPins.D2Pin == 5) | (ssdPins.D2Pin == 9))
				GPIOA->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D2Pin);
			else
				GPIOB->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D2Pin);
		}
		else if (ssdPins.D2Status == 'A')
			GPIOA->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D2Pin);

		if(ssdPins.D3Status == 'D'){
			if((ssdPins.D3Pin == 2) | (ssdPins.D3Pin == 4) | (ssdPins.D3Pin == 5) | (ssdPins.D3Pin == 9))
				GPIOA->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D3Pin);
			else
				GPIOB->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D3Pin);
		}
		else if (ssdPins.D3Status == 'A')
			GPIOA->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D3Pin);

		if(ssdPins.D4Status == 'D'){
			if((ssdPins.D4Pin == 2) | (ssdPins.D4Pin == 4) | (ssdPins.D4Pin == 5) | (ssdPins.D4Pin == 9))
				GPIOA->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D4Pin);
			else
				GPIOB->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D4Pin);
		}
		else if (ssdPins.D4Status == 'A')
			GPIOA->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D4Pin);
	}
	if(digitStatus == "on"){
		if(digit == 1){
			if(ssdPins.D1Status == 'D'){
				if((ssdPins.D1Pin == 2) | (ssdPins.D1Pin == 4) | (ssdPins.D1Pin == 5) | (ssdPins.D1Pin == 9)){
					GPIOA->ODR &= (ssdPins.SSDEnableDigitBit << ssdPins.D1Pin);
				}
				else{
					GPIOB->ODR &= (ssdPins.SSDEnableDigitBit << ssdPins.D1Pin);
				}
			}
			else if (ssdPins.D1Status == 'A'){
				GPIOA->ODR &= (ssdPins.SSDEnableDigitBit << ssdPins.D1Pin);
			}
		}
		else if(digit == 2){
			if(ssdPins.D2Status == 'D'){
				if((ssdPins.D2Pin == 2) | (ssdPins.D2Pin == 4) | (ssdPins.D2Pin == 5) | (ssdPins.D2Pin == 9)){
					GPIOA->ODR &= (ssdPins.SSDEnableDigitBit << ssdPins.D2Pin);
				}
				else{
					GPIOB->ODR &= (ssdPins.SSDEnableDigitBit << ssdPins.D2Pin);
				}
			}
			else if (ssdPins.D2Status == 'A'){
				GPIOA->ODR &= (ssdPins.SSDEnableDigitBit << ssdPins.D2Pin);
			}
		}
		else if(digit == 3){
			if(ssdPins.D3Status == 'D'){
				if((ssdPins.D3Pin == 2) | (ssdPins.D3Pin == 4) | (ssdPins.D3Pin == 5) | (ssdPins.D3Pin == 9)){
					GPIOA->ODR &= (ssdPins.SSDEnableDigitBit << ssdPins.D3Pin);
				}
				else{
					GPIOB->ODR &= (ssdPins.SSDEnableDigitBit << ssdPins.D3Pin);
				}
			}
			else if (ssdPins.D3Status == 'A'){
				GPIOA->ODR &= (ssdPins.SSDEnableDigitBit << ssdPins.D3Pin);
			}
		}
		else if(digit == 4){
			if(ssdPins.D4Status == 'D'){
				if((ssdPins.D4Pin == 2) | (ssdPins.D4Pin == 4) | (ssdPins.D4Pin == 5) | (ssdPins.D4Pin == 9)){
					GPIOA->ODR &= (ssdPins.SSDEnableDigitBit << ssdPins.D4Pin);
				}
				else{
					GPIOB->ODR &= (ssdPins.SSDEnableDigitBit << ssdPins.D4Pin);
				}
			}
			else if (ssdPins.D4Status == 'A'){
				GPIOA->ODR &= (ssdPins.SSDEnableDigitBit << ssdPins.D4Pin);
			}
		}
	}
	else if(digitStatus == "off"){
		if(digit == 1){
			if(ssdPins.D1Status == 'D'){
				if((ssdPins.D1Pin == 2) | (ssdPins.D1Pin == 4) | (ssdPins.D1Pin == 5) | (ssdPins.D1Pin == 9)){
					GPIOA->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D1Pin);
				}
				else{
					GPIOB->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D1Pin);
				}
			}
			else if (ssdPins.D1Status == 'A'){
				GPIOA->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D1Pin);
			}
		}
		else if(digit == 2){
			if(ssdPins.D2Status == 'D'){
				if((ssdPins.D2Pin == 2) | (ssdPins.D2Pin == 4) | (ssdPins.D2Pin == 5) | (ssdPins.D2Pin == 9)){
					GPIOA->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D2Pin);
				}
				else{
					GPIOB->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D2Pin);
				}
			}
			else if (ssdPins.D2Status == 'A'){
				GPIOA->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D2Pin);
			}
		}
		else if(digit == 3){
			if(ssdPins.D3Status == 'D'){
				if((ssdPins.D3Pin == 2) | (ssdPins.D3Pin == 4) | (ssdPins.D3Pin == 5) | (ssdPins.D3Pin == 9)){
					GPIOA->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D3Pin);
				}
				else{
					GPIOB->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D3Pin);
				}
			}
			else if (ssdPins.D3Status == 'A'){
				GPIOA->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D3Pin);
			}
		}
		else if(digit == 4){
			if(ssdPins.D4Status == 'D'){
				if((ssdPins.D4Pin == 2) | (ssdPins.D4Pin == 4) | (ssdPins.D4Pin == 5) | (ssdPins.D4Pin == 9)){
					GPIOA->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D4Pin);
				}
				else{
					GPIOB->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D4Pin);
				}
			}
			else if (ssdPins.D4Status == 'A'){
				GPIOA->ODR &= (ssdPins.SSDDisableDigitBit << ssdPins.D4Pin);
			}
		}
	}
}

void BSP_SSDTypeSet(char SSDType){
	if(SSDType == 'A'){
		ssdPins.SSDType = SSDType;
		ssdPins.SSDEnableDigitBit = 1;
		ssdPins.SSDDisableDigitBit = 0;
	}
	else if(SSDType == 'C'){
		ssdPins.SSDType = SSDType;
		ssdPins.SSDEnableDigitBit = 0;
		ssdPins.SSDDisableDigitBit = 1;
	}
}
