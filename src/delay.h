/**
  ******************************************************************************
	THIS DELAY LIBRARY IS NO USE SYSTICK INTERRUPT, JUST COUNTS THE CLOCK.
	Thanks Mr.Yohanes Erwin Setiawan for his SysTick-interrupt-based delay library.
	Thanks my lecturers Mr.Ha Huynh and Mr.Hoan Phan for their supporting
    By : hatodev	
	Use this library if you don't want to be in trouble with NVIC priorities.
  ******************************************************************************
  */
	
#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

////Define Clocks per micro second (CPUS)
#define CPUS SystemCoreClock/1000000

void DelayUs(uint32_t us);
void DelayMs(uint32_t ms);

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
