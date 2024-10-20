#include "main.h"

uint16_t D_Factor;

void Start_ACT(void)
{
    OLED_Clear();
    OLED_ShowString(0, 0, "Acting...", OLED_8X16);
    OLED_Update();
    
	u16 t=0;
	
    // 预备阶段，启动等待
    if(Store_Data[Status] == 0)// 状态保存
    {
		Delay_ms(1000);
        OLED_ShowString(0, 24, "READY", OLED_8X16);
        OLED_Update();

        while(1){if((R4>60)||(L4>60))break;}

        Store_Data[Status] = 1;
        Store_Save();

        // 第一步，上台
        fist_up_stage();
    }

	OLED_ClearArea(0, 24, 128, 16);
	OLED_ShowString(0, 24, "GO", OLED_8X16);
	OLED_Update();
	
    // 上台，并做出相应动作
	while(1)
	{
        if (Menu_BackEvent())
		{
            Store_Data[Status] = 0;
            Store_Save();
			Motor_Stop();
            return;
        }
		
        // 台下识别
		switch(stage_inspect())
		{
			case 0:                     // 台上
				switch(stage())         // 放掉台
				{
					case 0:             // 在擂台上
						switch(0/*xundi()*/) // 寻找敌人
							{
								case 0 : if(py){move(240,240);}else{move(110,110);}break;      			//未遇见敌人绕台寻找敌人
								// case 1 : tuixiatai(); break;										//敌人出现在前方执行进攻程序如果将敌人推下台会触发守擂功能
								// case 2 : if(L2>35){move(200,-200);}	else{move(200,200);}break;	    //敌人出现在前左和前
								// case 3 : if(R2>35){move(-200,200);} else{move(200,200);}break;		//敌人出现在右和前
								// case 4 : move(260,-260);while(t<23&&xun()){t++;}t=0;break; 			//敌人出现在前左
								// case 5 : move(-260,260);while(t<23&&xun()){t++;}t=0;break; 			//敌人出现在前右
								// case 6 : move(320,-320);while(t<36&&xun()){t++;}t=0;break; 			//敌人出现在左
								// case 7 : move(-320,320);while(t<36&&xun()){t++;}t=0;break; 			//敌人出现在右
								// case 8 : move(350,-350);while(t<23&&xun()){t++;}t=0;break; 			//敌人出现在后左
								// case 9 : move(-350,350);while(t<23&&xun()){t++;}t=0;break; 			//敌人出现在后右
								// case 10: move(-370,370);while(t<23&&xun()){t++;}t=0;break; 			//敌人出现在后
							}break; 
					case 1: move(-450,-450);delay_ms(300);move(-300,300);delay_ms(300);break;  																																											//前铲全空，直退掉头			
					case 2: if(R5<=23&&L5<=23){move(-450,-450);delay_ms(300);move(300,-300);delay_ms(300);}
							else{move(-130,-130);delay_ms(100);move(-150,150);delay_ms(200);}break; 	//前铲左无右有，退左转90度
					case 3: if(R5<=23&&L5<=23){move(-450,-450);delay_ms(300);move(-300,300);delay_ms(300);}
							else{move(-130,-130);delay_ms(100);move(150,-150);delay_ms(200);}break; 	//前铲左有右无，退右转90度
				}break;
			case 1: move(200, 200);break;				            //角落，前进
			case 2: move(-200, -200);delay_ms(800);break; 	        //角落，后退
			case 3: move(-200, 200);delay_ms(900); break; 	        //前对台，旋转180度
			case 4: move(200, 200);delay_ms(500);move(-450, -450);delay_ms(1200);move(0, 0);delay_ms(200);if(L1>=33)move(300, 300);delay_ms(300); break; 	//后对台,上台
			case 5: move(200, -200);delay_ms(400);stop(0);break;  	//转90
			case 6: move(150, -150);break;  						//慢转调整方向
		}
	}
}

void fist_up_stage(void)   //首次上台
{
	move(200,200);
	delay_ms(250);
	move(0,0);
	delay_ms(50);
	move(-400,-400);
	delay_ms(800);
	move(0,0);
	delay_ms(100);
	move(300,-300);	
	delay_ms(200);
}

int stage_inspect()		//台下识别函数
{
	if(((R1>=33&&L1>=33)||(L6>=33||R6>=33))&&((L4>=33&&R4<33)||(R4>=33&&L4<33)))
	{
		if(L6>=33&&R1<33&&L1<33){return 1;} //角落里，后对板
		else if(L6<33&&R1>=33&&L1>=33){return 2;}//角落里，前对板
		else {return 6;}
	}
	else if((R1>=33&&L1>=33&&(L6>=33||R6>=33)||(L4>=33&&R4>=33)||(L1>=33&&L5>=33)||(R1>=33&&R5>=33)))
	{
		if(R1>=33&&L1>=33&&L7>=33&&L6>=33&&L4<33&&R4<33) {return 3;}//走廊里，前对台  
		else if(R1>=33&&L1>=33&&L7<=33&&L6>=33&&L4<33&&R4<33){return 4;}//走廊里，后对台   
		else if(L4>=33&&R4>=33&&R1<33&&L1<=33&&L6<33){return 5;}//走廊里，左右对板
		else {									  return 6;}
	}
	if(R1>=33&&L1>=33&&L7<=33&&L6>=33&&L4<33&&R4<33){return 4;}//走廊里，后对台   
	else{return 0;}
}

int stage()			//防掉台     k1左   k2右   在台上为0空为1
{
	if	   ((k1==1)&&(k2==1))		{return 1;}// 全空，直退掉头													
	else if((k1==0)&&(k2==1))		{return 2;}// 左无右有，退左转90度
	else if((k1==1)&&(k2==0))		{return 3;}// 左有右无，退右转90度
	else 							{return 0;}// 在擂台上
}

// int stage()			//防掉台     k1左   k2右   在台上为0空为1
// {
// 	if(((k1==0)&&(k2==0)))			{return 1;}// 全空，直退掉头													
// 	else if((k1==1)&&(k2==0))		{return 2;}// 左无右有，退左转90度
// //	else if((k1==0)&&(k2==1))		{return 3;}// 左有右无，退右转90度
// 	else 							{return 0;}// 在擂台上
// }

int xundi()			//寻找敌人位置
{
	u8 L=0;
    
	if(py==1)
        {L=39;}
    else
        {L=28;}  

	if(R1<L&& R2<L&& R3<L&& R4<L&& R5<L&& R6<L&& L1<L&& L2<L&& L3<L&& L4<L&& L5<L&& L6<L)
	{
		return 0;															//未进入攻击范围
	}
	else
	{
		if     (L1>=L||R1>=L)							{return 1 ;}        //前  
		else if(L2>=L&&L1>=L)						    {return 1 ;}		//前左和前
		else if(R1>=L&&R2>=L)						    {return 1 ;}		//前右和前
		else if(L2>=L)									{return 2 ;}		//前左
		else if(R2>=L)									{return 3 ;}		//前右
		else if(L3>=L)									{return 4 ;}		//左前
		else if(R3>=L)									{return 5 ;}		//右前
		else if(L4>=L)									{return 6 ;}		//左
		else if(R4>=L)									{return 7 ;}		//右  
		else if(L5>=L)									{return 8 ;}		//后左
		else if(R5>=L)									{return 9 ;}		//后右
		else if(R6||L6>=L)							    {return 10;}	    //正后 
		else											{return 0 ;}		//未进入攻击范围
	}
}

void tuixiatai()
{
	int t=0;
	u16 s=0;
	
	while(1)//进攻
	{    
		if(stage()==0&&(L1>40||R1>40)&&R6<32&&L6<32&&L4<32&&R4<32)
		{
			if(py==0){s=470;}else{s=390;}
			move(s,s);
		}
		else if(stage()>0&&(L1>40||R1>40))
		{
			move(0,0);delay_ms(200);
			if(py==1){move(-200,-200);delay_ms(400);}stop(10);
			while(t<260&&xundi()==0){move(0,0);t++;}t=0;
			break;
		}
		else {break;}
	}
}

void stop(u16 s)
{
	move(0,0);
	if(s){delay_ms(s);}
}

int xun()
{
	if(R1<30&&R2<30)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void move(int Rs,int Ls)
{
    Motor_LSpeed(Ls*1.5);
    Motor_RSpeed(Rs*1.5);
}

uint16_t F_Distance(uint8_t ch)
{
	uint16_t temp = 0;
	for(uint8_t i = 0; i <= 3;i ++)
	{
		temp += AD_Value[ch];
		Delay_us(25);
	} 
	return (temp/3)/D_Factor;
}
