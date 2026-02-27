#include "stm32f10x.h"
#include "timer.h"

int main ( void )
{
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ;
	
	GPIOA->CRL &= ~(0xF<<4) ;
	GPIOA->CRL |= (0x2<<4) ;
	
	
	Stack_Init_Dummies();
	SysTick_Init();
	__set_PSP(0x20000400);
	__set_CONTROL(__get_CONTROL() | 0x2);
	
	//Processor_Mode_Init();
	
	
	
	
	
	while (1)
	{
	}
}
