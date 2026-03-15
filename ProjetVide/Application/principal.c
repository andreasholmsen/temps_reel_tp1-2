#include "stm32f10x.h"
#include "timer.h"

extern uint32_t*  dummy_address_1;
extern uint32_t* dummy_address_2;

extern uint32_t *dummy_psp_1;
extern uint32_t *dummy_psp_2;

int main ( void )
{
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ;
	
	GPIOA->CRL &= ~(0xF<<4) ;
	GPIOA->CRL |= (0x2<<4) ;
		
	Stack_Init_Dummies();

	
	SysTick_Init();
	__set_CONTROL(3);

	while (1)
	{
	}
}
