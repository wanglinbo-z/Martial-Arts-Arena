#include "Menu.h"

/**
 * 运行主菜单
 *
 * 该函数负责显示并处理主菜单的选项，包括工具、设置、信息等。
 * 用户可以在此菜单中选择不同的功能或子菜单进行操作。
 */

void Menu_RunMainMenu(void)
{
	static struct Option_Class Menu_StartOptionList[] = {
		{"<<<"},  // 返回上级菜单的选项
		{"Debug Mode", Menu_DebugMode},// DeBug菜单选项，点击后显示信息
		{"Start ACT", Start_ACT},// DeBug菜单选项，点击后显示信息
		{"Information", Menu_Information},// 信息菜单选项，点击后显示信息
		{".."}  // 结束选项列表的标记
	};

	Menu_RunMenu(Menu_StartOptionList);  // 运行菜单系统，传入主菜单的选项列表
}

/**
 * Debug Mode菜单
 *
 */
void Menu_DebugMode(void)
{
	static struct Option_Class Menu_DebugModeOptionList[] = {
		{"<<<"},  // 返回上级菜单的选项
		{"ADC", AD_DeBug},				// ADC调试菜单选项，点击后显示ADC信息
		{"Motor", Motor_Option_DeBug},	// 电机调试菜单选项，点击后显示信息
		{"F Distence", FDistance_Option_DeBug},	// 距离传感器调试菜单选项，点击后显示信息
		{"Erase All Data", Store_Clear},// 清除所有数据选项，点击后REST
		{".."}  // 结束选项列表的标记
	};

	Menu_RunMenu(Menu_DebugModeOptionList);  // 运行菜单系统，
}


void Motor_Option_DeBug(void)
{
		static struct Option_Class Menu_MotorDebugOptionList[] = {
		{"<<<"},  // 返回上级菜单的选项
		{"LeftErr:%.f", LMotorSpeed_ERR_SetCat, &LSpeedErr_Value},// 信息菜单选项，点击后显示信息
		{"RightErr:%.f", RMotorSpeed_ERR_SetCat, &RSpeedErr_Value},// 信息菜单选项，点击后显示信息
		{"Motor TEST", Motor_Test},// 信息菜单选项，点击后显示信息
		{".."}  // 结束选项列表的标记
	};

	Menu_RunMenu(Menu_MotorDebugOptionList);  // 运行菜单系统，
}

void Menu_Information(void)
{
	uint8_t Angle = 233;
	while (1)
	{
		OLED_Clear();

		OLED_ShowImage(88, 8, 32, 32, goutou);
		OLED_Rotation_Block(88 + 16, 8 + 16, 16, Angle * 360 / 256);

		Angle += Menu_RollEvent() * 8;
		Angle += 2;

		OLED_ShowString(2, 0, "Menu V1.8", OLED_8X16);
		OLED_ShowString(2, 26, "By:Adam", OLED_8X16);
		// OLED_ShowString(2, 42, "UP:", OLED_8X16);
		// OLED_ShowString(2, 42, "A三毛定制版", OLED_6X8);

		OLED_Update();
		if (Menu_EnterEvent())
		{
			return;
		}
		if (Menu_BackEvent())
		{
			return;
		}
	}
}

/**********************************************************/
