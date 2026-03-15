#include <stdio.h>
#include "stm32f10x.h"
#include "timer.h"

// PSP Stack frames
uint32_t *dummy_address_1 = (uint32_t *) 0x20002000;
uint32_t *dummy_address_2 = (uint32_t *) 0x20004000;

uint32_t *dummy_psp_1;
uint32_t *dummy_psp_2;


void SysTick_Init() {
	// Set reload value to 72000
	SysTick->LOAD = 71999;
	
	// Init at "0"
	SysTick->VAL = SysTick->LOAD;
	
	// enable SysTick, exception request and use the internal clock
	SysTick->CTRL |= SysTick_CTRL_ENABLE + SysTick_CTRL_TICKINT + SysTick_CTRL_CLKSOURCE;
}

int alternate_dummy = 1;
int startup = 1;


void SysTick_Handler ( void ) {
	if (startup) {
		startup = 0;
		__set_PSP((uint32_t) dummy_psp_2);
		return;
	}
	
	
	
	if (alternate_dummy) {
		alternate_dummy = 0;
		 dummy_psp_2 = (uint32_t *) __get_PSP();
		__set_PSP( (uint32_t) dummy_psp_1);
		
	} else {
		alternate_dummy = 1;
		dummy_psp_1 = (uint32_t *)__get_PSP();
		__set_PSP((uint32_t) dummy_psp_2);
	}
	__set_CONTROL(3);
}


void Processor_Mode_Init() {
	
	__set_PSP((uint32_t) dummy_psp_1);
	// Switch Thread mode to unprivileged and to PSP
	// __get_CONTROL() | 0x3
	__set_CONTROL(3);
	
}

int a = 0;
void Dummy_function_1() {
	a = 0;
	while(1) {
		a++;
		
	}
}

void Dummy_function_2() {
	while(1) {
		
	}
}

void Stack_Init_Dummies() {
	// Our init values
	// 																	xPSR, 								PC, 							LR, 			R12, 	R3, 		R2, 	R1, 	R0
	uint32_t registervalues1[8] = {
        0x00000000, // R0
        0x00000001, // R1
        0x00000002, // R2
        0x00000003, // R3
        0x0000000C, // R12
        0xFFFFFFFD, // LR (EXC_RETURN: return to Thread mode, use PSP, unprivileged)
        (uint32_t)Dummy_function_1, // PC
        0x01000000  // xPSR (Thumb bit set)
    };
	uint32_t registervalues2[8] = {
			0x00000000, // R0
			0x00000010, // R1
			0x00000020, // R2
			0x00000030, // R3
			0x000000C0, // R12
			0xFFFFFFFD, // LR
			(uint32_t)Dummy_function_2, // PC
			0x01000000  // xPSR
	};

		
	// Move down by 8 words (32 bytes) for the stack frame
	dummy_psp_1 = dummy_address_1 - 8;
	dummy_psp_2 = dummy_address_2 - 8;
	
	
	// Dummy init
	for (int i = 0; i < 8; i++) {
        dummy_psp_1[i] = registervalues1[i];
        dummy_psp_2[i] = registervalues2[i];
    }
}

