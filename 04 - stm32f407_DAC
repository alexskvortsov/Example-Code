#include 	"stm32f4xx.h"
#include  "stm32f4xx_gpio.h"
#include  "stm32f4xx_sdio.h"
#include  "stm32f4xx_dac.h"

#include  "stm32f4xx_rcc.h"
#include  "stm32f4xx_rng.h"

#include  "delay.h"
#include  "config.h"
#include  "gpio.h"


//Time
void SysTick_Handler(void);
void delay_ms(uint16_t delay_temp);


//Pin DAC_OUT1	PA4
//Pin DAC_OUT2	PA5



void Config_Simple_DAC() 
{
	//Create Struct
	GPIO_InitTypeDef GPIO_Init_DAC;
	DAC_InitTypeDef USER_Init_DAC;
		
	//Config Pin
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_Init_DAC.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init_DAC.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_DAC.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_DAC.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_DAC.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_Init_DAC);

	
	//Config Rcc_DAC
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	
	USER_Init_DAC.DAC_Trigger = DAC_Trigger_None;
	USER_Init_DAC.DAC_WaveGeneration = DAC_WaveGeneration_None;
	USER_Init_DAC.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	USER_Init_DAC.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &USER_Init_DAC);
	
	DAC_Cmd(DAC_Channel_1, ENABLE);		
}



void TIM4_IRQHandler(void)
{
	uint32_t rnd;
	
	
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		
		rnd = RNG_GetRandomNumber();
		
		DAC_SetChannel1Data(DAC_Align_12b_R, (uint16_t)rnd&0x0FFF); 
	}
}

void Config_Noise_DAC()
{
	//Create Struct
	GPIO_InitTypeDef GPIO_Init_DAC;
	DAC_InitTypeDef USER_Init_DAC;
	TIM_TimeBaseInitTypeDef TIM_Time_user;
	
	
	//Config Pin
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_Init_DAC.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init_DAC.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_DAC.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_DAC.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_DAC.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_Init_DAC);

	
	//Config Rcc_DAC
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	
	USER_Init_DAC.DAC_Trigger = DAC_Trigger_None;
	USER_Init_DAC.DAC_WaveGeneration = DAC_WaveGeneration_None;
	USER_Init_DAC.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bits9_0;
	USER_Init_DAC.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &USER_Init_DAC);
	
	DAC_Cmd(DAC_Channel_1, ENABLE);	
	
	
	//Config Timer for Noise
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_Time_user.TIM_Prescaler = 20-1;
	TIM_Time_user.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_Time_user.TIM_Period = 10;
	TIM_Time_user.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4, &TIM_Time_user);
	
	NVIC_EnableIRQ(TIM4_IRQn);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	//TIM_SelectOutputTrigger(TIM4,  TIM_TRGOSource_Update);
	
	TIM_Cmd(TIM4, ENABLE);	
}


int main()
{  

	
 SystemCoreClockUpdate();
 SysTick_Config(SystemCoreClock/1000);//1 ms
	
	//Simple_DAC === A*4095/3000 - datasheet
	Config_Simple_DAC();
	DAC_SetChannel1Data(DAC_Align_12b_R, 1021*1.365); // 0,999
	
	//Noise_DAC
	//RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
	//RNG_Cmd(ENABLE); 
	
	while(1)
	{
	
	}
}
