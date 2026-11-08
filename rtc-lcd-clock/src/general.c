#include "general.h"

//********FUNCTION-PROTOTYPES***********<<
void InitLedGpios(); 
//void Delay(__IO uint32_t time);
uint32_t Config_Systick_168MHz();
uint32_t Config_Systick_INT_CLK();
void InitGPIOs();
/**** MICROPROCESSOR LAB ********/
/**** PROJECT BY GROUP 1 *******/


/***** FUNCTION FOR INITIALIZATION of RTC 1307 ********/
void Init_RTC(void);

void Init_RTC(void){
TM_DS1307_Time_t time; 
//Day 3, 15th Nov 2023, 00:53:00
time.hours = 0 ;
time.minutes = 54;
time.seconds = 0;
time.date = 15;
time.day = 3;
time.month = 11;
time.year = 23;
TM_DS1307_SetDateTime(&time);
    
TM_DS1307_EnableOutputPin(TM_DS1307_OutputFrequency_4096Hz);
 TM_DS1307_Time_t time2;

}
//**************************************
extern __IO uint32_t TimingDelay;
bool gsm_active_flag = false;

//============INITIALIZE-ONBOARD-LEDs==========<<
void InitLedGpios()
{

  //*****ENABLE-GPIO-CLOCK**************<<
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  //*******GPIO-CONFIGURATIONN**********<<
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Pin = LED_GREEN | LED_ORANGE | LED_RED | LED_BLUE;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
   //*****INITIALIZE-GPIO-PERIPHERAL*****<<
  GPIO_Init(GPIOD, &GPIO_InitStruct);
  
// NOTES: GPIO_SetBits(GPIOD, LED_GREEN);   
//      : GPIO_ResetBits(GPIOD, LED_GREEN);
//      : GPIO_ToggleBits(GPIOD, LED_GREEN);
}


void InitGPIOs()
{
// Initialize your Push Button here
  // ************ Push Button *****************//
  
  //*************** ENABLING GPIO CLOCK *******************//
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);
  
  // ************** CREATING THE OBJECT ***************//
  GPIO_InitTypeDef GPIO_PushButton_Struct;
  
  //**************** INITIALIZING *******************//
  GPIO_PushButton_Struct.GPIO_Pin = PUSHBUTTON;
  GPIO_PushButton_Struct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_PushButton_Struct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_PushButton_Struct.GPIO_OType = GPIO_OType_PP;
  GPIO_PushButton_Struct.GPIO_PuPd = GPIO_PuPd_DOWN;
  
  //********** INITIALIZE-GPIO-PERIPHERAL ***** //
  GPIO_Init(GPIOA , &GPIO_PushButton_Struct);
  
   
}

/*****
void Delay(__IO uint32_t time)
{
  TimingDelay = time;
  while(TimingDelay != 0);
}

****/
uint32_t Config_Systick_168MHz()
{
  //NOTES: 168,000,000 ticks in 1 Sec
  //     : 168,000 ticks in 1 mSec so (SystemCoreClock/1000)
return SysTick_Config(SystemCoreClock/1000); 
}

uint32_t Config_Systick_INT_CLK()
{
uint32_t returnCode; 
RCC_ClocksTypeDef RCC_Clocks;
RCC_GetClocksFreq(&RCC_Clocks);
returnCode =SysTick_Config(RCC_Clocks.HCLK_Frequency/1000); 
return returnCode;
}



