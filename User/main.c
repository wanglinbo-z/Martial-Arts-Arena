#include "main.h"

int main(void)
{
	Sys_Init();

	/*模块初始化*/
	OLED_Init();				//OLED初始化
	Key_Init();					//按键初始化
	Store_Init();				//参数存储模块初始化，在上电的时候将闪存的数据加载回Store_Data，实现掉电不丢失
	LED_Init();					//LED初始化
	AD_Init();					//ADC转换初始化
	Motor_Init();				//电机初始化
	FDT_Init();
	
	OLED_Clear();
	OLED_Update();
	
	Store_Data[Status] = 0;
	//if (Store_Data[Status] == 1)Start_ACT();// 意外断电重启
	if (Store_Data[D_Factor_Data] == 0)Store_Data[D_Factor_Data]=41;D_Factor=Store_Data[D_Factor_Data];Store_Save();// 默认为41

	while (1)
	{
		Menu_RunMainMenu();

		Power_Off();
	}
}

int Power_Off(void) // 关机
{
	/*关闭外设区*******/
	OLED_Clear();
	OLED_Update();
	/*******关闭外设区*/

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); // Enables or disables the Low Speed APB (APB1) peripheral clock.
	PWR_WakeUpPinCmd(ENABLE);

	PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI); // STOP模式
	SystemInit();

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, DISABLE); // Enables or disables the Low Speed APB (APB1) peripheral clock.
	PWR_WakeUpPinCmd(DISABLE);

	Key_Reset_All();
	Key_Reset_All();

	return 1;
}


