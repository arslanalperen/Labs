#ifndef BSP_H_
#define BSP_H_

void BSP_init();

void delay(volatile unsigned int s);

void BSP_led_init();
void BSP_led_set();
void BSP_led_reset();
void BSP_led_toggle();

void BSP_button_init();
int BSP_button_read();

void init_timer1();

void BSP_SetSSD(char *pin);
void BSP_SetDigitalPins(char pinNumber);
void BSP_SetAnalogPins(char pinNumber);
void BSP_DisplaySSD(struct ssdPins *ssdPins);

#endif /* BSP_H_ */
