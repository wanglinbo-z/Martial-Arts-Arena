#include "stm32f10x.h"
#include "ADC.h"

uint16_t AD_Value[16];

/**
  * ��    ����AD��ʼ��
  * ��    ������
  * �� �� ֵ����
  */
void AD_Init(void)
{
	/*����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	//����ADC1��ʱ��
    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//����GPIOA��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//����GPIOB��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//����GPIOC��ʱ��
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);		//����DMA1��ʱ��
    
	/*����ADCʱ��*/
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);						//ѡ��ʱ��6��Ƶ��ADCCLK = 72MHz / 6 = 12MHz
	
	/*GPIO��ʼ��*/
	GPIO_InitTypeDef GPIO_adc;
    
    // PA0~PA7 8
	GPIO_adc.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_adc.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_adc.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_adc);
    
    // PB0~PB1 2
    GPIO_adc.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_adc.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_adc);
    
    // PC0~PC5 6
    GPIO_adc.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_adc.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_Init(GPIOC, &GPIO_adc);

	/*������ͨ������*/
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);   //����������1��λ�ã�����Ϊͨ��0
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);	  //����������2��λ�ã�����Ϊͨ��1
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);	  //����������3��λ�ã�����Ϊͨ��2
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);   //����������4��λ�ã�����Ϊͨ��3
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_55Cycles5);   //����������5��λ�ã�����Ϊͨ��4
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_55Cycles5);   //����������6��λ�ã�����Ϊͨ��5
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 7, ADC_SampleTime_55Cycles5);   //����������7��λ�ã�����Ϊͨ��6
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 8, ADC_SampleTime_55Cycles5);   //����������8��λ�ã�����Ϊͨ��7
    ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 9, ADC_SampleTime_55Cycles5);   //����������9��λ�ã�����Ϊͨ��8
    ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 10, ADC_SampleTime_55Cycles5);  //����������10��λ�ã�����Ϊͨ��9
    ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 11, ADC_SampleTime_55Cycles5); //����������11��λ�ã�����Ϊͨ��10
    ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 12, ADC_SampleTime_55Cycles5); //����������12��λ�ã�����Ϊͨ��11
    ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 13, ADC_SampleTime_55Cycles5); //����������13��λ�ã�����Ϊͨ��12
    ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 14, ADC_SampleTime_55Cycles5); //����������14��λ�ã�����Ϊͨ��13
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 15, ADC_SampleTime_55Cycles5); //����������15��λ�ã�����Ϊͨ��14 
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 16, ADC_SampleTime_55Cycles5); //����������16��λ�ã�����Ϊͨ��15

	/*ADC��ʼ��*/
	ADC_InitTypeDef ADC_InitStructure;						//����ṹ�����
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		//ģʽ��ѡ�����ģʽ��������ʹ��ADC1
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//���ݶ��룬ѡ���Ҷ���
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//�ⲿ������ʹ���������������Ҫ�ⲿ����
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;		//����ת��
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;			//ɨ��ģʽ
	ADC_InitStructure.ADC_NbrOfChannel = 14;			    //ͨ������Ϊ16
	ADC_Init(ADC1, &ADC_InitStructure);						//���ṹ���������ADC_Init������ADC1

	/*DMA��ʼ��*/
	DMA_InitTypeDef DMA_InitStructure;											//����ṹ�����
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;				//�������ַ�������β�AddrA
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//�������ݿ�ȣ�ѡ����֣���Ӧ16Ϊ��ADC���ݼĴ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			//�����ַ������ѡ��ʧ�ܣ�ʼ����ADC���ݼĴ���ΪԴ
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;					//�洢������ַ���������ADת�������ȫ������AD_Value
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;			//�洢�����ݿ�ȣ�ѡ����֣���Դ���ݿ�ȶ�Ӧ
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;						//�洢����ַ������ѡ��ʹ�ܣ�ÿ��ת�˺������Ƶ���һ��λ��
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;							//���ݴ��䷽��ѡ�������赽�洢����ADC���ݼĴ���ת������
	DMA_InitStructure.DMA_BufferSize = 14;										//ת�˵����ݴ�С��ת�˴���������ADCͨ����һ��
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;								//ģʽ��ѡ��ѭ��ģʽ����ADC������ת��һ��
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;								//�洢�����洢����ѡ��ʧ�ܣ�������ADC���败��ת�˵��洢��
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						    //���ȼ���ѡ���
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);								//���ṹ���������DMA_Init������DMA1��ͨ��1
	
	/*DMA��ADCʹ��*/
	DMA_Cmd(DMA1_Channel1, ENABLE);							//DMA1��ͨ��1ʹ��
	ADC_DMACmd(ADC1, ENABLE);								//ADC1����DMA1���ź�ʹ��
	ADC_Cmd(ADC1, ENABLE);									//ADC1ʹ��

	/*ADCУ׼*/
	ADC_ResetCalibration(ADC1);								//�̶����̣��ڲ��е�·���Զ�ִ��У׼
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET);
    
    /*ADC����*/
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	                //�������ADC��ʼ����������ADC��������ת��ģʽ���ʴ���һ�κ�ADC�Ϳ���һֱ�������ϵع���
}

