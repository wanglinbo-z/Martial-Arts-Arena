#include "Motor.h"
#include "Store.h"

float RSpeedErr_Value;
float LSpeedErr_Value;
float RSpeed;
float LSpeed;

/*
 * PWML1=(PWM) PWML2=1 �����ת
 * PWML1=1 PWML2=(PWM) �����ת
 * PWML1=1 PWML2=1 ���ɲ��
 */
void Motor_PWM_Init(void)
{

	LSpeedErr_Value = (float)(Store_Data[StoreData_LSpeedErr_Value]);
	RSpeedErr_Value = (float)(Store_Data[StoreData_RSpeedErr_Value]);
	RSpeed = 0;
	LSpeed = 0;
	

	/*<- 1.����GPIOΪ�����������  ->*/
	/*******************************************************************/
	// 1�������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// ����GPIO�ṹ��
	GPIO_InitTypeDef GPIO_Motor_PWM;
    
	// 2�����������ʼ���ṹ��
	GPIO_Motor_PWM.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_Motor_PWM.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Motor_PWM.GPIO_Speed = GPIO_Speed_50MHz;
    
	// 3����ʼ��GPIO
	GPIO_Init(GPIOA, &GPIO_Motor_PWM);
	/*******************************************************************/
	
	/*<- 2�����ö�ʱ�����ϼ��������ö�ʱ��Ƶ�� ->*/
	/*******************************************************************/
	/* TIM1 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	TIM_InternalClockConfig(TIM1);
 
	/* Compute the prescaler(PSC) value */
	// uint16_t PrescalerValue = (uint16_t) ((SystemCoreClock) / 2000000) - 1;
	
	// ����TIM_TimeBaseInitTypeDef�ṹ��
 	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 1000-1;						// ARR
	TIM_TimeBaseStructure.TIM_Prescaler = 8; 					// PSC
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	
	// ��ʼ��timebase
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	/*******************************************************************/
	
	/*<-3������PWM���->*/
	/*******************************************************************/
	/* ����TIM_OCInitTypeDef�ṹ��*/
	TIM_OCInitTypeDef  TIM_OCInitStructure;
    
    /* ��ʼ��TIM_OCInitStructure�ṹ�� */
	TIM_OCStructInit(&TIM_OCInitStructure);
	
    /* PWM Mode configuration: Channel1234 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; 								// CCR
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
 
    /* ��ʼ��TIM1_CH1234 */
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	/*******************************************************************/

	/*<-4��ʹ�ܶ�ʱ��->*/
	/*******************************************************************/ 
	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	/*******************************************************************/
}

void Motor_Init(void)
{
    /* PWM Init */
    Motor_PWM_Init();
    Motor_RSpeed(RSpeed);
    Motor_LSpeed(LSpeed);
}

uint16_t LSpeedErr(int16_t Err)
{
	if (Err < 0 || Err > 1000){
		return 1;
	}
	LSpeedErr_Value = Err;
	Store_Data[StoreData_LSpeedErr_Value] = Err;
	Store_Save();
	return 0;
}

uint16_t RSpeedErr(int16_t Err)
{
	if (Err < 0 || Err > 1000){
		return 1;
	}
	RSpeedErr_Value = Err;
	Store_Data[StoreData_RSpeedErr_Value] = Err;
	Store_Save();
	return 0;
}

/*���PWM���ƺ���*/

/**
 * @brief  ���ɲ��
 * 
 */


void Motor_Stop(void)
{
	Motor_RSpeed(0);
	Motor_LSpeed(0);
}

/**
 * @brief  �Ҳ�������
 * @param Speed: -1000~1000
 */
void Motor_RSpeed(int16_t Speed)
{
	RSpeed = Speed;
    if (Speed > 0 && Speed < 1000)
    {
        TIM_SetCompare1(TIM1, Speed);
        TIM_SetCompare2(TIM1, 0);
    }
    else if (Speed < 0 && Speed > -1000)
    {
        TIM_SetCompare1(TIM1, 0);
        TIM_SetCompare2(TIM1, -Speed);
    }
    else if (Speed == 0)
    {
        TIM_SetCompare1(TIM1, 0);
        TIM_SetCompare2(TIM1, 0);
    }
}

/**
 * @brief  ���������
 * @param Speed: -1000~1000
 */
void Motor_LSpeed(int16_t Speed)
{
	LSpeed = Speed;
    if (Speed > 0 && Speed < 1000)
    {
        TIM_SetCompare4(TIM1, Speed);
        TIM_SetCompare3(TIM1, 0);
    }
    else if (Speed < 0 && Speed > -1000)
    {
        TIM_SetCompare4(TIM1, 0);
        TIM_SetCompare3(TIM1, -Speed);
    }
    else if (Speed == 0)
    {
        TIM_SetCompare4(TIM1, 0);
        TIM_SetCompare3(TIM1, 0);
    }
}
