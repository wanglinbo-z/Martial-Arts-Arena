#include "menu.h"

#include "ADC.h"
#include "LED.h"
#include "Delay.h"

static float NumPower = 1;

/* AD Debug */
/*BEGAIN***********************************************************/
extern uint16_t AD_Value[16];

void AD_DeBug(void)
{
	OLED_Clear();
    
	while (1){

		OLED_ShowString(0,  0, "L1 ", OLED_6X8);
		OLED_ShowString(0,  8, "L2 ", OLED_6X8);
		OLED_ShowString(0, 16, "L3 ", OLED_6X8);
		OLED_ShowString(0, 24, "L4 ", OLED_6X8);
		OLED_ShowString(0, 32, "L5 ", OLED_6X8);
		OLED_ShowString(0, 40, "L6 ", OLED_6X8);
		OLED_ShowString(0, 48, "K1 ", OLED_6X8);
		OLED_ShowString(0, 56, "PY ", OLED_6X8);
		
		
		OLED_ShowString(64,  0, "R1 ", OLED_6X8);
		OLED_ShowString(64,  8, "R2 ", OLED_6X8);
		OLED_ShowString(64, 16, "R3 ", OLED_6X8);
		OLED_ShowString(64, 24, "R4 ", OLED_6X8);
		OLED_ShowString(64, 32, "R5 ", OLED_6X8);
		OLED_ShowString(64, 40, "R6 ", OLED_6X8);
		OLED_ShowString(64, 48, "K2 ", OLED_6X8);
		OLED_ShowString(64, 56, "GF ", OLED_6X8);

		// 左边 10 12 1 3 5 7 15 9
		OLED_ShowNum(18,  0, L1, 3, OLED_6X8);
		OLED_ShowNum(18,  8, L2, 3, OLED_6X8);
		OLED_ShowNum(18, 16, L3, 3, OLED_6X8);
		OLED_ShowNum(18, 24, L4, 3, OLED_6X8);
		OLED_ShowNum(18, 32, L5, 3, OLED_6X8);
		OLED_ShowNum(18, 40, L6, 3, OLED_6X8);
		OLED_ShowNum(18, 48, k1, 1, OLED_6X8);
		OLED_ShowNum(18, 56, py, 4, OLED_6X8);
		
		// 右边 11 13 0 2 4 6 14 8
		OLED_ShowNum(82,  0, R1, 3, OLED_6X8);
		OLED_ShowNum(82,  8, R2, 3, OLED_6X8);
		OLED_ShowNum(82, 16, R3, 3, OLED_6X8);
		OLED_ShowNum(82, 24, R4, 3, OLED_6X8);
		OLED_ShowNum(82, 32, R5, 3, OLED_6X8);
		OLED_ShowNum(82, 40, R6, 3, OLED_6X8);
		OLED_ShowNum(82, 48, k2, 1, OLED_6X8);
		OLED_ShowNum(82, 56, Sensor8, 4, OLED_6X8);
		
		OLED_Update();// 更新OLED
        LED_TOGGLE;
        if (Menu_EnterEvent())
		{
            LED_OFF;
			return;
		}
		if (Menu_BackEvent())
		{
            LED_OFF;
			return;
		}
	}
}

/***********************************************************END*/


/* Motor Debug */
/*BEGAIN***********************************************************/

struct Option_Class MotorDeBugOptionList[] = {
	{"<<<"},
	{"RSpeedErr:%.1f", RMotorSpeed_ERR_SetCat, &RSpeedErr_Value},
	{"LSpeedErr:%.1f", LMotorSpeed_ERR_SetCat, &LSpeedErr_Value},
	{".."},
};

void MotorSpeedErr_Output_Set(int8_t Catch)
{
	NumPower = 1;
	float RSpeedErr_Value_t = RSpeedErr_Value;
	float LSpeedErr_Value_t = LSpeedErr_Value;
	
	while (1)
	{
		OLED_Clear();
		
		switch (Catch) 
		{
		case 1:
			RSpeedErr_Value_t += Menu_RollEvent() * NumPower; // 频率加上 编码器偏移量乘以位权
			OLED_Printf(2, 24, OLED_8X16, "RSpeedErr = %.f", RSpeedErr_Value_t);
			// Tools_PWM_Output_SetFreq(PWM_Output_Freq);		// 设置频率
			// OLED_Printf(2, 24, OLED_8X16, "Freq = (%.1f)", PWM_Output_Freq);
			break;
		case 2:
			LSpeedErr_Value_t += Menu_RollEvent() * NumPower;
			OLED_Printf(2, 24, OLED_8X16, "LSpeedErr:%.f", LSpeedErr_Value_t);
			// Tools_PWM_Output_SetDuty(PWM_Output_Duty); // 设置频率
			// OLED_Printf(2, 24, OLED_8X16, "Duty = (%.1f)", PWM_Output_Duty);
			break;
		default:
			break;
		}

		if (RSpeedErr_Value_t < 0 || LSpeedErr_Value_t < 0)
		{
			RSpeedErr_Value_t = 0;
			LSpeedErr_Value_t = 0;
		}
		
		if (RSpeedErr_Value_t > 1000 || LSpeedErr_Value_t > 1000)
		{
			RSpeedErr_Value_t = 1000;
			LSpeedErr_Value_t = 1000;
		}
		
		if (Menu_BackEvent())
		{
			if (Catch == 1)
			{
				RSpeedErr(RSpeedErr_Value_t);
			}
			if (Catch == 2)
			{
				LSpeedErr(LSpeedErr_Value_t);
			}
			NumPower = 1;
			return;
		}
		if (Menu_EnterEvent())
		{
			NumPower *= 10; 
			if (NumPower > 100)
			{
				NumPower = 1;
			}
		}
		OLED_Printf(0, 48, 8, "Power: x%.f", NumPower);
		OLED_Update();
	}
}

void RMotorSpeed_ERR_SetCat(void)
{
	MotorSpeedErr_Output_Set(1);
}
void LMotorSpeed_ERR_SetCat(void)
{
	MotorSpeedErr_Output_Set(2);
}

struct Option_Class MotorTESTOptionList[] = {
	{"<<<"},
	{"RSpeed:%.f", MotorTest_R, &RSpeed},
	{"LSpeed:%.f", MotorTest_L, &LSpeed},
	{".."},
};

void MotorTest_Output_Set(int8_t Catch)
{
	NumPower = 1;
	float RSpeed_t = RSpeed;
	float LSpeed_t = LSpeed;
	
	while (1)
	{
		OLED_Clear();
		
		switch (Catch) 
		{
		case 1:
			RSpeed_t += Menu_RollEvent() * NumPower;
			Motor_RSpeed(RSpeed_t);
			OLED_Printf(2, 24, OLED_8X16, "R_Speed = %.f", RSpeed_t);
			break;
		case 2:
			LSpeed_t += Menu_RollEvent() * NumPower;
			Motor_LSpeed(LSpeed_t);
			OLED_Printf(2, 24, OLED_8X16, "L_Speed:%.f", LSpeed_t);
			break;
		default:
			break;
		}
		
		if (RSpeed_t > 999 || LSpeed_t > 999)
		{
			RSpeed_t = 999;
			LSpeed_t = 999;
			if (Catch == 1)
			{
				Motor_RSpeed(RSpeed_t);
			}
			if (Catch == 2)
			{
				Motor_LSpeed(LSpeed_t);
			}

		}
		
		if (RSpeed_t < -999 || LSpeed_t < -999)
		{
			RSpeed_t = -999;
			LSpeed_t = -999;
			if (Catch == 1)
			{
				Motor_RSpeed(RSpeed_t);
			}
			if (Catch == 2)
			{
				Motor_LSpeed(LSpeed_t);
			}
		}
		
		if (Menu_BackEvent())
		{
			if (Catch == 1)
			{
				Motor_RSpeed(RSpeed_t);
			}
			if (Catch == 2)
			{
				Motor_LSpeed(LSpeed_t);
			}
			NumPower = 1;
			return;
		}
		if (Menu_EnterEvent())
		{
			NumPower *= 10; 
			if (NumPower > 100)
			{
				NumPower = 1;
			}
		}
		OLED_Printf(0, 48, 8, "Power: x%.f", NumPower);
		OLED_Update();
	}
}

void MotorTest_R(void)
{
	MotorTest_Output_Set(1);
}

void MotorTest_L(void)
{
	MotorTest_Output_Set(2);
}

void Motor_Test(void)
{
	Motor_RSpeed(0);
	Motor_LSpeed(0);

	Menu_RunMenu(MotorTESTOptionList);  // 运行菜单系统

	Motor_RSpeed(0);
	Motor_LSpeed(0);
}

/**********************************************************END*/

/* F Distance DeBug */

/*BEGAIN*******************************************************/

float D_Factor_t;

struct Option_Class F_DeBugOptionList[] = {
	{"<<<"},
	{"D_Factor:%.f", F_DeBug, &D_Factor_t},
	{".."},
};

void F_DeBug(void)
{
	NumPower = 1;
	OLED_Clear();
	
	while (1)
	{

		D_Factor_t += Menu_RollEvent() * NumPower;
		OLED_Printf(2, 24, OLED_8X16, "D_Factor:%.f", D_Factor_t);

		OLED_Printf(0, 48, 8, "Power: x%.f", NumPower);

		if (D_Factor_t > 99)
		{
			D_Factor_t = 99;
		}

		if (Menu_BackEvent())
		{
			D_Factor = D_Factor_t;
			Store_Data[D_Factor_Data] = D_Factor_t;
			Store_Save();
			return;
		}
		
		if (Menu_EnterEvent())
		{
			NumPower *= 10; 
			if (NumPower > 10)
			{
				NumPower = 1;
			}
		}
		OLED_Update();
	}
}

void FDistance_Option_DeBug(void)
{
	D_Factor_t = D_Factor;
	Menu_RunMenu(F_DeBugOptionList);  // 运行菜单系统
}

/*********************************************************END*/
