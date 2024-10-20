#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "Store.h"
#include "Key.h"
#include "ADC.h"
#include "menu.h"
#include "Motor.h"
#include "FDT.h"

extern uint16_t AD_Value[16];

#define HardFault_Tims_Data 100 

int Power_Off(void);

/* 5shu.c */
#define Status 5
#define D_Factor_Data 7

#define delay_ms(x) Delay_ms(x)             //����
#define k1          FDT_Read(2) //ǰ����
#define k2          FDT_Read(1) //ǰ����
#define py          Sensor9  < 2500 ? 1 : 0 //ǰ���

void Start_ACT(void);       //����������

void fist_up_stage(void);   //��̨
int stage_inspect(void);    //̨��ʶ��
int stage(void);            //����̨
int xundi(void);            //Ѱ��
void stop(u16 s);           //ͣ��
void tuixiatai(void);       //��̨
int xun(void);              //
void move(int Rs,int Ls);      //�ƶ�
uint16_t F_Distance(uint8_t ch);

#endif /* __MAIN_H */
