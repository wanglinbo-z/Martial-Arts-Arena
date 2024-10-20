#include "Menu.h"

/**
 * �������˵�
 *
 * �ú���������ʾ���������˵���ѡ��������ߡ����á���Ϣ�ȡ�
 * �û������ڴ˲˵���ѡ��ͬ�Ĺ��ܻ��Ӳ˵����в�����
 */

void Menu_RunMainMenu(void)
{
	static struct Option_Class Menu_StartOptionList[] = {
		{"<<<"},  // �����ϼ��˵���ѡ��
		{"Debug Mode", Menu_DebugMode},// DeBug�˵�ѡ��������ʾ��Ϣ
		{"Start ACT", Start_ACT},// DeBug�˵�ѡ��������ʾ��Ϣ
		{"Information", Menu_Information},// ��Ϣ�˵�ѡ��������ʾ��Ϣ
		{".."}  // ����ѡ���б�ı��
	};

	Menu_RunMenu(Menu_StartOptionList);  // ���в˵�ϵͳ���������˵���ѡ���б�
}

/**
 * Debug Mode�˵�
 *
 */
void Menu_DebugMode(void)
{
	static struct Option_Class Menu_DebugModeOptionList[] = {
		{"<<<"},  // �����ϼ��˵���ѡ��
		{"ADC", AD_DeBug},				// ADC���Բ˵�ѡ��������ʾADC��Ϣ
		{"Motor", Motor_Option_DeBug},	// ������Բ˵�ѡ��������ʾ��Ϣ
		{"F Distence", FDistance_Option_DeBug},	// ���봫�������Բ˵�ѡ��������ʾ��Ϣ
		{"Erase All Data", Store_Clear},// �����������ѡ������REST
		{".."}  // ����ѡ���б�ı��
	};

	Menu_RunMenu(Menu_DebugModeOptionList);  // ���в˵�ϵͳ��
}


void Motor_Option_DeBug(void)
{
		static struct Option_Class Menu_MotorDebugOptionList[] = {
		{"<<<"},  // �����ϼ��˵���ѡ��
		{"LeftErr:%.f", LMotorSpeed_ERR_SetCat, &LSpeedErr_Value},// ��Ϣ�˵�ѡ��������ʾ��Ϣ
		{"RightErr:%.f", RMotorSpeed_ERR_SetCat, &RSpeedErr_Value},// ��Ϣ�˵�ѡ��������ʾ��Ϣ
		{"Motor TEST", Motor_Test},// ��Ϣ�˵�ѡ��������ʾ��Ϣ
		{".."}  // ����ѡ���б�ı��
	};

	Menu_RunMenu(Menu_MotorDebugOptionList);  // ���в˵�ϵͳ��
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
		// OLED_ShowString(2, 42, "A��ë���ư�", OLED_6X8);

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
