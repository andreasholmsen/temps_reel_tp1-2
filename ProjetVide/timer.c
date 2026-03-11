#include <stdio.h>
#include "stm32f10x.h"
#include "timer.h"

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

int alternate_dummy = 0;
	
void SysTick_Handler ( void ) {
	alternate_dummy = (alternate_dummy + 1) % 2;
	
	
	if (alternate_dummy) {
		__set_PSP(0x20001000);
		
	} else {
		__set_PSP(0x20002000);
	}
}


void Processor_Mode_Init() {
	
	__set_PSP(0x20000400);
	// Switch Thread mode to unprivileged and to PSP
	// __get_CONTROL() | 0x3
	__set_CONTROL(__get_CONTROL() | 0x3);
	
}

int a = 0;
void Dummy_function_1() {
	while(1) a++;
}

int b  =0;
void Dummy_function_2() {
	while(1) b++;
}

void Stack_Init_Dummies() {
	// Our init values
	// xPSR, PC, LR, R12, R3, R2, R1, R0
	uint32_t registervalues1[7] 	= {0x01000000, (uint32_t) Dummy_function_1, 0xFFFFFFFD, 0x00, 0x00, 0x00, 0x00};
	uint32_t registervalues2[7] 	= {0x01000000, (uint32_t) Dummy_function_2, 0xFFFFFFFD, 0x00, 0x00, 0x00, 0x00};
	
	
	// Start point, dummy_1 and dummy_2
	uint32_t * dummy_1_psp = (uint32_t *) 0x20001000;
	uint32_t * dummy_2_psp = (uint32_t *) 0x20002000;
	
	
	// Dummy 1 init
	for (int i = 0; i < 7; i++) {
		dummy_1_psp += 1;
		*(dummy_1_psp) = registervalues1[i];
	}
	
	
	
	// Dummy 2 init
	for (int i = 0; i < 7; i++) {
		dummy_2_psp += 1;
		*(dummy_2_psp) = registervalues2[i];
	}
	
	while (1)
	{
	}
	
	
}

