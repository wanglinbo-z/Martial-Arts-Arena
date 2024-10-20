#ifndef __OLED_H
#define __OLED_H

#include <stdint.h>
#include "OLED_Data.h"
#include "timer.h"
#include "MyI2C.h"

/*�����궨��*********************/

#define OLED_IIC_Software false

/*FontSize����ȡֵ*/
/*�˲���ֵ���������жϣ��������ڼ�������ַ�ƫ�ƣ�Ĭ��ֵΪ�������ؿ��*/
#define OLED_8X16				8
#define OLED_6X8				6

/*IsFilled������ֵ*/
#define OLED_UNFILLED			0
#define OLED_FILLED				1

/*********************�����궨��*/

extern uint8_t OLED_DisplayBuf[8][128];

/*��������*********************/

/*��ʼ������*/
void OLED_Init(void);

/*���º���*/
void OLED_Update(void);
void OLED_UpdateArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);

/*�Դ���ƺ���*/
void OLED_Clear(void);
void OLED_ClearArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
void OLED_Reverse(void);
void OLED_ReverseArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);

/*��ʾ����*/
void OLED_ShowChar(uint8_t X, uint8_t Y, char Char, uint8_t FontSize);
void OLED_ShowString(uint8_t X, uint8_t Y, char *String, uint8_t FontSize);
void OLED_ShowNum(uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowSignedNum(uint8_t X, uint8_t Y, int32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowHexNum(uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowBinNum(uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowFloatNum(uint8_t X, uint8_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize);
void OLED_ShowChinese(uint8_t X, uint8_t Y, char *Chinese);
void OLED_ShowImage(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image);
void OLED_Printf(uint8_t X, uint8_t Y, uint8_t FontSize, char *format, ...);

/*��ͼ����*/
void OLED_DrawPoint(uint8_t X, uint8_t Y);
uint8_t OLED_GetPoint(uint8_t X, uint8_t Y);
void OLED_DrawLine(uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1);
void OLED_DrawRectangle(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, uint8_t IsFilled);
void OLED_DrawTriangle(uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2, uint8_t IsFilled);
void OLED_DrawCircle(uint8_t X, uint8_t Y, uint8_t Radius, uint8_t IsFilled);
void OLED_DrawEllipse(uint8_t X, uint8_t Y, uint8_t A, uint8_t B, uint8_t IsFilled);
void OLED_DrawArc(uint8_t X, uint8_t Y, uint8_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled);

/*********************��������*/
uint8_t OLED_ShowStringArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, char *String, uint8_t FontSize);	//�����ӡ;


void OLED_Rotation_C_P(int8_t CX, int8_t CY, float* PX, float* PY, int16_t Angle);	//����ת
void OLED_Rotation_Block(int8_t X, int8_t Y, int8_t Width, int16_t Angle);			//������ת
void bresenham_ellipse(int x0, int y0, int rx, int ry);
void ellipse_algorithm(int8_t x0, int8_t y0, int8_t a, int8_t b);



#endif


/*****************��Э�Ƽ�|��Ȩ����****************/
/*****************jiangxiekeji.com*****************/
