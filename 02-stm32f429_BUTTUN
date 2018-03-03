/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"		
	
/* Private define ------------------------------------------------------------*/
#define RED_ON()			GPIO_SetBits(GPIOG, GPIO_Pin_14)
#define RED_OFF()			GPIO_ResetBits(GPIOG, GPIO_Pin_14)	
#define GREEN_ON()			GPIO_SetBits(GPIOG, GPIO_Pin_13)	
#define GREEN_OFF()			GPIO_ResetBits(GPIOG, GPIO_Pin_13)

#define BUTTON_A0()			GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)

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
void User_Button(void);

/* Main ---------------------------------------------------------------------*/
int main (void)
{
		//168Mhz
		SysTick_Config(SystemCoreClock/1000);//1 ms	
	
		User_Led();
		User_Button();
		
		while(1)
		{
			if (BUTTON_A0() != 0)
			{ RED_ON();GREEN_OFF(); }	
			else
			{ RED_OFF();GREEN_ON(); }
		}
}

/* Use Function  ----------------------------------------------------*/

void User_Led(void)
{
	GPIO_InitTypeDef GPIO_Init_LED;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

	//LED_RED GPIO_Pin_14
	//LED_GREEN GPIO_Pin_14
	GPIO_Init_LED.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOG, &GPIO_Init_LED);
}

void User_Button(void)
{
	GPIO_InitTypeDef GPIO_Init_Button_A;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//USER_BUTTON GPIO_Pin_0	
	GPIO_Init_Button_A.GPIO_Pin = GPIO_Pin_0; 
	GPIO_Init_Button_A.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init_Button_A.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_Button_A.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Button_A.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &GPIO_Init_Button_A);
}	
