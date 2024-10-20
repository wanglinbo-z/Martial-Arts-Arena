#ifndef __LED_H
#define __LED_H

#define LED_GPIO_PORT GPIOC
#define LED_GPIO_PIN GPIO_Pin_7

#define digitalTOGGLE(p,i)	{p->ODR ^= i;}
#define LED_TOGGLE			digitalTOGGLE(LED_GPIO_PORT,LED_GPIO_PIN)
#define LED_ON				{LED_GPIO_PORT->BRR = LED_GPIO_PIN;}
#define LED_OFF				{LED_GPIO_PORT->BSRR = LED_GPIO_PIN;}


void LED_Init(void);

#endif
