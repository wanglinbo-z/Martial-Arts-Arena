#include "Menu.h"

/**********************************************************
 * ��Ƭ���༶�˵����v1.8	By:Adam
 *
 * ���θ���:
 * ���OLED����,OLED��ʾͼ����Y������Ǹ���,����˵�����ʱ�����ǿհ׵�����;
 * �Ż��������߼�, ת��������;
 * ʵ�ù���PWM���;
 * �Ż�������, �Ա�׼������������;
 * ����˲˵�ȫ�����Խṹ��;
 * �ú�����װ�˲��ֹ���;
 * ����ṹ������;
 * �����ע��!;
 *
 * ֡����ʾ,������ת�� OLED_Update() �������ע�Ϳ���;
 * OLED��ʾ�����Խ�Э�Ƽ���OLED��ʾ����������Ϊ���������������޸�
 * OLED��ʾ��ʹ�����IICͨ��: SCL�ӵ�PB8, SDA�ӵ�PB9;
 *
 * ��������
 * �ٶ�����:https://pan.baidu.com/s/1bZPWCKaiNbb-l1gpAv6QNg?pwd=KYWS
 * GitHub:https://github.com/AdamLoong/Embedded_Menu_Simple
 * BվUP:����Ŷ�����
 * ������ô˲˵���������а����ǵû�������һ������Ŷ( ?? �� ?? )?
 **********************************************************/

/*�˵�ȫ������*/
struct MenuProperty Menu_Global = {
	.Cursor_Actual_X = 0,  // ��ǰ���λ��X
	.Cursor_Actual_Y = 63, // ��ǰ���λ��Y
	.Cursor_Actual_W = 0,  // ��ǰ���ߴ��
	.Cursor_Actual_H = 0,  // ��ǰ���ߴ��

	.CursorStyle = reverse,	 // �����;
	.Cursor_ActSpeed = 0.15, // ��궯���ٶ�ϵ��;
	.Slide_ActSpeed = 2,	 // ���������ٶ�ϵ��;

	.Font_Width = 8,	// ������ 8 �� 6
	.Font_Height = 16,	// ����߶�
	.Line_Height = 16,	// �и�
	.Layout_Margin = 0, // ҳ�߾�

	.Window_X = 0,	 // ����λ��X
	.Window_Y = 0,	 // ����λ��Y
	.Window_W = 128, // ���ڿ��
	.Window_H = 64,	 // ���ڸ߶�
};

/*�˵��õ��İ���������������,������ֲ���޸�,����û�б���������������������������;*/
int8_t Menu_RollEvent(void) // �˵�����
{
	if (Key_Up_Get()) 
	{
		return 1;
	}
	if (Key_Down_Get())
	{
		return -1;
	}
	return 0;
	// return Encoder_Get_Div4(); // ��ť������PA8,PA9;
}
int8_t Menu_EnterEvent(void) // �˵�ȷ��
{
	return Key_Enter_Get();
}
int8_t Menu_BackEvent(void) // �˵�����
{
	return Key_Back_Get();
}

/**
 * ��    �����˵�����
 * ��    ����ѡ���б�
 * �� �� ֵ��
 * ˵    ������ѡ���б���ʾ����,�����ݰ����¼�ִ����Ӧ����
 */
void Menu_RunMenu(struct Option_Class *Option_List)
{

	int8_t Roll_Event = 0;		// ��¼�˵������¼�
	int8_t Show_i = 0;			// ��ʾ��ʼ�±�
	int8_t Show_i_previous = 4; // ��ʾ��ʼ�±��ǰһ��״̬(���ڱȽ�)
	int8_t Show_offset;			// ��ʾY���ƫ��
	int8_t Cat_i = 1;			// ѡ���±�Ĭ��Ϊ1,(��ΪOption_List[0]Ϊ"<<<")
	int8_t Cur_i = 0;			// ����±�Ĭ��Ϊ0

	int8_t Option_MaxNum = 0;
	for (Option_MaxNum = 0; Option_List[Option_MaxNum].String[0] != '.'; Option_MaxNum++) // ����ѡ���б���
	{
		// Option_List[Option_MaxNum].StrLen = Menu_GetOptionStrLen(Option_List[Option_MaxNum].String); // ˳�ּ���ѡ�����ֳ���
	}
	Option_MaxNum--;

	/*����±����Ƶ��ڴ��ڸ߶ȼ�ȥ����ҳ�߾��ٳ����и�*/
	int8_t Cur_i_Ceiling = (Menu_Global.Window_H - Menu_Global.Layout_Margin * 2) / Menu_Global.Line_Height; // ����������λ��;

	/**********************************************************/

	while (1)
	{

		if (Menu_EnterEvent())
		{
			/*������ܲ�Ϊ����ִ�й���,���򷵻�*/
			if (Option_List[Cat_i].func)
			{
				Option_List[Cat_i].func();
			}
			else
			{
				return;
			}
		}
		if (Menu_BackEvent())
		{
			return;
		}

		/*���ݰ����¼�����ѡ���±�͹���±�*/
		Roll_Event = -Menu_RollEvent();
		if (Roll_Event)
		{
			/*�����±�*/
			Cur_i += Roll_Event;
			Cat_i += Roll_Event;
			/*����ѡ���±�*/
			if (Cat_i > Option_MaxNum)
			{
				Cat_i = Option_MaxNum;
			}
			if (Cat_i < 0)
			{
				Cat_i = 0;
			}
			/*���ƹ���±�*/
			if (Cur_i >= Cur_i_Ceiling)
			{
				Cur_i = Cur_i_Ceiling - 1;
			}
			if (Cur_i > Option_MaxNum)
			{
				Cur_i = Option_MaxNum;
			}
			if (Cur_i < 0) // �ȿӼ�¼: (Cur_i >= Cur_i_Ceiling) Cur_i_Ceiling �п����Ǹ���, �������(Cur_i < 0)�����ж�, �� Cur_i ���ɸ���, ��ɳ�����; ����: �������λ�������ж�, �����ж�Ӧ�÷���ǰ,�����ж�Ӧ�÷��ں�;
			{
				Cur_i = 0;
			}
		}

		/**********************************************************/

		OLED_Clear();

		/*������ʾ��ʼ�±�*/
		Show_i = Cat_i - Cur_i;

		if (1) // ������ʾƫ����ʵ��ƽ���ƶ�
		{
			if (Show_i - Show_i_previous) // ����±���ƫ��
			{
				Show_offset = (Show_i - Show_i_previous) * Menu_Global.Line_Height; // ������ʾƫ����
				Show_i_previous = Show_i;
			}
			if (Show_offset)
			{
				Show_offset /= Menu_Global.Slide_ActSpeed; // ��ʾƫ�����𽥹���
			}
		}

		for (int8_t i = -1; i < Cur_i_Ceiling + 1; i++) // ������ʾѡ��(���� i �� -1 ��ʼ�� Cur_i_Ceiling + 1 ����, ��Ϊ�˲˵�������ʱ�����к�β�в����пհ�);
		{
			if (Show_i + i < 0)
			{
				continue;
			}
			if (Show_i + i > Option_MaxNum)
			{
				break;
			}

			/*�˵���ʽ����ӡ�����᷵�ش�ӡ���ַ�������*/
			Option_List[Show_i + i].StrLen =
				/*ʹ�ø�ʽ���ַ�����ӡ, ֧�����һ��(float)����*/
				Menu_PrintfOptionStr(
					/*��ʾ�Ӵ���X���, ����ҳ�߾�*/
					2 + Menu_Global.Window_X + Menu_Global.Layout_Margin,
					/*��ʾ�Ӵ���Y���, ����ҳ�߾�, ������ƫ��, ������ʾƫ��, ���ϴ�ֱ����*/
					Menu_Global.Window_Y + (Menu_Global.Layout_Margin) + (i * Menu_Global.Line_Height) + (Show_offset) + ((Menu_Global.Line_Height - Menu_Global.Font_Height) / 2),
					/*��ʾ��ȷ�Χ��ȥ˫��(����)ҳ�߾�*/
					Menu_Global.Window_W - Menu_Global.Layout_Margin * 2,
					/*��ʾ�߶Ⱦ����и�(���ָ�)*/
					Menu_Global.Line_Height,
					/*��ʾ�ַ��Ŀ��*/
					Menu_Global.Font_Width,
					/*Ҫ��ʾ���ַ���*/
					Option_List[Show_i + i].String,
					/*��ѡ����*/
					*Option_List[Show_i + i].Variable);
		}

		// ������ʾ��꺯��
		Menu_ShowCursor(Menu_Global.Window_X + Menu_Global.Layout_Margin,									  // �����������ҳ�߾�
						Menu_Global.Window_Y + Menu_Global.Layout_Margin + (Cur_i * Menu_Global.Line_Height), // ����������Ϲ����ƫ��
						4 + Option_List[Cat_i].StrLen * Menu_Global.Font_Width + Menu_Global.Layout_Margin,	  // ����ȵ����ַ������ȳ����ַ���ȼ���ҳ�߾�(�����ַ���)
																											  // Menu_Global.Window_W - Menu_Global.Layout_Margin * 2,// ����ȵ��ڴ��ڿ�ȼ�ȥ����ҳ�߾�(�ȳ�)(��ѡһע��)
						Menu_Global.Line_Height,															  // ���߶Ⱦ����и�
						Menu_Global.CursorStyle,															  // ���״̬
						Menu_Global.Cursor_ActSpeed);														  // ����ٶ�

		// OLED_DrawRectangle(Menu_Global.Window_X, Menu_Global.Window_Y, Menu_Global.Window_W, Menu_Global.Window_H, 0); // ��ʾ���ڱ߿�,���ݸ���ϲ��ѡ��

		/**********************************************************/
		/*������Ϣ*/

		// OLED_ShowSignedNum(110, 48, Cur_i, 2, OLED_6X8);
		// OLED_ShowSignedNum(110, 56, Cat_i, 2, OLED_6X8);

		// int delay = 1000000; while(delay--);
		/**********************************************************/
		OLED_Update();
	}
}

/**
 * ��    ��������ѡ���ַ�������;
 * ��    ����String ���㳤�ȵ��ַ���
 * �� �� ֵ���ַ�������
 * ˵    ����Ӣ��һ������,������������;
 */
uint8_t Menu_GetOptionStrLen(char *String)
{
	uint8_t i = 0, len = 0;
	while (String[i] != '\0') // �����ַ�����ÿ���ַ�
	{
		if (String[i] > '~') // ���������Ӣ���ַ����ȼ�2
		{
			len += 2;
			i += 3;
		}
		else // ����Ӣ���ַ����ȼ�1
		{
			len += 1;
			i += 1;
		}
	}
	return len;
}

/**
 * ��    ����ʹ��printf������ӡ��ʽ���ַ���(���ӷ�Χ��ӡ)
 * ��    ����X ָ����ʽ���ַ������Ͻǵĺ����꣬��Χ��0~127
 * ��    ����Y ָ����ʽ���ַ������Ͻǵ������꣬��Χ��0~63
 * ��    ����Width  ��Χ��0~127
 * ��    ����Height ��Χ��0~63
 * ��    ����FontSize ָ�������С
 *           ��Χ��OLED_8X16		��8���أ���16����
 *                 OLED_6X8		��6���أ���8����
 * ��    ����format ָ��Ҫ��ʾ�ĸ�ʽ���ַ�������Χ��ASCII��ɼ��ַ���ɵ��ַ���
 * ��    ����... ��ʽ���ַ��������б�
 * �� �� ֵ��*****************��ӡ�ַ����ĳ���******************
 * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
uint8_t Menu_PrintfOptionStr(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, uint8_t FontSize, char *format, ...)
{
	char String[30];												   // �����ַ�����
	va_list arg;													   // ����ɱ�����б��������͵ı���arg
	va_start(arg, format);											   // ��format��ʼ�����ղ����б�arg����
	vsprintf(String, format, arg);									   // ʹ��vsprintf��ӡ��ʽ���ַ����Ͳ����б��ַ�������
	va_end(arg);													   // ��������arg
	return OLED_ShowStringArea(X, Y, Width, Height, String, FontSize); // OLED��ʾ�ַ����飨�ַ������������ַ���
}

/**
 * ��    ����ƽ��ƫ��
 * ��    ����Actual_Value ��ǰ��ֵ
 * ��    ����Target_Value Ŀ����ֵ
 * ��    ����Act_Speed ƫ���ٶ�
 * �� �� ֵ: ��ǰ��ֵƫ�ƺ��ֵ
 * ˵    �������ո�ʽд�����, ÿ��ѭ������, ��ǰֵ����Ŀ��ֵ����һ������
 */
float Menu_CurveMigration(float Actual_Value, float Target_Value, float Act_Speed)
{
	if ((Target_Value - Actual_Value) > 1)
	{
		Actual_Value += (Target_Value - Actual_Value) * Act_Speed + 1;
	}
	else if ((Target_Value - Actual_Value) < -1)
	{
		Actual_Value += (Target_Value - Actual_Value) * Act_Speed - 1;
	}
	else
	{
		Actual_Value = Target_Value;
	}

	return Actual_Value;
}

/**
 * ��    �����˵�ƽ����ʾ���
 * ��    ����Target_Cur_X ���Ŀ��Xλ��
 * ��    ����Target_Cur_Y ���Ŀ��Yλ��
 * ��    ����Target_Cur_W ���Ŀ����
 * ��    ����Target_Cur_H ���Ŀ��߶�
 * ��    ����Cur_Act_Speed ����ƶ��ٶȷ�Χ: 0 < Cur_Act_Speed <=1
 * �� �� ֵ����
 * ˵    ����������Ŀ��λ�úͳߴ�, �����ڶ�δ�ӡ���𽥽ӽ�Ŀ��λ�úͳߴ�;
 */
void Menu_ShowCursor(float Target_Cur_X, float Target_Cur_Y, float Target_Cur_W, float Target_Cur_H, enum CursorStyle CurStyle, float Cur_Act_Speed)
{
	Menu_Global.Cursor_Actual_X = Menu_CurveMigration(Menu_Global.Cursor_Actual_X, Target_Cur_X, Cur_Act_Speed);
	Menu_Global.Cursor_Actual_Y = Menu_CurveMigration(Menu_Global.Cursor_Actual_Y, Target_Cur_Y, Cur_Act_Speed);
	Menu_Global.Cursor_Actual_W = Menu_CurveMigration(Menu_Global.Cursor_Actual_W, Target_Cur_W, Cur_Act_Speed);
	Menu_Global.Cursor_Actual_H = Menu_CurveMigration(Menu_Global.Cursor_Actual_H, Target_Cur_H, Cur_Act_Speed);

	if (CurStyle == reverse)
	{
		OLED_ReverseArea(Menu_Global.Cursor_Actual_X, Menu_Global.Cursor_Actual_Y, Menu_Global.Cursor_Actual_W, Menu_Global.Cursor_Actual_H); // ������
	}
	else if (CurStyle == mouse)
	{
		OLED_ShowString(Menu_Global.Cursor_Actual_X + Menu_Global.Cursor_Actual_W, Menu_Global.Cursor_Actual_Y + (Menu_Global.Cursor_Actual_H - 6) / 2, "<-", OLED_6X8); // β�͹��
	}
	else if (CurStyle == frame)
	{
		OLED_DrawRectangle(Menu_Global.Cursor_Actual_X, Menu_Global.Cursor_Actual_Y, Menu_Global.Cursor_Actual_W, Menu_Global.Cursor_Actual_H, 0); // ���ι��
	}
}

/***
 * ��    ��: ��ʾ��ֽ;
 * ��    ��: ͼƬ��ı�ֽ
 * �� �� ֵ:
 * ˵    ��: ʹ��memcpy��Ч�ʰѱ�ֽ���ݸ��Ƶ��Դ�;
 */
void Menu_ShowWallpaper(const uint8_t *Wallpaper)
{
	memcpy(OLED_DisplayBuf, Wallpaper, 1024);
}
