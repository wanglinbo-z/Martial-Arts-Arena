#include "stm32f10x.h"                  // Device header
#include "MyFLASH.h"
#include "sys.h"

#define STORE_START_ADDRESS		0x0807F800		//�洢����ʼ��ַ
#define STORE_COUNT				512				//�洢���ݵĸ���

uint16_t Store_Data[STORE_COUNT];				//����SRAM����

/**
  * ��    ���������洢ģ���ʼ��
  * ��    ������
  * �� �� ֵ����
  */
void Store_Init(void)
{
	/*�ж��ǲ��ǵ�һ��ʹ��*/
	if (MyFLASH_ReadHalfWord(STORE_START_ADDRESS) != 0xA5A5)	//��ȡ��һ�����ֵı�־λ��if��������ִ�е�һ��ʹ�õĳ�ʼ��
	{
		MyFLASH_ErasePage(STORE_START_ADDRESS);					//����ָ��ҳ
		MyFLASH_ProgramHalfWord(STORE_START_ADDRESS, 0xA5A5);	//�ڵ�һ������д���Լ��涨�ı�־λ�������ж��ǲ��ǵ�һ��ʹ��
		for (uint16_t i = 1; i < STORE_COUNT; i ++)				//ѭ��STORE_COUNT�Σ����˵�һ����־λ
		{
			MyFLASH_ProgramHalfWord(STORE_START_ADDRESS + i * 2, 0x0000);		//���˱�־λ����Ч����ȫ����0
		}
	}
	
	/*�ϵ�ʱ�����������ݼ��ػ�SRAM���飬ʵ��SRAM����ĵ��粻��ʧ*/
	for (uint16_t i = 0; i < STORE_COUNT; i ++)					//ѭ��STORE_COUNT�Σ�������һ����־λ
	{
		Store_Data[i] = MyFLASH_ReadHalfWord(STORE_START_ADDRESS + i * 2);		//����������ݼ��ػ�SRAM����
	}
}

/**
  * ��    ���������洢ģ�鱣�����ݵ�����
  * ��    ������
  * �� �� ֵ����
  */
void Store_Save(void)
{
	MyFLASH_ErasePage(STORE_START_ADDRESS);				//����ָ��ҳ
	for (uint16_t i = 0; i < STORE_COUNT; i ++)			//ѭ��STORE_COUNT�Σ�������һ����־λ
	{
		MyFLASH_ProgramHalfWord(STORE_START_ADDRESS + i * 2, Store_Data[i]);	//��SRAM��������ݱ��ݱ��浽����
	}
}

/**
  * ��    ���������洢ģ�齫������Ч������0
  * ��    ������
  * �� �� ֵ����
  */
void Store_Clear(void)
{
	for (uint16_t i = 1; i < STORE_COUNT; i ++)			//ѭ��STORE_COUNT�Σ����˵�һ����־λ
	{
		Store_Data[i] = 0x0000;							//SRAM������Ч������0
	}
	Store_Save();										//�������ݵ�����
	
	Sys_Rest();
}
