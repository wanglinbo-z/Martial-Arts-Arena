#ifndef __TIMER_H
#define __TIMER_H

void Timer_Init(void);

uint8_t Timer_GetFPS(void);				//��ȡ֡��
void Timer_SetFreqCounter(void);		//���ü�����
uint8_t Timer_GetFreqCounter(void);		//��ȡƵ��

#endif
