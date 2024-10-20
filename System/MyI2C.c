#include "stm32f10x.h"
#include "MyI2C.h"

/**
  * @brief  I2Cx初始化
  * @param  None
  */
void MyI2C_Init(void)
{	
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);		//开启I2C2的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOB的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*I2C初始化*/
	I2C_InitTypeDef I2C_InitStructure;						//定义结构体变量
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;				//模式，选择为I2C模式
	I2C_InitStructure.I2C_ClockSpeed = 400000;				//时钟速度，选择为50KHz
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;		//时钟占空比，选择Tlow/Thigh = 2
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;				//应答，选择使能
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;	//应答地址，选择7位，从机模式下才有效
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;				//自身地址，从机模式下才有效
	I2C_Init(MyI2Cx, &I2C_InitStructure);						//将结构体变量交给I2C_Init，配置I2C2
	
	/*I2C使能*/
	I2C_Cmd(MyI2Cx, ENABLE);									//使能I2C2，开始运行
}

/**
  * @brief  I2C发送数据
  * @param  SlaveAddr: 从机地址
  * @param  RegAddr: 寄存器地址
  * @param  Data: 数据
  * @retval None
  */ 
void MyI2C_WriteCommend(uint8_t SlaveAddr, uint8_t RegAddr, uint8_t Data)
{
    // 发送起始信号
    I2C_GenerateSTART(MyI2Cx, ENABLE);
    MyI2C_WaitEvent(I2C_EVENT_MASTER_MODE_SELECT);// 等待EV5

    // 发送从机地址
    I2C_Send7bitAddress(MyI2Cx, SlaveAddr, I2C_Direction_Transmitter);
    MyI2C_WaitEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);// 等待EV6

    // 发送寄存器地址
    I2C_SendData(MyI2Cx, RegAddr);
    MyI2C_WaitEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING);// 等待EV8

    // 发送数据
    I2C_SendData(MyI2Cx, Data);
    MyI2C_WaitEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED);// 等待EV8_2

    // 发送停止信号
    I2C_GenerateSTOP(MyI2Cx, ENABLE);
}

/**
  * @brief  I2C发送数据
  * @param  SlaveAddr: 从机地址
  * @param  RegAddr: 寄存器地址
  * @param  Data: 数据
  * @param  count: 数据长度
  * @retval None
  */
void MyI2C_WriteData(uint8_t SlaveAddr, uint8_t RegAddr, uint8_t* Data,uint8_t count)
{
    // 发送起始信号
    I2C_GenerateSTART(MyI2Cx, ENABLE);
    MyI2C_WaitEvent(I2C_EVENT_MASTER_MODE_SELECT);// 等待EV5

    // 发送从机地址
    I2C_Send7bitAddress(MyI2Cx, SlaveAddr, I2C_Direction_Transmitter);
    MyI2C_WaitEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);// 等待EV6

    // 发送寄存器地址
    I2C_SendData(MyI2Cx, RegAddr);
    MyI2C_WaitEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING);// 等待EV8

	for (uint8_t i = 0;i < count;i ++){
		// 发送数据
		I2C_SendData(MyI2Cx, Data[i]);
		MyI2C_WaitEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED);// 等待EV8_2
	}
    // 发送停止信号
    I2C_GenerateSTOP(MyI2Cx, ENABLE);
}

/**
  * @brief  I2C读取数据
  * @param  SlaveAddr: 从机地址
  * @param  RegAddr: 寄存器地址
  * @retval 数据
  */
 uint8_t MyI2C_Read(uint8_t SlaveAddr, uint8_t RegAddr)
{
	uint8_t Data;
	 
	I2C_GenerateSTART(MyI2Cx, ENABLE);										//硬件I2C生成起始条件
	MyI2C_WaitEvent(I2C_EVENT_MASTER_MODE_SELECT);					//等待EV5
	
	I2C_Send7bitAddress(MyI2Cx, SlaveAddr, I2C_Direction_Transmitter);	    //硬件I2C发送从机地址，方向为发送
	MyI2C_WaitEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);	//等待EV6
	
	I2C_SendData(MyI2Cx, RegAddr);											//硬件I2C发送寄存器地址
	MyI2C_WaitEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED);				//等待EV8_2
	
	I2C_GenerateSTART(MyI2Cx, ENABLE);										//硬件I2C生成重复起始条件
	MyI2C_WaitEvent(I2C_EVENT_MASTER_MODE_SELECT);					//等待EV5
	
	I2C_Send7bitAddress(MyI2Cx, SlaveAddr, I2C_Direction_Receiver);		    //硬件I2C发送从机地址，方向为接收
	MyI2C_WaitEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);		//等待EV6
	
	I2C_AcknowledgeConfig(MyI2Cx, DISABLE);									//在接收最后一个字节之前提前将应答失能
	I2C_GenerateSTOP(MyI2Cx, ENABLE);											//在接收最后一个字节之前提前申请停止条件
	
	MyI2C_WaitEvent(I2C_EVENT_MASTER_BYTE_RECEIVED);				//等待EV7
	Data = I2C_ReceiveData(MyI2Cx);											//接收数据寄存器
	
	I2C_AcknowledgeConfig(MyI2Cx, ENABLE);									//将应答恢复为使能，为了不影响后续可能产生的读取多字节操作
	
	return Data;
}

/**
  * @brief I2C等待事件
  * @param I2C_EVENT：I2C事件
  * @retval None
  */
void MyI2C_WaitEvent(uint32_t I2C_EVENT)
{
	uint32_t Timeout;
	Timeout = 10000;									//给定超时计数时间
	while (I2C_CheckEvent(MyI2Cx, I2C_EVENT) != SUCCESS)	//循环等待指定事件
	{
		Timeout --;										//等待时，计数值自减
		if (Timeout == 0)								//自减到0后，等待超时
		{
			/*超时的错误处理代码，可以添加到此处*/
			break;										//跳出等待，不等了
		}
	}
}
