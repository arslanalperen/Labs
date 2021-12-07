#include "stm32g0xx.h"
#ifndef BSP_H
#define BSP_H

void BSP_RCC_ENABLE(uint32_t bit);
void BSP_GPIOx_MODER(char pin, uint32_t mode);

#endif
