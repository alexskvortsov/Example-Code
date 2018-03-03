/* Includes ------------------------------------------------------------------*/
#include  "stm32f4xx.h"
#include  "stm32f4xx_gpio.h"		
#include  "stm32f4xx_tim.h"

/* Private define ------------------------------------------------------------*/
#define RED_ON()	    GPIO_SetBits(GPIOD, GPIO_Pin_14)
#define RED_OFF()	    GPIO_ResetBits(GPIOD, GPIO_Pin_14)	
#define BLUE_ON()	    GPIO_SetBits(GPIOD, GPIO_Pin_15)	
#define BLUE_OFF()	  GPIO_ResetBits(GPIOD, GPIO_Pin_15)	
#define	GREEN_ON()	  GPIO_SetBits(GPIOD, GPIO_Pin_12)
#define	GREEN_OFF()	  GPIO_ResetBits(GPIOD, GPIO_Pin_12)
#define	YELLOW_ON()	  GPIO_SetBits(GPIOD, GPIO_Pin_13)
#define	YELLOW_OFF()	GPIO_ResetBits(GPIOD, GPIO_Pin_13)

#define TOGGLE_GREEN()		GPIO_ToggleBits(GPIOD, GPIO_Pin_12)
#define TOGGLE_RED()		  GPIO_ToggleBits(GPIOD, GPIO_Pin_14)

/* SysTick -----------------------------------------------------------------*/
uint16_t delay_count = 0;

void SysTick_Handler(void) //1 ms
{
  if (delay_count > 0) {delay_count--;}
}
void delay_ms(uint16_t delay_temp)
{
  delay_count = delay_temp;
  while(delay_count){}
}

/* Private function prototypes -----------------------------------------------*/
void User_Led(void);
void User_TIM2(void);
void TIM2_IRQHandler(void);

/* Main ---------------------------------------------------------------------*/
int main (void)
{
	
		SysTick_Config(SystemCoreClock/1000);//1 ms	
		User_Led();
		User_TIM2();
		while (1)
		{
			TOGGLE_GREEN();
			delay_ms(1000);
		}
}

/* Use Function  ----------------------------------------------------*/

void User_Led(void)
{
	GPIO_InitTypeDef GPIO_Init_LED;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_Init_LED.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &GPIO_Init_LED);;
}

//Config = 1ms
void User_TIM2(void)
{
	TIM_TimeBaseInitTypeDef TIM_Time_user;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_Time_user.TIM_Prescaler = 20000;
	TIM_Time_user.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_Time_user.TIM_Period = 1000-1;
	TIM_Time_user.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM2, &TIM_Time_user);
	
	NVIC_EnableIRQ(TIM2_IRQn);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	TIM_Cmd(TIM2, ENABLE);
}


void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		TOGGLE_RED();
	}
}
