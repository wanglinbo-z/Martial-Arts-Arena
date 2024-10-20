#include "main.h"

uint16_t D_Factor;

void Start_ACT(void)
{
    OLED_Clear();
    OLED_ShowString(0, 0, "Acting...", OLED_8X16);
    OLED_Update();
    
	u16 t=0;
	
    // Ԥ���׶Σ������ȴ�
    if(Store_Data[Status] == 0)// ״̬����
    {
		Delay_ms(1000);
        OLED_ShowString(0, 24, "READY", OLED_8X16);
        OLED_Update();

        while(1){if((R4>60)||(L4>60))break;}

        Store_Data[Status] = 1;
        Store_Save();

        // ��һ������̨
        fist_up_stage();
    }

	OLED_ClearArea(0, 24, 128, 16);
	OLED_ShowString(0, 24, "GO", OLED_8X16);
	OLED_Update();
	
    // ��̨����������Ӧ����
	while(1)
	{
        if (Menu_BackEvent())
		{
            Store_Data[Status] = 0;
            Store_Save();
			Motor_Stop();
            return;
        }
		
        // ̨��ʶ��
		switch(stage_inspect())
		{
			case 0:                     // ̨��
				switch(stage())         // �ŵ�̨
				{
					case 0:             // ����̨��
						switch(0/*xundi()*/) // Ѱ�ҵ���
							{
								case 0 : if(py){move(240,240);}else{move(110,110);}break;      			//δ����������̨Ѱ�ҵ���
								// case 1 : tuixiatai(); break;										//���˳�����ǰ��ִ�н��������������������̨�ᴥ�����޹���
								// case 2 : if(L2>35){move(200,-200);}	else{move(200,200);}break;	    //���˳�����ǰ���ǰ
								// case 3 : if(R2>35){move(-200,200);} else{move(200,200);}break;		//���˳������Һ�ǰ
								// case 4 : move(260,-260);while(t<23&&xun()){t++;}t=0;break; 			//���˳�����ǰ��
								// case 5 : move(-260,260);while(t<23&&xun()){t++;}t=0;break; 			//���˳�����ǰ��
								// case 6 : move(320,-320);while(t<36&&xun()){t++;}t=0;break; 			//���˳�������
								// case 7 : move(-320,320);while(t<36&&xun()){t++;}t=0;break; 			//���˳�������
								// case 8 : move(350,-350);while(t<23&&xun()){t++;}t=0;break; 			//���˳����ں���
								// case 9 : move(-350,350);while(t<23&&xun()){t++;}t=0;break; 			//���˳����ں���
								// case 10: move(-370,370);while(t<23&&xun()){t++;}t=0;break; 			//���˳����ں�
							}break; 
					case 1: move(-450,-450);delay_ms(300);move(-300,300);delay_ms(300);break;  																																											//ǰ��ȫ�գ�ֱ�˵�ͷ			
					case 2: if(R5<=23&&L5<=23){move(-450,-450);delay_ms(300);move(300,-300);delay_ms(300);}
							else{move(-130,-130);delay_ms(100);move(-150,150);delay_ms(200);}break; 	//ǰ���������У�����ת90��
					case 3: if(R5<=23&&L5<=23){move(-450,-450);delay_ms(300);move(-300,300);delay_ms(300);}
							else{move(-130,-130);delay_ms(100);move(150,-150);delay_ms(200);}break; 	//ǰ���������ޣ�����ת90��
				}break;
			case 1: move(200, 200);break;				            //���䣬ǰ��
			case 2: move(-200, -200);delay_ms(800);break; 	        //���䣬����
			case 3: move(-200, 200);delay_ms(900); break; 	        //ǰ��̨����ת180��
			case 4: move(200, 200);delay_ms(500);move(-450, -450);delay_ms(1200);move(0, 0);delay_ms(200);if(L1>=33)move(300, 300);delay_ms(300); break; 	//���̨,��̨
			case 5: move(200, -200);delay_ms(400);stop(0);break;  	//ת90
			case 6: move(150, -150);break;  						//��ת��������
		}
	}
}

void fist_up_stage(void)   //�״���̨
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

int stage_inspect()		//̨��ʶ����
{
	if(((R1>=33&&L1>=33)||(L6>=33||R6>=33))&&((L4>=33&&R4<33)||(R4>=33&&L4<33)))
	{
		if(L6>=33&&R1<33&&L1<33){return 1;} //�������԰�
		else if(L6<33&&R1>=33&&L1>=33){return 2;}//�����ǰ�԰�
		else {return 6;}
	}
	else if((R1>=33&&L1>=33&&(L6>=33||R6>=33)||(L4>=33&&R4>=33)||(L1>=33&&L5>=33)||(R1>=33&&R5>=33)))
	{
		if(R1>=33&&L1>=33&&L7>=33&&L6>=33&&L4<33&&R4<33) {return 3;}//�����ǰ��̨  
		else if(R1>=33&&L1>=33&&L7<=33&&L6>=33&&L4<33&&R4<33){return 4;}//��������̨   
		else if(L4>=33&&R4>=33&&R1<33&&L1<=33&&L6<33){return 5;}//��������Ҷ԰�
		else {									  return 6;}
	}
	if(R1>=33&&L1>=33&&L7<=33&&L6>=33&&L4<33&&R4<33){return 4;}//��������̨   
	else{return 0;}
}

int stage()			//����̨     k1��   k2��   ��̨��Ϊ0��Ϊ1
{
	if	   ((k1==1)&&(k2==1))		{return 1;}// ȫ�գ�ֱ�˵�ͷ													
	else if((k1==0)&&(k2==1))		{return 2;}// �������У�����ת90��
	else if((k1==1)&&(k2==0))		{return 3;}// �������ޣ�����ת90��
	else 							{return 0;}// ����̨��
}

// int stage()			//����̨     k1��   k2��   ��̨��Ϊ0��Ϊ1
// {
// 	if(((k1==0)&&(k2==0)))			{return 1;}// ȫ�գ�ֱ�˵�ͷ													
// 	else if((k1==1)&&(k2==0))		{return 2;}// �������У�����ת90��
// //	else if((k1==0)&&(k2==1))		{return 3;}// �������ޣ�����ת90��
// 	else 							{return 0;}// ����̨��
// }

int xundi()			//Ѱ�ҵ���λ��
{
	u8 L=0;
    
	if(py==1)
        {L=39;}
    else
        {L=28;}  

	if(R1<L&& R2<L&& R3<L&& R4<L&& R5<L&& R6<L&& L1<L&& L2<L&& L3<L&& L4<L&& L5<L&& L6<L)
	{
		return 0;															//δ���빥����Χ
	}
	else
	{
		if     (L1>=L||R1>=L)							{return 1 ;}        //ǰ  
		else if(L2>=L&&L1>=L)						    {return 1 ;}		//ǰ���ǰ
		else if(R1>=L&&R2>=L)						    {return 1 ;}		//ǰ�Һ�ǰ
		else if(L2>=L)									{return 2 ;}		//ǰ��
		else if(R2>=L)									{return 3 ;}		//ǰ��
		else if(L3>=L)									{return 4 ;}		//��ǰ
		else if(R3>=L)									{return 5 ;}		//��ǰ
		else if(L4>=L)									{return 6 ;}		//��
		else if(R4>=L)									{return 7 ;}		//��  
		else if(L5>=L)									{return 8 ;}		//����
		else if(R5>=L)									{return 9 ;}		//����
		else if(R6||L6>=L)							    {return 10;}	    //���� 
		else											{return 0 ;}		//δ���빥����Χ
	}
}

void tuixiatai()
{
	int t=0;
	u16 s=0;
	
	while(1)//����
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
