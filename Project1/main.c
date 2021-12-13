//main.c
//
//Author: Alperen Arslan
//Description: Changes the mode of the LED by pressing the button.
//At the same time, it shows which mode it is in with a 7-segment display.

#include "bsp.h"

int main(void) {
	BSP_SSDTypeSet('C');

	BSP_SetSSD('D',2,"D1");
	BSP_SetSSD('D',4,"D2");
	BSP_SetSSD('D',5,"D3");
	BSP_SetSSD('D',9,"D4");
	BSP_SetSSD('D',6,"d");
	BSP_SetSSD('D',3,"A");
	BSP_SetSSD('D',7,"B");
	BSP_SetSSD('D',13,"C");
	BSP_SetSSD('D',12,"D");
	BSP_SetSSD('D',11,"E");
	BSP_SetSSD('D',1,"F");
	BSP_SetSSD('D',0,"G");

	BSP_DigitEnable(4,"on");
	BSP_DisplaySSD(4,'2');
}
