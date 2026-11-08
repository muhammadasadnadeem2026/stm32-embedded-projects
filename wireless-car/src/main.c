/**** MICROPROCESSOR LAB ********/
/**** PROJECT BY GROUP 1 *******/
#include "general.h"

int main(void) { 
    /****************  INITIALIZATIONS *******************/
  
    /**** SYSTEM CLOCK *****/
    Config_Systick_168MHz();
    
    /**** DELAY INITIALIZATIONS ****/
    TM_DELAY_Init();
    TIM7_Configuration();
    
    /**** SERVO MOTOR *****/
    TM_SERVO_t Servo1;
    TM_SERVO_Init(&Servo1, TIM2, TM_PWM_Channel_1, TM_PWM_PinsPack_2);
    
    /**** HCSR04 INITIAZATIONS ******/
    TM_HCSR04_t HCSR04;
    TM_HCSR04_Init(&HCSR04, GPIOC, GPIO_PIN_1, GPIOC, GPIO_PIN_3);
    
    /**** BUZZER INITIALIZATIONS *****/
    BuzzerInit();
    
    /**** LED INITIALIZATIONS *****/
    InitLedGpios();
    Init_USART();
    
    /***** VARIIABLE INITIALIZATIONS *****/
    float distance_cm = 0;   // READING FROM ULTRASONIC SENSOR 
    uint8_t forward = 0 ;
    uint8_t reverse = 0;
    uint8_t left = 0 ;
    uint8_t right = 0 ;
    uint8_t autoManual = 0;  // SAVE THE STATE OF THE CAR 
    uint8_t IR1 = 1;
    uint8_t IR2 = 1;
 __IO uint32_t start_time;
 __IO uint32_t end_time;
  STATE state = IDLE ;
  
     while (1) {
    /// FIRSTLY READING THE AUTO/MANUAL CONTROL OF THE CAR
    autoManual = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7);
    
        /***** PROJECT BY ABSOLUTE ZERO  *****/
    switch(autoManual) {
      
    // PROCEED ACCORDING TO THE GIVEN INSTRUCTIONS FROM THE WiFi Module
    case 0:
      IR1 = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_9) ;  // READ THE LEFT IR SENSOR 
      IR2 = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10) ; // READ THE RIGHT IR SENSOR
      
      /// IF IR1 AND IR2 BOTH ARE TRUE THEN STOP THE CAR
      if(IR1 && IR2)
      GPIO_ResetBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13);
      
      /// ROTATE TO LEFT SIDE
      else if(IR1 && !(IR2)){
        GPIO_ResetBits(GPIOD,GPIO_Pin_12);
      }
      /// ROTATE TO RIGHT SIDE
      else if(IR2 && !(IR1)){
        GPIO_SetBits(GPIOD,GPIO_Pin_12);
        GPIO_ResetBits(GPIOD,GPIO_Pin_13);
      }
      /// MOVE FORWARD DIRECTION
      else
        GPIO_SetBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13);
      break;
      
                     // MANUAL CONTROL  
    
        /***** PROJECT BY ABSOLUTE ZERO  *****/

    case 1:
             /// GET THE READINGS FROM WiFi MODULE
      forward = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) ;
      reverse = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) ;
      left = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) ;
      right = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) ;
      
      /// FORWARD IF FORWARD BUTTON IS PRESSED ON THE APP 
      if (forward)
      GPIO_SetBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13); //D12 -> IN1 , D13 -> IN4
      
      /// REVERSE IF REVERSE BUTTON IS PRESSED ON THE APP 
      else if(reverse)
        GPIO_SetBits(GPIOD,GPIO_Pin_14 | GPIO_Pin_15 );// D14 -> IN2 , D15 ->  IN3
      
      /// LEFT IF LEFT BUTTON IS PRESSED ON THE APP 
      else if(left)
        GPIO_SetBits(GPIOD,GPIO_Pin_12);
      
      /// RIGHT IF RIGHT BUTTON IS PRESSED ON THE APP 
      else if(right)
        GPIO_SetBits(GPIOD,GPIO_Pin_13);
      
                   /// STOP THE CAR
      else 
      GPIO_ResetBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
    }
    
    // IF DISTANCE IS LESS THAN 10 CM TURN ON THE BUZZER
    distance_cm = TM_HCSR04_Read(&HCSR04);
    if(distance_cm < 10.0){
    GPIO_SetBits(GPIOD ,BUZZER);
    }
else{
switch(state){
            /// TIMER DELAY
case IDLE:
  
  /// ROTATE THE SERVO MOTOR TO 0 DEGREE
  TM_SERVO_SetDegrees(&Servo1, 0);
  state = ACTIVE;
  start_time = Read1ms();
  break;
  case ACTIVE:
    
    /// ROTATE THE SERVO MOTOR TO 45 DEGREE
    if(Diff1ms(start_time) > 250)
    TM_SERVO_SetDegrees(&Servo1, 45);
    
    /// ROTATE THE SERVO MOTOR TO 90 DEGREE
    if(Diff1ms(start_time) > 500)
    TM_SERVO_SetDegrees(&Servo1, 90);
    
    /// ROTATE THE SERVO MOTOR TO 135 DEGREE
    if(Diff1ms(start_time) > 750 )
    TM_SERVO_SetDegrees(&Servo1, 135);
    
    /// ROTATE THE SERVO MOTOR TO 180 DEGREE
    if(Diff1ms(start_time) > 1000){
    TM_SERVO_SetDegrees(&Servo1, 180);
    state = PASSIVE;
    start_time = Read1ms();
    }
    break;
  case PASSIVE:
    /// ROTATING THE SERVO MOTOR ANTICLOCK WISE DIRECTION

    if(Diff1ms(start_time) > 1000){ 
      TM_SERVO_SetDegrees(&Servo1, 0);
      state = IDLE;
    }
    
    /// ROTATE THE SERVO MOTOR TO 135 DEGREE
    if(Diff1ms(start_time) > 250)
    TM_SERVO_SetDegrees(&Servo1, 135);
    
    /// ROTATE THE SERVO MOTOR TO 90 DEGREE
    if(Diff1ms(start_time) > 500)
    TM_SERVO_SetDegrees(&Servo1, 90);
    
    /// ROTATE THE SERVO MOTOR TO 45 DEGREE
    if(Diff1ms(start_time) > 750)
    TM_SERVO_SetDegrees(&Servo1, 45);
    break;
  }
    GPIO_ResetBits(GPIOD ,BUZZER); // TURN OFF THE BUZZER
   }
  }             
}
