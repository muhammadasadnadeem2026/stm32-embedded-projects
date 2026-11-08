/**** MICROPROCESSOR LAB ********/
/**** PROJECT BY GROUP 1 *******/
#include "general.h"
int main(void) {
   
  /***** INITIALIZATIONS *********/
  TM_DS1307_Init();
  //Initialize system
    InitLedGpios();
    Config_Systick_168MHz();
    //Initialize LCD 16 cols x 2 rows
    TM_HD44780_Init(16 , 2);
    SystemInit();
  
  /****** CUSTOM CHARACTERS ******/  
   uint8_t smileyFace[] = {
       0x00, 0x00, 0x0A, 0x00, 0x11, 0x0E, 0x00, 0x00
    };
   TM_HD44780_CreateChar(0, &smileyFace[0]);
   uint8_t bell[] = {0x00, 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x04, 0x00};  // bell
   TM_HD44780_CreateChar(1, &bell[0]);
uint8_t heart[] = {0x00, 0x00, 0x0A, 0x15, 0x11, 0x0E, 0x04, 0x00};  // Heart
TM_HD44780_CreateChar(2, &heart[0]);
uint8_t robo[] = {0x0E, 0x0E, 0x04, 0x0E, 0x15, 0x04, 0x0A, 0x0A};  // Robo
TM_HD44780_CreateChar(3, &robo[0]);

  /***** VARAIBLES *******/
  char time_T[100];
  char date_D[100];
    
  /****** CREDTIS PRINTING ON THE LCD 16 X 2 *********/
    TM_HD44780_Puts(2,0 ,"PROJECT BY");
    TM_HD44780_Puts(0,1 ,"263/267/284/339");
    Delayms(3000);
    TM_HD44780_Clear();
    TM_HD44780_PutCustom(12, 0, 2);
    Delayms(1000);
    TM_HD44780_Puts(0,1 ,"ASAD NADEEM");
    TM_HD44780_PutCustom(12, 1, 3);
    Delayms(1000);
    TM_HD44780_Clear();
    TM_HD44780_PutCustom(13, 0, 1);
    Delayms(1000);
    TM_HD44780_PutCustom(14, 1, 0);
    Delayms(1000);
    TM_HD44780_Clear();
    TM_HD44780_Puts(3,0 , "LOADING");
    Delayms(1000);
    TM_HD44780_Puts(10,0 , ".");
    Delayms(1000);
    TM_HD44780_Puts(11,0 , ".");
    Delayms(1000);
    TM_HD44780_Puts(12 , 0, ".");
    Delayms(1000);
    TM_HD44780_Puts(1,1 , "SUCCESSFUL !!!");
    Delayms(1000);
    TM_HD44780_Clear();
    
/******* INITIALIZATION OF DS 1307 ************/
   //Init_RTC(); // UNCOMMENT THIS FUNCTION WHEN YOU WANT TO SET DATE & TIME
   
   
  TM_DS1307_Time_t time;
 
  /******* READING THE TIME AND DATE CONTINUOUSLY ********/
    while(1){
TM_DS1307_GetDateTime(&time);
sprintf(time_T,"Time = %d:%d:%2d" ,  time.hours,time.minutes,time.seconds );

sprintf(date_D , "Date = %d/%d/%d" , time.date, time.month, time.year );
TM_HD44780_Puts(0,0 , time_T);
TM_HD44780_Puts(0 , 1 , date_D);
Delayms(200);

    }
}


