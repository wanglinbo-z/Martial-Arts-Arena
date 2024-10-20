#ifndef __OLED_DATA_H
#define __OLED_DATA_H

#include <stdint.h>

/*�����ַ��ֽڿ��*/
#define OLED_CHN_CHAR_WIDTH			2		//UTF-8�����ʽ��3��GB2312�����ʽ��2

/*��ģ������Ԫ*/
typedef struct 
{
	uint8_t Data[32];						//��ģ����
	char Index[OLED_CHN_CHAR_WIDTH + 1];	//��������
} ChineseCell_t;

/*ASCII��ģ��������*/
extern const uint8_t OLED_F8x16[][16];
extern const uint8_t OLED_F6x8[][6];

/*������ģ��������*/
extern const ChineseCell_t OLED_CF16x16[];
extern const ChineseCell_t OLED_CF12x12[];
extern const ChineseCell_t OLED_CF10x10[];
extern const ChineseCell_t OLED_CF8x8[];

/*ͼ����������*/
extern const uint8_t Diode[];
/*��������ĸ�ʽ�������λ�ü����µ�ͼ����������*/
extern const uint8_t Cursor[];
extern const uint8_t goutou[];
extern const uint8_t Wallpaper[];
extern const uint8_t XpWallpaper[];
extern const uint8_t Win11Wallpaper[];
//...
	
#endif


/*****************��Э�Ƽ�|��Ȩ����****************/
/*****************jiangxiekeji.com*****************/
