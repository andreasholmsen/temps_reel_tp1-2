#include <stdio.h>
#include "stm32f10x.h"

void SysTick_Init() {
	// Set reload value to 72000
	SysTick->LOAD = 71999;
	
	// Init at "0"
	SysTick->VAL = SysTick->LOAD;
	
	// enable SysTick, exception request and use the internal clock
	SysTick->CTRL |= SysTick_CTRL_ENABLE;
	SysTick->CTRL |= SysTick_CTRL_TICKINT;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE;
}



void SysTick_Handler ( void ) {
	
}


void Processor_Mode_Init() {
	
	__set_PSP(0x20000400);
	// Switch Thread mode to unprivileged and to PSP
	// __get_CONTROL() | 0x3
	__set_CONTROL(__get_CONTROL() | 0x3);
	
}
