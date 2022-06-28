
#include "stm32g0xx.h"
#include "BSP.h"
#include "system_stm32g0xx.h"


#define SYSTEM_CLK  16000000
#define EEPROM_ADRESS_1 	0x50
#define EEPROM_ADRESS_2 	0x51

enum state_Type{START, IDLE, FULL, RECORD, PLAYBACK, STATUS};
enum keypad_Type{ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, A, B, C, D, HASTAG, STAR};

volatile enum state_Type mod = START;
volatile enum keypad_Type button; //variable to hold keypad button value

volatile uint8_t avaliable_tracks = 0;
volatile uint8_t seconds; //variable to count how many seconds passed for record mode
volatile uint8_t selected_track = 0;


//button flags
volatile uint8_t record_flag = 0;
volatile uint8_t delete_flag = 0;


void start(){//ssd start mod

	static uint8_t digits = 1;

		switch(digits){
		case 1:
			reset_digits();
			GPIOA->ODR &= ~(1U << 11);	// open first digit
			print_digit(1);
			digits ++;
			break;
		case 2:
			reset_digits();
			GPIOA->ODR &= ~(1U << 12);	// open second digit
			print_digit(9);
			digits ++;

			break;
		case 3:
			reset_digits();
			GPIOA->ODR &= ~(1U << 5);	//open third digit
			print_digit(3);
			digits ++;
			break;
		case 4:
			reset_digits();
			GPIOB->ODR &= ~(1U << 9);	//open fourth digit
			print_digit(9);
			digits = 1;
			break;
		}
}


void idle(){//ssd idle mod

	static uint8_t digits = 1;

		switch(digits){
		case 1:
			reset_digits();
			GPIOA->ODR &= ~(1U << 11);	// open first digit
			print_digit(1);//I
			digits ++;
			break;
		case 2:
			reset_digits();
			GPIOA->ODR &= ~(1U << 12);	// open second digit
			print_digit(22);//d
			digits ++;

			break;
		case 3:
			reset_digits();
			GPIOA->ODR &= ~(1U << 5);	//open third digit
			print_digit(23);//L
			digits ++;
			break;
		case 4:
			reset_digits();
			GPIOB->ODR &= ~(1U << 9);	//open fourth digit
			print_digit(13);//E
			digits = 1;
			break;
		}

}

void full(){//ssd full
	static uint8_t digits = 1;

		switch(digits){
		case 1:
			reset_digits();
			GPIOA->ODR &= ~(1U << 11);	// open first digit
			print_digit(25);//F
			digits ++;
			break;
		case 2:
			reset_digits();
			GPIOA->ODR &= ~(1U << 12);	// open second digit
			print_digit(26);//u
			digits ++;

			break;
		case 3:
			reset_digits();
			GPIOA->ODR &= ~(1U << 5);	//open third digit
			print_digit(23);//L
			digits ++;
			break;
		case 4:
			reset_digits();
			GPIOB->ODR &= ~(1U << 9);	//open fourth digit
			print_digit(23);//L
			digits = 1;
			break;
		}

}

void record(){// ssd record
	static uint8_t digits = 1;

		switch(digits){
		case 1:
			reset_digits();
			GPIOA->ODR &= ~(1U << 11);	// open first digit
			print_digit(16);//r
			digits ++;
			break;
		case 2:
			reset_digits();
			GPIOA->ODR &= ~(1U << 12);	// open second digit
			print_digit(12);//c
			digits ++;

			break;
		case 3:
			reset_digits();
			GPIOA->ODR &= ~(1U << 5);	//open third digit
			print_digit(22);//d
			digits ++;
			break;
		case 4:
			reset_digits();
			GPIOB->ODR &= ~(1U << 9);	//open fourth digit
			print_digit(seconds);
			digits = 1;
			break;
		}

}

void playback(){

	static uint8_t digits = 1;

			switch(digits){
			case 1:
				reset_digits();
				GPIOA->ODR &= ~(1U << 11);	// open first digit
				print_digit(21);//p
				digits ++;
				break;
			case 2:
				reset_digits();
				GPIOA->ODR &= ~(1U << 12);	// open second digit
				print_digit(23);//L
				digits ++;

				break;
			case 3:
				reset_digits();
				GPIOA->ODR &= ~(1U << 5);	//open third digit
				print_digit(27);//b
				digits ++;
				break;
			case 4:
				reset_digits();
				GPIOB->ODR &= ~(1U << 9);	//open fourth digit
				print_digit(selected_track);
				digits = 1;
				break;
			}

}

void status(){


	static uint8_t digits = 1;

			switch(digits){
			case 1:
				reset_digits();
				GPIOA->ODR &= ~(1U << 11);	// open first digit
				print_digit(11);//A
				digits ++;
				break;
			case 2:
				reset_digits();
				GPIOA->ODR &= ~(1U << 12);	// open second digit
				print_digit(26);//v
				digits ++;

				break;
			case 3:
				reset_digits();
				GPIOA->ODR &= ~(1U << 5);	//open third digit
				print_digit(11);//A
				digits ++;
				break;
			case 4:
				reset_digits();
				GPIOB->ODR &= ~(1U << 9);	//open fourth digit
				print_digit(avaliable_tracks);
				digits = 1;
				break;
			}
}





void EXTI2_3_IRQHandler(void)//interrupt function for keypads first and last columns
{

	//reset ssd pins to have a clear look
	GPIOA->ODR |= (1U << 11);	//set  a5
	GPIOA->ODR |= (1U << 12);	//set  a4
	GPIOA->ODR |= (1U << 5);	//set  a3
	GPIOB->ODR |= (1U << 9);	//set  d10

	/*handles first and last columns*/


	GPIOB->ODR &= ~(1U << 9);	//reset  d10

	if((GPIOB->IDR >> 3) & 1){
		clear_rows_keypad();
		//try for each keypad rows

		GPIOB->ODR |= (1U << 6); //keypad A button
		if((GPIOB->IDR >> 3) & 1){

			button = A;

			delay_ms(600); //little bit delay for debouncing


		}


		GPIOB->ODR &= ~(1U << 6); //close first row


		GPIOB->ODR |= (1U << 7); //keypad B button
		if((GPIOB->IDR >> 3) & 1){

			button = B;
			delay_ms(600); //little bit delay for debouncing

		}


		GPIOB->ODR &= ~(1U << 7); //close second row



		GPIOA->ODR |= (1U << 15); //keypad C button
		if((GPIOB->IDR >> 3) & 1){

			button = C;
			delay_ms(600); //little bit delay for debouncing

		}


		GPIOA->ODR &= ~(1U << 15); //close third row



		GPIOB->ODR |= (1U << 1); //keypad D button
		if((GPIOB->IDR >> 3) & 1){

			button = D;
			delay_ms(600); //little bit delay for debouncing

		}


		GPIOB->ODR &= ~(1U << 1); //close fourth row


		EXTI-> RPR1 |= (1 << 3); //clear pending bit
		set_rows_keypad();
	}





	if((GPIOB->IDR >> 2) & 1){
		clear_rows_keypad();
		//try for each keypad rows

		GPIOB->ODR |= (1U << 6);  //keypad 1 button
		if((GPIOB->IDR >> 2) & 1){

			button = ONE;
			selected_track = 1;
			delay_ms(600); //little bit delay for debouncing
		}


		GPIOB->ODR &= ~(1U << 6); //close first row

		GPIOB->ODR |= (1U << 7);  //keypad 4 button
		if((GPIOB->IDR >> 2) & 1){

			button = FOUR;
			 selected_track = 4;
			delay_ms(600); //little bit delay for debouncing
		}
		GPIOB->ODR &= ~(1U << 7); //close second row
		GPIOA->ODR |= (1U << 15); //keypad 7 button
		if((GPIOB->IDR >> 2) & 1){

			button = SEVEN;
			delay_ms(600); //little bit delay for debouncing
		}
		GPIOA->ODR &= ~(1U << 15); //close third row
		GPIOB->ODR |= (1U << 1);  //keypad * button
		if((GPIOB->IDR >> 2) & 1){

			button = STAR;
			delay_ms(600); //little bit delay for debouncing
		}

		GPIOB->ODR &= ~(1U << 1); //close fourth row

		EXTI-> RPR1 |= (1 << 2); //clear pending bit
		set_rows_keypad();
	}
}

void EXTI0_1_IRQHandler(void)//interrupt function for keypads second and third columns
{
	//reset ssd pins to have a clear look
	GPIOA->ODR |= (1U << 11);	//set  a5
	GPIOA->ODR |= (1U << 12);	//set  a4
	GPIOA->ODR |= (1U << 5);	//set  a3
	GPIOB->ODR |= (1U << 9);	//set  d10

	/*handles second and third columns*/
	GPIOB->ODR &= ~(1U << 9);	//reset  d10

	if((GPIOB->IDR >> 0) & 1){
		clear_rows_keypad();
		//try for each keypad rows

		GPIOB->ODR |= (1U << 6);  //keypad 3 button
		if((GPIOB->IDR >> 0) & 1){
			button = THREE;
			selected_track = 3;
			delay_ms(600); //little bit delay for debouncing
		}
		GPIOB->ODR &= ~(1U << 6); //close first row

		GPIOB->ODR |= (1U << 7);  //keypad 6 button
		if((GPIOB->IDR >> 0) & 1){

			button = SIX;
			delay_ms(600); //little bit delay for debouncing
		}
		GPIOB->ODR &= ~(1U << 7); //close second row
		GPIOA->ODR |= (1U << 15);  //keypad 9 button
		if((GPIOB->IDR >> 0) & 1){
			button = NINE;
			delay_ms(600); //little bit delay for debouncing
		}
		GPIOA->ODR &= ~(1U << 15); //close third row
		GPIOB->ODR |= (1U << 1);  //keypad # button
		if((GPIOB->IDR >> 0) & 1){

			button = HASTAG;
			delay_ms(600); //little bit delay for debouncing
		}
		GPIOB->ODR &= ~(1U << 1); //close fourth row

		EXTI-> RPR1 |= (1 << 0); //clear pending bit
		set_rows_keypad();
	}

	if((GPIOA->IDR >> 1) & 1){
		clear_rows_keypad();
		//try for each keypad rows

		GPIOB->ODR |= (1U << 6);  //keypad 2 button
		if((GPIOA->IDR >> 1) & 1){

			button = TWO;
			selected_track = 2;
			delay_ms(600); //little bit delay for debouncing
		}

		GPIOB->ODR &= ~(1U << 6); //close first row
		GPIOB->ODR |= (1U << 7);  //keypad 5 button

		if((GPIOA->IDR >> 1) & 1){

			button = FIVE;
			delay_ms(600); //little bit delay for debouncing
		}
		GPIOB->ODR &= ~(1U << 7); //close second row

		GPIOA->ODR |= (1U << 15);  //keypad 8 button
		if((GPIOA->IDR >> 1) & 1){

			button = EIGHT;
			delete_flag = 1;
			delay_ms(600); //little bit delay for debouncing

		}

		GPIOA->ODR &= ~(1U << 15); //close third row

		GPIOB->ODR |= (1U << 1);  //keypad 0 button
		if((GPIOA->IDR >> 1) & 1){

			button = ZERO;
			seconds = 5;//set the record time at 5 seconds
			record_flag = 1;
			delay_ms(600); //little bit delay for debouncing
		}
		GPIOB->ODR &= ~(1U << 1); //close fourth row

		EXTI-> RPR1 |= (1 << 1); //clear pending bit
		set_rows_keypad();
	}
}

void TIM3_IRQHandler(){

	seconds--;
	if(seconds <= 0 && button == ZERO){


		mod = IDLE;
		//stop the ADC
		ADC1 -> CR |= (1U << 4);
		ADC1 -> CR &= ~(1U << 2);

		TIM3->CR1 &= ~(1U << 0); // disable the timer
		NVIC_DisableIRQ(TIM3_IRQn);//if seconds is zero, stop counting
	}

	TIM3->SR &= ~(1U << 0);
}

void TIM2_IRQHandler(void) {
    // update duty (CCR1)

    // Clear update status register
		TIM2->SR &= ~(1U << 0);
}

void TIM1_BRK_UP_TRG_COM_IRQHandler(void){
	//ssd timer
	switch(mod){
	case START:
		start();
		break;

	case IDLE:
		idle();
		break;

	case FULL:
		full();
		break;

	case RECORD:
		record();
		break;

	case PLAYBACK:
		playback();
		break;

	case STATUS:
		status();
		break;
	}
	TIM1->SR &= ~(1U << 0);
}

void init_pwm(){

	   // Enable GPIOB clock
		    RCC->IOPENR |= (1U << 1);
		    // Enable TIM2 clock
		    RCC->APBENR1 |= RCC_APBENR1_TIM2EN;

		    // Set alternate function to 2
		    // 3 comes from PB3
		    GPIOB->AFR[0] |= (2U << 4*3);
		    // Select AF from Moder
		    GPIOB->MODER &= ~(3U << 2*3);
		    GPIOB->MODER |= (2U << 2*3);

		    // zero out the control register just in case
		    TIM2->CR1 = 0;

		    // Select PWM Mode 1
		    TIM2->CCMR1 |= (6U << 12);
		    // Preload Enable
		    TIM2->CCMR1 |= TIM_CCMR1_OC2PE;

		    // Capture compare ch2 enable
		    TIM2->CCER |= TIM_CCER_CC2E;

		    // zero out counter
		    TIM2->CNT = 0;
		    // fast signal
		    TIM2->PSC = 10;
		    TIM2->ARR = 10;

		    // zero out duty
		    TIM2->CCR2 = 0;

		    // Update interrupt enable
		    TIM2->DIER |= (1 << 0);

		    // TIM1 Enable
		    TIM2->CR1 |= TIM_CR1_CEN;

		    NVIC_SetPriority(TIM2_IRQn, 3);
		   // NVIC_EnableIRQ(TIM2_IRQn);
}

void init_tim1(){

	RCC->APBENR2 |= (1U << 11); //Enable tim1 module clock
	TIM1->CR1 = 0; //zero out the control register just incase
	TIM1->CR1 |= (1 << 7); //preload enable
	TIM1->CNT = 0; //zero out the counter

	//1ms interrupt
	TIM1->PSC = 310;
	TIM1->ARR = 100;

	TIM1->DIER |= (1 << 0);
	TIM1->CR1 |= (1 << 0); // enable the timer

	//set interrpts
	NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 3);
	NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
}

void init_tim3(){
	RCC->APBENR1 |= (1U << 1); //Enable tim1 module clock
	TIM3->CR1 = 0; //zero out the control register just incase
	TIM3->CR1 |= (1 << 7); //preload enable
	TIM3->CNT = 0; //zero out the counter

	//1s interrupt
	TIM3->PSC = 16000;
	TIM3->ARR = 1000;

	TIM3->DIER |= (1 << 0);
	TIM3->CR1 |= (1 << 0); // enable the timer

	//set interrpts
	NVIC_SetPriority(TIM3_IRQn, 3);
	//NVIC_EnableIRQ(TIM3_IRQn);
}

void init_ADC(){
	//set A0 as analog mode
	setMode('A',0,'A');

	//open ADC clock
	RCC->APBENR2 |= (1U << 20);

	//ADC struct is defined for common mode, we have to use ADC1 struct to change ADC register

//disable the ADC as initial just in case
 // this fields are probably zero as initial, it is not mandatory to assign them zero

	ADC1->CR &= ~(1U << 0); // disable the ADC enable bit ADEN
	ADC1->CR &= ~(1U << 1); // disable ADDIS
	ADC1->CR &= ~(1U << 2); // disable ADSTART
	ADC1->CR &= ~(1U << 4); // disable ADSTP
	ADC1->CR &= ~(1U << 31); // disable ADCAL

	//open ADC voltage regulator enable bit
	ADC1->CR |= (1U << 28);
	delay_ms(1); //1ms delay for wait to regulator to regulate the voltage (20 us should be fine, no need to 1ms)

	//do the ADC calibration ADC calibration
	ADC1->CR |= (1U << 31);
	while(ADC1->CR == (9U << 28));//wait until calibration is done
	ADC1->IER |= (1U << 11); //enable end of the calibration interrupt register (EOCALIE)

	//set the resolution
	//since eeproms has a small capacity of data, i choose 256 bytes resolution for storage optimization
	ADC1->CFGR1 |= (2U << 3); //set the ADC resolution as 10 bits (max 1023)(CFGR->RES register (10))

	//configure to continuous mode
	ADC1->CFGR1 &= ~(1U << 16);//disable discontinuous mode if its opened before just in case
	ADC1->CFGR1 |= (1U << 13);

	//configure sampling rates
	ADC1->SMPR |= (5U << 0);// set the sampling rate 110 mode (sample per 79.5 clock cycles)
	ADC1->SMPR &= ~(1U << 8);//set smpsel1 register which we're just configured

	//Enable the channels
	ADC1->CHSELR |= (1U << 0);//select channel A1 to read

	ADC1->CR |= (1U << 0); // enable ADC
	while(((ADC1->CR)>>0)  == (1U));
	//ADC1 -> CR |= (1U << 2);//ADSTAR1 for ADC
	ADC1 -> CR |= (1U << 4);//ADSTOP for ADC stop the adc as initial
}

void voice_Recorder(){  //function to handle the modes


	switch(button){
	case ZERO:
		//if keypad button 0 is pressed, record a track
		if(record_flag == 1){

		if(avaliable_tracks >= 4){
			mod = FULL;
			break; //if the tracks are full, don't record anything
		}
		//disable keypad interrupts while recording a track
		NVIC_DisableIRQ(EXTI2_3_IRQn);
		NVIC_DisableIRQ(EXTI0_1_IRQn);
		NVIC_EnableIRQ(TIM3_IRQn);

		//start the ADC
		ADC1 -> CR &= ~(1U << 4);
		ADC1 -> CR |= (1U << 2);

		TIM3->CR1 |= (1U << 0); // enable the timer

		avaliable_tracks ++;
		mod = RECORD;


		//enable keypad again
	    NVIC_EnableIRQ(EXTI0_1_IRQn);
	    NVIC_EnableIRQ(EXTI2_3_IRQn);

	    record_flag = 0;
		}
		break;
	case EIGHT:
		//if keypad button 8 is pressed, delete a track

		if(avaliable_tracks > 0 && delete_flag == 1){
			avaliable_tracks --;
			delete_flag = 0;
		}
		break;

	case STAR:
		//if keypad button * is pressed, pause the track
		break;
	case HASTAG:
		mod = STATUS;
		break;
	case NINE://button 9 is for play the track
		mod = PLAYBACK;
		break;
	default:
		if(mod != START){
		mod = IDLE;
		}
		break;
	}
}

int main(void) {
	init_systick(SystemCoreClock/1000);

	/*open clocks*/
	openClock('A');
	openClock('B');

	init_SSD();

	/*configure keypad*/
	//rows are output, columns are input
	config_keypad_pins();//configure the pins
	config_keypad_IRQs();//configure the interrupts

	init_tim1();
	init_tim3();
	init_ADC();
	init_I2C();

while(1){
	voice_Recorder();

}

return 0;
}
