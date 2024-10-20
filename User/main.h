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

#define delay_ms(x) Delay_ms(x)             //兼容
#define k1          FDT_Read(2) //前铲左
#define k2          FDT_Read(1) //前铲右
#define py          Sensor9  < 2500 ? 1 : 0 //前光电

void Start_ACT(void);       //比赛主函数

void fist_up_stage(void);   //上台
int stage_inspect(void);    //台下识别
int stage(void);            //防掉台
int xundi(void);            //寻敌
void stop(u16 s);           //停车
void tuixiatai(void);       //退台
int xun(void);              //
void move(int Rs,int Ls);      //移动
uint16_t F_Distance(uint8_t ch);

#endif /* __MAIN_H */
