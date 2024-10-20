#include "stm32f10x.h"                  // Device header

struct {uint16_t Value; uint16_t Count;} FreqCounter = {0, 0};	//֡����ؽṹ�岢ֱ��ʵ����


/**
  * ��    ������ʱ�жϳ�ʼ��
  * ��    ������
  * �� �� ֵ����
  */
void Timer_Init(void)
{
	/*����ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);			//����TIM4��ʱ��
	
	/*����ʱ��Դ*/
	TIM_InternalClockConfig(TIM4);		//ѡ��TIM4Ϊ�ڲ�ʱ�ӣ��������ô˺�����TIMĬ��ҲΪ�ڲ�ʱ��
	
	/*ʱ����Ԫ��ʼ��*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//����ṹ�����
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//ʱ�ӷ�Ƶ��ѡ�񲻷�Ƶ���˲������������˲���ʱ�ӣ���Ӱ��ʱ����Ԫ����
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//������ģʽ��ѡ�����ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;				//�������ڣ���ARR��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;				//Ԥ��Ƶ������PSC��ֵ
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;			//�ظ����������߼���ʱ���Ż��õ�
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);				//���ṹ���������TIM_TimeBaseInit������TIM4��ʱ����Ԫ	
	
	/*�ж��������*/
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);						//�����ʱ�����±�־λ
																//TIM_TimeBaseInit����ĩβ���ֶ������˸����¼�
																//��������˱�־λ�������жϺ󣬻����̽���һ���ж�
																//�������������⣬������˱�־λҲ��
	
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);					//����TIM4�ĸ����ж�
	
	/*NVIC�жϷ���*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//����NVICΪ����2
																//����ռ���ȼ���Χ��0~3����Ӧ���ȼ���Χ��0~3
																//�˷������������������н������һ��
																//���ж���жϣ����԰Ѵ˴������main�����ڣ�whileѭ��֮ǰ
																//�����ö�����÷���Ĵ��룬���ִ�е����ûḲ����ִ�е�����
	
	/*NVIC����*/
	NVIC_InitTypeDef NVIC_InitStructure;						//����ṹ�����
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;				//ѡ������NVIC��TIM4��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//ָ��NVIC��·ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//ָ��NVIC��·����ռ���ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//ָ��NVIC��·����Ӧ���ȼ�Ϊ1
	NVIC_Init(&NVIC_InitStructure);								//���ṹ���������NVIC_Init������NVIC����
	
	/*TIMʹ��*/
	TIM_Cmd(TIM4, ENABLE);			//ʹ��TIM4����ʱ����ʼ����
}

uint8_t Timer_GetFPS(void)			//��ȡ֡��
{
	FreqCounter.Count++;
	return FreqCounter.Value;
}

void Timer_SetFreqCounter(void)		//���ü�����
{
	FreqCounter.Count++;
}

uint8_t Timer_GetFreqCounter(void)	//��ȡ����Ƶ��
{
	return FreqCounter.Value;
}

//	/* ��ʱ���жϺ��������Ը��Ƶ�ʹ�����ĵط�
void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
	{
		FreqCounter.Value = FreqCounter.Count;
		FreqCounter.Count = 0;
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}
//	*/
