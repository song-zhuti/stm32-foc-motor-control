#include "stm32f10x.h"                  // Device header
#include "Periph_Init.h"

/**
  * @brief  配置GPIO外设的初始化，包括所有被使用的引脚
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to gates its clock.
  *   This parameter can be any combination of the following values:
  * @param  NewState: new state of the specified peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval 无返回值
  */
void Perioh_gpioinit(void)
{
  /*开启时钟*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);		      //开启GPIOC的时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		      //开启GPIOB的时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		      //开启GPIOA的时钟
  /*GPIO初始化*/
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;              //推挽输出
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_Init(GPIOC, &GPIO_InitStructure);						            //将PC13引脚初始化为推挽输出

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_Init(GPIOA, &GPIO_InitStructure);						            //将PA1引脚初始化为上拉输入,用于按键输入

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;               //复用推挽输出
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_Init(GPIOA, &GPIO_InitStructure);						            //将PA2引脚初始化为复用推挽输出,用于usart2_tx

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;         //浮空输入
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);						            //将PA3引脚初始化为浮空输入,用于usart2_rx

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_Init(GPIOA, &GPIO_InitStructure);						            //将PA4和PA5引脚初始化为模拟输入,用于ADC采样

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;              //推挽输出
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_Init(GPIOA, &GPIO_InitStructure);						            //将PA6和PA7引脚初始化为推挽输出,用于tim3_ch1、2的PWM输出

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;               //复用推挽输出
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_Init(GPIOA, &GPIO_InitStructure);						            //将PA8、PA9和PA10引脚初始化为复用推挽输出,用于tim1_ch1、2、3的PWM输出          

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;              //推挽输出
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11;
  GPIO_Init(GPIOA, &GPIO_InitStructure);						            //将PA11引脚初始化为推挽输出,用于somplefoc_enable

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;               //复用推挽输出
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_InitStructure);				                //将PB0和PB1引脚初始化为复用推挽输出,用于tim3_ch3、4的PWM输出 		            
//还有PB10和PB11没初始化不知道i2c咋用
}

/**
  * @brief  配置Tim3外设的初始化
  * @retval 无返回值
  */
void Perioh_tim3init(void)
{
  /*开启时钟*/
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);		      //开启TIM3的时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		      //开启TIM2的时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);		      //开启TIM1的时钟
  
  TIM_InternalClockConfig(TIM3);                                //选择TIM3为内部时钟模式
  TIM_InternalClockConfig(TIM2);                                //选择TIM2为内部时钟模式
  TIM_InternalClockConfig(TIM1);                                //选择TIM1为内部时钟模式

  /* 定时器Tim3初始化 */
  TIM_TimeBaseInitTypeDef TIM_InitStructure;
  TIM_TimeBaseStructInit(&TIM_InitStructure);                   //将TIM_InitStructure结构体初始化为默认值
  TIM_InitStructure.TIM_RepetitionCounter = 0;                  //高级定时器才有所以不用
  TIM_InitStructure.TIM_Prescaler = 7200-1;                     //PSC预分频器，将APB1时钟分频为72MHz
  TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;       //计数器模式，向上计数
  TIM_InitStructure.TIM_Period = 5000-1;                        //ARR自动重装载寄存器计数到999时产生中断
  TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;           //输入时钟滤波器分频，这里为1分频
  TIM_TimeBaseInit(TIM3, &TIM_InitStructure);                   //配置定时器Tim3的时基单元

  TIM_InitStructure.TIM_RepetitionCounter = 0;                  //高级定时器才有所以不用
  TIM_InitStructure.TIM_Prescaler = 7200-1;                     //PSC预分频器，将APB1时钟分频为72MHz
  TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;       //计数器模式，向上计数
  TIM_InitStructure.TIM_Period = 10-1;                          //ARR自动重装载寄存器计数到9时产生中断
  TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;           //输入时钟滤波器分频，这里为1分频
  TIM_TimeBaseInit(TIM2, &TIM_InitStructure);                   //配置定时器Tim2的时基单元

  // TIM_OCInitTypeDef TIM_OCInitStructure;
  // TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;             //PWM模式1
  // TIM_OCInitStructure.TIM_OutputState = ;
  // TIM_OCInitStructure.TIM_OutputNState = ;
  // TIM_OCInitStructure.TIM_Pulse = ;
  // TIM_OCInitStructure.TIM_OCPolarity = ;
  // TIM_OCInitStructure.TIM_OCNPolarity = ;
  // TIM_OCInitStructure.TIM_OCIdleState = ;
  // TIM_OCInitStructure.TIM_OCNIdleState = ;
  // TIM_OC1Init(TIM2, &TIM_OCInitStructure);                      //配置定时器Tim2的通道1为PWM模式

  TIM_InitStructure.TIM_RepetitionCounter = 0;                  //高级定时器才有所以不用
  TIM_InitStructure.TIM_Prescaler = 7200-1;                     //PSC预分频器，将APB1时钟分频为72MHz
  TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;       //计数器模式，向上计数
  TIM_InitStructure.TIM_Period = 5000-1;                        //ARR自动重装载寄存器计数到999时产生中断
  TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;           //输入时钟滤波器分频，这里为1分频
  TIM_TimeBaseInit(TIM1, &TIM_InitStructure);                   //配置定时器Tim1的时基单元

  /* 使能定时器Tim3中断 */
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

  /* 使能定时器Tim3 */
  TIM_Cmd(TIM3, ENABLE);
  TIM_Cmd(TIM1, ENABLE);
}

void Perioh_nvicinit(void)
{
  /* NVIC优先级分组 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);              //将NVIC优先级分组为2
  
  /* 配置NVIC */
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;              //选择TIM3中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;    //设置抢占优先级为2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;           //设置子优先级为0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              //使能TIM3中断通道
  NVIC_Init(&NVIC_InitStructure);                              //配置NVIC

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;            //设置NVIC中断通道为USART1
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    //设置NVIC中断通道的抢占优先级为0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;           //设置NVIC中断通道的子优先级为0
  NVIC_Init(&NVIC_InitStructure);                              //初始化NVIC

  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;     //设置NVIC中断通道为DMA1通道1
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;    //设置NVIC中断通道的抢占优先级为1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;           //设置NVIC中断通道的子优先级为0
  NVIC_Init(&NVIC_InitStructure);                              //初始化NVIC
}

/**
 * @brief  配置ADC1外设的初始化
 * @retval 无返回值
 */
void Perioh_ad1init(void)
{
  /*开启时钟*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);          //开启ADC1的时钟

  RCC_ADCCLKConfig(RCC_PCLK2_Div6);                             //将ADC时钟分频为72MHz/6=12MHz

  /* 采样时间的计算t (us)= (采样周期+ 12.5个周期) / ADC时钟频率(单位:MHz) */
  ADC_RegularChannelConfig(ADC1,ADC_Channel_4,1,ADC_SampleTime_55Cycles5); //配置ADC1的规则通道1为PA3,采样时间为55个周期
  ADC_RegularChannelConfig(ADC1,ADC_Channel_5,2,ADC_SampleTime_55Cycles5); //配置ADC1的规则通道2为PA4,采样时间为55个周期

  ADC_InitTypeDef ADC_InitStructure;
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;           //独立模式
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;           //开启连续转换模式
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //不使用外部触发,使用软件触发
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;       //数据右对齐
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;                 //开启扫描模式
  ADC_InitStructure.ADC_NbrOfChannel = 2;                      //转换通道数为2
  ADC_Init(ADC1, &ADC_InitStructure);                          //初始化ADC1

  ADC_Cmd(ADC1, ENABLE);                                       //使能ADC1

  ADC_DMACmd(ADC1, ENABLE);                                    //使能ADC1的DMA功能

  ADC_ResetCalibration(ADC1);                                  //重置校准寄存器
  while(ADC_GetResetCalibrationStatus(ADC1));                  //等待校准寄存器重置完成
  ADC_StartCalibration(ADC1);                                  //开始校准
  while(ADC_GetCalibrationStatus(ADC1));                       //等待校准完成 
}

void Perioh_dma1init(uint32_t peripheaddr,uint32_t memoryaddr,uint16_t buffer_size)
{
  /*开启时钟*/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);           //开启DMA1的时钟

  DMA_InitTypeDef DMA_InitStructure;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)peripheaddr;       //设置DMA1通道1的数据基地址
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//设置DMA1通道1的外设数据宽度为半字(16位)
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;         //设置DMA1通道1的外设地址增量模式为不增量
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)memoryaddr;            //设置DMA1通道1的目的基地址
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;     //设置DMA1通道1的内存数据宽度为半字(16位)
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 //设置DMA1通道1的内存地址增量模式为增量
  DMA_InitStructure.DMA_BufferSize = buffer_size;                         //设置DMA1通道1的缓冲区大小为buffer_size个数据,传输计数器的值
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                      //设置DMA1通道1的数据传输方向为从外设到内存,外设作为数据源
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            //不使用软件触发，使用硬件触发一般应用于外设到存储器
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                         //设置DMA1通道1的工作模式为自动重装，自动重装不可与软件触发同时使用
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;                     //设置DMA1通道1的优先级为高优先级
  DMA_Init(DMA1_Channel1,&DMA_InitStructure);

  DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);              //使能DMA1通道1的传输完成中断

  DMA_Cmd(DMA1_Channel1,ENABLE);                                          //使能DMA1通道1
}
/**
 * @brief 
 *    @note  程序使用时建议加上检查传输完成标志为的函数，并在程序初始化是自动运行一下
 * 
 * @param DMAy_Channelx 
 * @param buffer_size 
 */
void Perioh_dmatransfer(DMA_Channel_TypeDef* DMAy_Channelx,uint16_t buffer_size)
{
  if(DMA_GetFlagStatus(DMA1_FLAG_TC1) == SET)                  //检查DMA1通道1的全局传输完成标志位是否置位
  {
    DMA_ClearFlag(DMA1_FLAG_TC1);                             //清除DMA1通道1的全局传输完成标志位
    DMA_Cmd(DMAy_Channelx,DISABLE);                            //关闭DMAy通道x
    DMA_SetCurrDataCounter(DMAy_Channelx,buffer_size);         //设置DMAy通道x的传输计数器的值为buffer_size
    DMA_Cmd(DMAy_Channelx,ENABLE);                             //使能DMAy通道x
  }
}

void Perioh_usartinit(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);        //开启USART1的时钟

  USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = 115200;                    //设置波特
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;   //设置数据位为8位
  USART_InitStructure.USART_StopBits = USART_StopBits_1;        //设置停止
  USART_InitStructure.USART_Parity = USART_Parity_No;           //无奇偶校验
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //设置收发模式
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件流控制
  USART_Init(USART1, &USART_InitStructure);                     //初始化USART1

}

void USART1_SendByte(uint8_t data)
{
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); //等待发送数据寄存器为空
  USART_SendData(USART1, data);                                //通过USART1发送一个字节的数据
}
