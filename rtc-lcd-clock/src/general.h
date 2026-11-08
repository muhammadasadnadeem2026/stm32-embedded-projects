#ifndef __GENERAL_H__
#define __GENERAL_H__

#include <stdio.h>
#include "stdint.h"
#include "string.h"
#include "stdbool.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_hd44780.h"
#include "defines.h"
#include "tm_stm32f4_i2c.h"
#include "tm_stm32f4_ds1307.h"
#include "defines.h"
//#include "tm_stm32f4_adc.h"
//#include "tm_stm32f4_lis302dl_lis3dsh.h"


#define LED_GREEN GPIO_Pin_12
#define LED_ORANGE GPIO_Pin_13
#define LED_RED GPIO_Pin_14
#define LED_BLUE GPIO_Pin_15
#define PUSHBUTTON GPIO_Pin_0

//******* FUNCTION PROTOTYPE **********//
void InitGPIOs();
void InitLedGpios();  
//void Delay(__IO uint32_t time);
uint32_t Config_Systick_168MHz();
uint32_t Config_Systick_INT_CLK();

/***** FUNCTION FOR INITIALIZATION of RTC 1307 ********/

void Init_RTC(void);

#endif /* __GENERAL_H__ */
