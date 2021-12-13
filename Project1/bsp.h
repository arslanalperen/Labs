#ifndef BSP_H_
#define BSP_H_

#include "stm32g0xx.h"
#include "string.h"
#include "stdbool.h"

struct ssdPins{
	char D1Status;int D1Pin;
	char D2Status;int D2Pin;
	char D3Status;int D3Pin;
	char D4Status;int D4Pin;
	char dStatus;int dPin;
	char AStatus;int APin;
	char BStatus;int BPin;
	char CStatus;int CPin;
	char DStatus;int DPin;
	char EStatus;int EPin;
	char FStatus;int FPin;
	char GStatus;int GPin;
	char SSDType;
	bool SSDEnableDigitBit;
	bool SSDDisableDigitBit;
}ssdPins;

void BSP_init();

void delay(volatile unsigned int s);

void BSP_led_init();
void BSP_led_set();
void BSP_led_reset();
void BSP_led_toggle();

void BSP_button_init();
int BSP_button_read();

void init_timer1();

void BSP_SetSSD(char pinStatus, int pinNumber, char *ssdPin);
void BSP_SetDigitalPins(int pinNumber);
void BSP_SetAnalogPins(int pinNumber);
void BSP_DisplaySSD(int digit, char displayChar);
void BSP_SSDPinStatusControl(char controlPin);
void BSP_DigitEnable(int digit, char *digitStatus);
void BSP_SSDTypeSet(char SSDType);

#endif /* BSP_H_ */
