/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include  "stm32f4xx_gpio.h"		
	
/* Private define ------------------------------------------------------------*/
#define RED_ON()	GPIO_SetBits(GPIOD, GPIO_Pin_14)
#define RED_OFF()	GPIO_ResetBits(GPIOD, GPIO_Pin_14)	
#define BLUE_ON()	GPIO_SetBits(GPIOD, GPIO_Pin_15)	
#define BLUE_OFF()	GPIO_ResetBits(GPIOD, GPIO_Pin_15)	
#define GREEN_ON()	GPIO_SetBits(GPIOD, GPIO_Pin_12)
#define GREEN_OFF()	GPIO_ResetBits(GPIOD, GPIO_Pin_12)
#define YELLOW_ON()	GPIO_SetBits(GPIOD, GPIO_Pin_13)
#define YELLOW_OFF()	GPIO_ResetBits(GPIOD, GPIO_Pin_13)

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


/* Private macro prototypes -----------------------------------------------*/
uint32_t PortVal = 0;
uint32_t i_count = 0;


/* Main ---------------------------------------------------------------------*/
int main (void)
{

		SysTick_Config(SystemCoreClock/1000);//1 ms	
		LEDs_Config();
		
		i_count = 0x0FFF;

		while (1)
		{
			PortVal=i_count;
			GPIO_Write(GPIOD, PortVal);
	  		i_count = i_count+0x0FFF;
			delay_ms(DELAY);
		}
}

/* Use Function  ----------------------------------------------------*/

void LEDs_Config(void)
{
	GPIO_InitTypeDef GPIO_Init_LED;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_Init_LED.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &GPIO_Init_LED);
}
