#include "stm32f10x.h"
#include "MyI2C.h"

/**
  * @brief  I2Cx��ʼ��
  * @param  None
  */
void MyI2C_Init(void)
{	
	/*����ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);		//����I2C2��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//����GPIOB��ʱ��
	
	/*GPIO��ʼ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*I2C��ʼ��*/
	I2C_InitTypeDef I2C_InitStructure;						//����ṹ�����
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;				//ģʽ��ѡ��ΪI2Cģʽ
	I2C_InitStructure.I2C_ClockSpeed = 400000;				//ʱ���ٶȣ�ѡ��Ϊ50KHz
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;		//ʱ��ռ�ձȣ�ѡ��Tlow/Thigh = 2
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;				//Ӧ��ѡ��ʹ��
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;	//Ӧ���ַ��ѡ��7λ���ӻ�ģʽ�²���Ч
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;				//�����ַ���ӻ�ģʽ�²���Ч
	I2C_Init(MyI2Cx, &I2C_InitStructure);						//���ṹ���������I2C_Init������I2C2
	
	/*I2Cʹ��*/
	I2C_Cmd(MyI2Cx, ENABLE);									//ʹ��I2C2����ʼ����
}

/**
  * @brief  I2C��������
  * @param  SlaveAddr: �ӻ���ַ
  * @param  RegAddr: �Ĵ�����ַ
  * @param  Data: ����
  * @retval None
  */ 
void MyI2C_WriteCommend(uint8_t SlaveAddr, uint8_t RegAddr, uint8_t Data)
{
    // ������ʼ�ź�
    I2C_GenerateSTART(MyI2Cx, ENABLE);
    MyI2C_WaitEvent(I2C_EVENT_MASTER_MODE_SELECT);// �ȴ�EV5

    // ���ʹӻ���ַ
    I2C_Send7bitAddress(MyI2Cx, SlaveAddr, I2C_Direction_Transmitter);
    MyI2C_WaitEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);// �ȴ�EV6

    // ���ͼĴ�����ַ
    I2C_SendData(MyI2Cx, RegAddr);
    MyI2C_WaitEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING);// �ȴ�EV8

    // ��������
    I2C_SendData(MyI2Cx, Data);
    MyI2C_WaitEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED);// �ȴ�EV8_2

    // ����ֹͣ�ź�
    I2C_GenerateSTOP(MyI2Cx, ENABLE);
}

/**
  * @brief  I2C��������
  * @param  SlaveAddr: �ӻ���ַ
  * @param  RegAddr: �Ĵ�����ַ
  * @param  Data: ����
  * @param  count: ���ݳ���
  * @retval None
  */
void MyI2C_WriteData(uint8_t SlaveAddr, uint8_t RegAddr, uint8_t* Data,uint8_t count)
{
    // ������ʼ�ź�
    I2C_GenerateSTART(MyI2Cx, ENABLE);
    MyI2C_WaitEvent(I2C_EVENT_MASTER_MODE_SELECT);// �ȴ�EV5

    // ���ʹӻ���ַ
    I2C_Send7bitAddress(MyI2Cx, SlaveAddr, I2C_Direction_Transmitter);
    MyI2C_WaitEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);// �ȴ�EV6

    // ���ͼĴ�����ַ
    I2C_SendData(MyI2Cx, RegAddr);
    MyI2C_WaitEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING);// �ȴ�EV8

	for (uint8_t i = 0;i < count;i ++){
		// ��������
		I2C_SendData(MyI2Cx, Data[i]);
		MyI2C_WaitEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED);// �ȴ�EV8_2
	}
    // ����ֹͣ�ź�
    I2C_GenerateSTOP(MyI2Cx, ENABLE);
}

/**
  * @brief  I2C��ȡ����
  * @param  SlaveAddr: �ӻ���ַ
  * @param  RegAddr: �Ĵ�����ַ
  * @retval ����
  */
 uint8_t MyI2C_Read(uint8_t SlaveAddr, uint8_t RegAddr)
{
	uint8_t Data;
	 
	I2C_GenerateSTART(MyI2Cx, ENABLE);										//Ӳ��I2C������ʼ����
	MyI2C_WaitEvent(I2C_EVENT_MASTER_MODE_SELECT);					//�ȴ�EV5
	
	I2C_Send7bitAddress(MyI2Cx, SlaveAddr, I2C_Direction_Transmitter);	    //Ӳ��I2C���ʹӻ���ַ������Ϊ����
	MyI2C_WaitEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);	//�ȴ�EV6
	
	I2C_SendData(MyI2Cx, RegAddr);											//Ӳ��I2C���ͼĴ�����ַ
	MyI2C_WaitEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED);				//�ȴ�EV8_2
	
	I2C_GenerateSTART(MyI2Cx, ENABLE);										//Ӳ��I2C�����ظ���ʼ����
	MyI2C_WaitEvent(I2C_EVENT_MASTER_MODE_SELECT);					//�ȴ�EV5
	
	I2C_Send7bitAddress(MyI2Cx, SlaveAddr, I2C_Direction_Receiver);		    //Ӳ��I2C���ʹӻ���ַ������Ϊ����
	MyI2C_WaitEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);		//�ȴ�EV6
	
	I2C_AcknowledgeConfig(MyI2Cx, DISABLE);									//�ڽ������һ���ֽ�֮ǰ��ǰ��Ӧ��ʧ��
	I2C_GenerateSTOP(MyI2Cx, ENABLE);											//�ڽ������һ���ֽ�֮ǰ��ǰ����ֹͣ����
	
	MyI2C_WaitEvent(I2C_EVENT_MASTER_BYTE_RECEIVED);				//�ȴ�EV7
	Data = I2C_ReceiveData(MyI2Cx);											//�������ݼĴ���
	
	I2C_AcknowledgeConfig(MyI2Cx, ENABLE);									//��Ӧ��ָ�Ϊʹ�ܣ�Ϊ�˲�Ӱ��������ܲ����Ķ�ȡ���ֽڲ���
	
	return Data;
}

/**
  * @brief I2C�ȴ��¼�
  * @param I2C_EVENT��I2C�¼�
  * @retval None
  */
void MyI2C_WaitEvent(uint32_t I2C_EVENT)
{
	uint32_t Timeout;
	Timeout = 10000;									//������ʱ����ʱ��
	while (I2C_CheckEvent(MyI2Cx, I2C_EVENT) != SUCCESS)	//ѭ���ȴ�ָ���¼�
	{
		Timeout --;										//�ȴ�ʱ������ֵ�Լ�
		if (Timeout == 0)								//�Լ���0�󣬵ȴ���ʱ
		{
			/*��ʱ�Ĵ�������룬������ӵ��˴�*/
			break;										//�����ȴ���������
		}
	}
}
