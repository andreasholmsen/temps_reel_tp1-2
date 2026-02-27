#include <stdio.h>
#include "stm32f10x.h"

// Handler
void SysTick_Handler ( void );


// Init the SysTick with 1ms period
void SysTick_Init();

// Set Processor to Unprivileged mode with Process Stack using CONTROL register
void Processor_Mode_Init();

void Dummy_function_1();

void Dummy_function_2();

void Stack_Init_Dummies();