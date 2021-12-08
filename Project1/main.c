//main.c
//
//Author: Alperen Arslan
//Description: Changes the mode of the LED by pressing the button.
//At the same time, it shows which mode it is in with a 7-segment display.

#include "bsp.h"

/*
struct ssdPins{
	char D1[1];char D2[1];char D3[1];char D4[1];char d;
	char A[1];char B[1];char C[1];char D[1];char E[1];char F[1];char G[1];
}ssdPins;
*/

//strcpy(ssdPins.D1,"D2")s;

struct ssdPins{
	char *D1;char *D2;char *D3;char *D4;char *d;
	char *A;char *B;char *C;char *D;char *E;char *F;char *G;
}ssdPins;

int main(void) {
	//SSD pin configuration
	ssdPins.D1 = "D2";
	ssdPins.D2 = "D2";
	ssdPins.D3 = "D2";
	ssdPins.D4 = "D2";
	ssdPins.d = "D2";
	ssdPins.A = "D2";
	ssdPins.B = "D2";
	ssdPins.C = "D2";
	ssdPins.D = "D2";
	ssdPins.E = "D2";
	ssdPins.F = "D2";
	ssdPins.G = "D2";

	BSP_SetSSD(ssdPins.D1);
	BSP_SetSSD(ssdPins.D2);
	BSP_SetSSD(ssdPins.D3);
	BSP_SetSSD(ssdPins.D4);
	BSP_SetSSD(ssdPins.d);
	BSP_SetSSD(ssdPins.A);
	BSP_SetSSD(ssdPins.B);
	BSP_SetSSD(ssdPins.C);
	BSP_SetSSD(ssdPins.D);
	BSP_SetSSD(ssdPins.E);
	BSP_SetSSD(ssdPins.F);
	BSP_SetSSD(ssdPins.G);
}
