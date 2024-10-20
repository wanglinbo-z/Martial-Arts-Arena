#ifndef __MENU_H
#define __MENU_H
#include <stdio.h>
#include <stdarg.h>
#include "stm32f10x.h" // Device header
#include <string.h>
#include "main.h"

struct Option_Class
{
	char *String;		// ѡ������
	void (*func)(void); // ����ָ��
	float *Variable;	// ��ѡ����
	uint8_t StrLen;		// ��������ռ�����ֽ�,��strlen�������ֳ��Ȳ���׼ȷ,������ⴢ�����ֳ���
};

enum CursorStyle
{
	reverse,
	mouse,
	frame,
};

struct MenuProperty
{
	float Cursor_Actual_X;		  // ��ǰ���λ��X
	float Cursor_Actual_Y;		  // ��ǰ���λ��Y
	float Cursor_Actual_W;		  // ��ǰ���ߴ��
	float Cursor_Actual_H;		  // ��ǰ���ߴ��
	enum CursorStyle CursorStyle; // �����;
	float Cursor_ActSpeed;		  // ��궯���ٶ�ϵ��;
	float Slide_ActSpeed;		  // ���������ٶ�ϵ��;
	int8_t Font_Width;			  // ������
	int8_t Font_Height;			  // ������
	int8_t Line_Height;			  // �и�
	int8_t Layout_Margin;		  // ҳ�߾�

	int8_t Window_X;				// ����λ��X
	int8_t Window_Y;                // ����λ��Y
	uint8_t Window_W;               // ���ڿ��
	uint8_t Window_H;               // ���ڸ߶�
};
extern struct MenuProperty Menu_Global;

void Menu_RunMenu(struct Option_Class *MU);
/**********************************************************/
void Menu_RunMainMenu(void);
void Menu_DebugMode(void);
void Motor_Option_DeBug(void);
void Menu_Information(void);
/**********************************************************/
/* DeBug Mode Function */

// ADC
void AD_DeBug(void);

// Motor
extern float RSpeedErr_Value;
extern float LSpeedErr_Value;
extern float RSpeed;
extern float LSpeed;

void RMotorSpeed_ERR_SetCat(void);
void LMotorSpeed_ERR_SetCat(void);
void MotorTest_R(void);
void MotorTest_L(void);
void Motor_Test(void);

// F Distance
extern uint16_t D_Factor;

void F_DeBug(void);
void FDistance_Option_DeBug(void);
/**********************************************************/
int8_t Menu_RollEvent(void);
int8_t Menu_EnterEvent(void);
int8_t Menu_BackEvent(void);
/**********************************************************/
uint8_t Menu_GetOptionStrLen(char *String);
uint8_t Menu_PrintfOptionStr(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, uint8_t FontSize, char *format, ...);
/**********************************************************/
float Menu_CurveMigration(float Actual_Value, float Target_Value, float Act_Speed);
void Menu_ShowCursor(float Target_Cur_X, float Target_Cur_Y, float Target_Cur_W, float Target_Cur_H, enum CursorStyle CurStyle, float Cur_Act_Speed);
/**********************************************************/
void Menu_ShowWallpaper(const uint8_t *Wallpaper);

#endif
