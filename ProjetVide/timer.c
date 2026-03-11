#include <stdio.h>
#include "stm32f10x.h"
#include "timer.h"

uint32_t *dummy_address_1 = (uint32_t *) 0x20001000;
uint32_t *dummy_address_2 = (uint32_t *) 0x20002000;


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
	
	uint32_t * current_PSP  = (uint32_t*) __get_PSP();
	
	if (alternate_dummy) {
		dummy_address_2 = current_PSP;
		__set_PSP( (uint32_t) dummy_address_1); // +6
		
	} else {
		dummy_address_1 = current_PSP;
		__set_PSP((uint32_t) dummy_address_2); // +6
	}
}


void Processor_Mode_Init() {
	
	__set_PSP((uint32_t)dummy_address_1);
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
	// 																	xPSR, 								PC, 							LR, 			R12, 	R3, 		R2, 	R1, 	R0
	uint32_t registervalues1[8] 	= {0x01000000, (uint32_t) Dummy_function_1, 0xFFFFFFFD, 0x01, 0x02, 0x03, 0x04, 0x05};
	uint32_t registervalues2[8] 	= {0x01000000, (uint32_t) Dummy_function_2, 0xFFFFFFFD, 0x06, 0x07, 0x08, 0x09, 0x0A};
	
	
	
	// Dummy 1 init
	for (int i = 0; i < 8; i++) {
		*(--dummy_address_1) = registervalues1[i];
	}
	
	
	
	// Dummy 2 init
	for (int i = 0; i < 8; i++) {
		*(--dummy_address_2) = registervalues2[i];
	}
	
	
}

