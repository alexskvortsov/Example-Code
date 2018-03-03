/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include  "stm32f4xx_gpio.h"		
	
/* Private define ------------------------------------------------------------*/
#define RED_ON()	GPIO_SetBits(GPIOG, GPIO_Pin_14)
#define RED_OFF()	GPIO_ResetBits(GPIOG, GPIO_Pin_14)	
#define GREEN_ON()	GPIO_SetBits(GPIOG, GPIO_Pin_13)	
#define GREEN_OFF()	GPIO_ResetBits(GPIOG, GPIO_Pin_13)
#define RED_Toggle() 	GPIO_ToggleBits(GPIOG, GPIO_Pin_14)
#define GREEN_Toggle() 	GPIO_ToggleBits(GPIOG, GPIO_Pin_13)

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
void LEDs_Config(void);
void Led_Toggle(void);
void Led_OnOff(void);

/* Main ---------------------------------------------------------------------*/
int main (void)
{
		//168Mhz
		SysTick_Config(SystemCoreClock/1000);//1 ms	
		LEDs_Config();
		
		while (1)
		{
			Led_OnOff();
		}
}

/* Use Function  ----------------------------------------------------*/

void LEDs_Config(void)
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

void Led_Toggle(void)
{
	RED_Toggle();
	delay_ms(500);
	GREEN_Toggle();
	delay_ms(500);
}

void Led_OnOff(void)
{
	RED_ON();
	GREEN_OFF();
	delay_ms(500);
	RED_OFF();
	GREEN_ON();
	delay_ms(500);
}

