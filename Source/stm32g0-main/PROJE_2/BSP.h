/*
 * BSP.h
 *
 *  Created on: 28 Kas 2021
 *      Author: Alpeten
 */
#include "stm32g0xx.h"
#include "system_stm32g0xx.h"

#ifndef BSP_H_
#define BSP_H_

#define LEDDELAY 1600000

#define KEY1   0x45670123
#define KEY2   0xCDEF89AB


#if !defined  (HSE_VALUE)
#define HSE_VALUE    (8000000UL)    /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSI_VALUE)
  #define HSI_VALUE  (16000000UL)   /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

#define PLL_M 	1U
#define PLL_N 	8U
#define PLL_P 	7U
#define PLL_Q 	2U
#define PLL_L 	2U




extern uint32_t SystemCoreClock;






/*COOL FUNCTIONS*/
void openClock(char port);
void setMode(char port, uint32_t num,char IO);

/*onboard led functions*/
void configureOnboardLed();
void toggleOnboardLed();
void turnOnOnboardLed();
void turnOffOnboardLed();

/*onboard button functions*/
void unlockFlash();
void lockFlash();
void configureOnboardButton();
int readOnboardButton();


/*clock configure functions*/
void set_sysclk_to_hse();
void set_sysclk_to_hsi();
void set_sysclk_to_84();


/*INTERRUPTS*/
void EXT0_1_IRQHandler();
void EXT2_3_IRQHandler();
void EXT4_15_IRQHandler();
void configure_A0_int();

/*SYSTICK functions*/
void SysTick_Handler();
void init_systick(uint32_t s);


void delay(volatile uint32_t s);
void delay_ms(uint32_t s);



/*SSD functions*/
void init_SSD();
void print_digit(volatile uint32_t dig);
void ssd_output(uint32_t x);
void reset_segments();
void reset_digits();

/*keypad functions*/
void config_keypad_pins();
void config_keypad_IRQs();
void clear_rows_keypad();
void set_rows_keypad();

/*communication functions*/
void init_I2C();
void read_I2C(uint8_t devAddr,uint8_t* data,int Size);
void write_I2C(uint8_t devAddr,uint8_t* data, int Size);
void write_memory_I2C(uint8_t devAddr,uint16_t memAddr,uint8_t* data, int Size);
void random_read_I2C(uint8_t devAddr,uint16_t memAddr,uint8_t* data,int Size);



#endif /* BSP_H_ */
