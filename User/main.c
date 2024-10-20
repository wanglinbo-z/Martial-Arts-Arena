#include "main.h"

int main(void)
{
	Sys_Init();

	/*ģ���ʼ��*/
	OLED_Init();				//OLED��ʼ��
	Key_Init();					//������ʼ��
	Store_Init();				//�����洢ģ���ʼ�������ϵ��ʱ����������ݼ��ػ�Store_Data��ʵ�ֵ��粻��ʧ
	LED_Init();					//LED��ʼ��
	AD_Init();					//ADCת����ʼ��
	Motor_Init();				//�����ʼ��
	FDT_Init();
	
	OLED_Clear();
	OLED_Update();
	
	Store_Data[Status] = 0;
	//if (Store_Data[Status] == 1)Start_ACT();// ����ϵ�����
	if (Store_Data[D_Factor_Data] == 0)Store_Data[D_Factor_Data]=41;D_Factor=Store_Data[D_Factor_Data];Store_Save();// Ĭ��Ϊ41

	while (1)
	{
		Menu_RunMainMenu();

		Power_Off();
	}
}

int Power_Off(void) // �ػ�
{
	/*�ر�������*******/
	OLED_Clear();
	OLED_Update();
	/*******�ر�������*/

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); // Enables or disables the Low Speed APB (APB1) peripheral clock.
	PWR_WakeUpPinCmd(ENABLE);

	PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI); // STOPģʽ
	SystemInit();

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, DISABLE); // Enables or disables the Low Speed APB (APB1) peripheral clock.
	PWR_WakeUpPinCmd(DISABLE);

	Key_Reset_All();
	Key_Reset_All();

	return 1;
}


