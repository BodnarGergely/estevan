#include "stm32f4xx_it.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "lcd.h"
#include "rtc.h"
#include "inputs.h"
#include "outputs.h"
#include "list.h"
#include "stm32f4xx_rtc.h"


/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */



extern __IO uint32_t uwPeriodValue;
extern __IO uint32_t uwCaptureNumber;
uint16_t tmpCC4[2] = {0, 0};

extern char temp[17];
/*extern char menu_first;
extern char menu_sub_first;
extern char menu_chosen;
extern char menu_sub_chosen;*/
extern char menu_level;
extern char menu_special_function;


extern MenuElement_Typedef menu_MENU;
extern MenuElement_Typedef menu_outputs_on;
extern MenuElement_Typedef menu_outputs_on0;
extern MenuElement_Typedef menu_outputs_on1;
extern MenuElement_Typedef menu_outputs_on2;
extern MenuElement_Typedef menu_outputs_on3;
extern MenuElement_Typedef menu_outputs_on4;
extern MenuElement_Typedef menu_outputs_on5;
extern MenuElement_Typedef menu_outputs_on6;
extern MenuElement_Typedef menu_outputs_on7;
extern MenuElement_Typedef menu_outputs_on8;
extern MenuElement_Typedef menu_outputs_on9;
extern MenuElement_Typedef menu_outputs_on10;
extern MenuElement_Typedef menu_outputs_off;
extern MenuElement_Typedef menu_outputs_off0;
extern MenuElement_Typedef menu_outputs_off1;
extern MenuElement_Typedef menu_outputs_off2;
extern MenuElement_Typedef menu_outputs_off3;
extern MenuElement_Typedef menu_outputs_off4;
extern MenuElement_Typedef menu_outputs_off5;
extern MenuElement_Typedef menu_outputs_off6;
extern MenuElement_Typedef menu_outputs_off7;
extern MenuElement_Typedef menu_outputs_off8;
extern MenuElement_Typedef menu_outputs_off9;
extern MenuElement_Typedef menu_outputs_off10;
extern MenuElement_Typedef menu_time;
extern MenuElement_Typedef menu_time0;
extern MenuElement_Typedef menu_ontozes;
extern MenuElement_Typedef menu_ingyen_sor;


extern MenuElement_Typedef * menu_first;
extern MenuElement_Typedef * menu_current;
extern MenuElement_Typedef * menu_temporary;
extern MenuElement_Typedef menu_level_first[MENU_LEVEL_MAX];
extern MenuElement_Typedef menu_level_current[MENU_LEVEL_MAX];


extern Watering_Typedef watering[WATERING_MAX_ELEMENT];
extern char watering_i;
extern char watering_temp[6][17];
extern Watering_Typedef * watering_temporary;
extern Watering_Typedef * watering_temporary2;


extern MenuElement_Typedef watering_settings_0;
extern MenuElement_Typedef watering_delete;
extern MenuElement_Typedef watering_new;
extern MenuElement_Typedef watering_settings;

extern MenuElement_Typedef watering_prcess1;
extern MenuElement_Typedef watering_prcess2;

extern RTC_AlarmTypeDef RTC_AlarmStructure;

extern Watering_Typedef * watering_current;
extern int alarm_temp;
extern int day_counter;




/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


int limit_swich_counter;
int pump_counter;


void RTC_WKUP_IRQHandler(void)
{
  if(RTC_GetITStatus(RTC_IT_WUT) != RESET)
  {
	  char RTC_WKUP_i = 0;
	  int RTC_WKUP_divider = 0;
	  int remaining_time;
	  int remaining_time2;
	  Watering_Typedef * RTC_WKUP_watering_temporary;

	 /* if((((RTC->TR & (RTC_TR_HT | RTC_TR_HU)) >> 16) == 0) && (((RTC->TR & (RTC_TR_MNT | RTC_TR_MNU)) >> 8) == 0) && ((RTC->TR & (RTC_TR_ST | RTC_TR_SU)) == 0))
	  {
		  day_counter++;
		  if(day_counter >= (WATERING_LKKT + 1))
			  day_counter = 1;
	  }*/

	  if(watering_prcess1.nev[0] != '0' || watering_prcess1.nev[1] != '0' || watering_prcess1.nev[3] != '0' || watering_prcess1.nev[4] != '0')
	  {
		  remaining_time = (watering_prcess1.nev[0] - ASCII_OFFSEET) * 600 + (watering_prcess1.nev[1] - ASCII_OFFSEET) * 60 + (watering_prcess1.nev[3] - ASCII_OFFSEET) * 10 + (watering_prcess1.nev[4] - ASCII_OFFSEET);
		  remaining_time--;

		  if(&(*menu_current) == &watering_prcess1)
		  {
		     for(RTC_WKUP_i = 4; RTC_WKUP_i < 255; RTC_WKUP_i--)
		     {
		    	 if(RTC_WKUP_i == 2)
		    		 RTC_WKUP_i--;

		    	 switch(RTC_WKUP_i)
		    	 {
		    	 	 case 0:
		    	 		RTC_WKUP_divider = 1;
		    	 		break;
		    	 	 case 1:
		    	 		RTC_WKUP_divider = 10;
		    	 		break;
		    	 	 case 3:
		    	 		RTC_WKUP_divider = 60;
		    	 		break;
		    	 	 case 4:
		    	 		RTC_WKUP_divider = 600;
		    	 		break;
		    	 }
		    	 watering_prcess1.nev[4 - RTC_WKUP_i] = (char)((remaining_time / RTC_WKUP_divider) + ASCII_OFFSEET);
		    	 remaining_time -= (watering_prcess1.nev[4 - RTC_WKUP_i] - ASCII_OFFSEET) * RTC_WKUP_divider;
		       }

		     remaining_time2 = limit_swich_counter;

		     for(RTC_WKUP_i = 4; RTC_WKUP_i < 255; RTC_WKUP_i--)
		     {
		    	 if(RTC_WKUP_i == 2)
		    		 RTC_WKUP_i--;

		    	 switch(RTC_WKUP_i)
		    	 {
		    	 	 case 0:
		    	 		RTC_WKUP_divider = 1;
		    	 		break;
		    	 	 case 1:
		    	 		RTC_WKUP_divider = 10;
		    	 		break;
		    	 	 case 3:
		    	 		RTC_WKUP_divider = 60;
		    	 		break;
		    	 	 case 4:
		    	 		RTC_WKUP_divider = 600;
		    	 		break;
		    	 }

		    	 watering_prcess2.nev[4 - RTC_WKUP_i] = (char)((remaining_time2 / RTC_WKUP_divider) + ASCII_OFFSEET);
		    	 remaining_time2 -= (watering_prcess2.nev[4 - RTC_WKUP_i] - ASCII_OFFSEET) * RTC_WKUP_divider;
		       }

		     Cursor(0,0);
		     StrAlign(watering_prcess1.nev, temp, ALIGN_LEFT);
		     PrintStr(temp);
		     Cursor(1,0);
		     StrAlign(watering_prcess2.nev, temp, ALIGN_LEFT);
		     PrintStr(temp);
		  }

		     if(!(GPIO_ReadInputDataBit(INPUT_PORT, INPUT_6_PIN)))										//Ha  a végálláskapcsoló riaszt, letiltom a kimeneteket(STOP állapot)
		     {
		    	 Output_Off(Output_all);
		    	 limit_swich_counter = LIMIT_SWITCH_COUNTER_WAIT;
		     }
		     else if((GPIO_ReadInputDataBit(INPUT_PORT, INPUT_6_PIN)) && limit_swich_counter)			//Ha már van víz, de még várni kell a telítõdésig(még tiltva van a szivattyú) (WAIT állapot)
		     {
		    	 Output_Off((Output_all));
		    	 limit_swich_counter--;
		     }
		     else if((GPIO_ReadInputDataBit(INPUT_PORT, INPUT_6_PIN)) && (limit_swich_counter == 0))	//Ha a végálláskapcsoló van víz, illetve ha már letelt a szivattyú tiltásának ideje
		     {
		    	 RTC_WKUP_watering_temporary = &watering[1];

		         for(RTC_WKUP_i = 0; RTC_WKUP_i < 6; RTC_WKUP_i++)
		         {
		         	if(!TimeCompare(RTC_WKUP_watering_temporary))		//Ha van egy aktív program. Ekkor ugyan a tömb része az új öntözés, mégsem fogjuk megnézni, hogy melyik a következõ program, hiszen ekkor már megy egy.
		         	{
		         		pump_counter++;

		         		if(pump_counter < PUMP_WAIT_1)
		         		{
		         			Output_On((watering_current->Watering_channel) + 2);
		         		}
		         		else if((pump_counter >= PUMP_WAIT_1) && (pump_counter < (PUMP_WAIT_1 + PUMP_WAIT_2)))
		         		{
		         			Output_Off(Output_all);
		         		}
		         		else
		         		{
		         			pump_counter = 0;
		         		}

		         		break;
		         	}

		         	RTC_WKUP_watering_temporary = RTC_WKUP_watering_temporary->next;
		         }
		     }
	  }

    RTC_ClearITPendingBit(RTC_IT_WUT);
    EXTI_ClearITPendingBit(EXTI_Line22);
  }
}

/*	RTC_Alarm_IRQHandler
 * Ez a függvény kezeli le az ALARM  megszakításokat, azaz õ az, aki az öntözés kezdetét, végét lekezeli.
*/
void RTC_Alarm_IRQHandler(void)
{
	int RTC_Alarm_IRQH_a, RTC_Alarm_IRQH_b;

  if((RTC_GetITStatus(RTC_IT_ALRA) != RESET)/* && (!(day_counter % watering_current->nev[6]))*/)	//Öntözés kezdetét kezelõ rész
  {
	  if((!(day_counter % (watering_current->nev[6] - ASCII_OFFSEET))))				//Megnézem, hogy aznap kell-e öntözni.
	  {

		  Output_Off((Output_all));													//Biztonság kedvéért minden szelepet kikapcsolok
		  Output_On((watering_current->Watering_channel) + 2);						//Megfelelõ szelep bekapcsolása
		  pump_counter = limit_swich_counter = 0;									//Nullázza a szivattyú kapcsolagatását(öntözéso programon belüli periódikus szünetek) vezérlõ változókat.

		  menu_level_first[menu_level] = *menu_first;								//Elmenti az elõzõ képernyõ állását.
		  menu_level_current[menu_level] = *menu_current;
		  menu_first = menu_current = &watering_prcess1;     						//Az almenü elsõ pontjára állítom az almenü aktuálisan kiválasztott változóját.
		  menu_level++;

		  watering_prcess1.nev[0] = watering_temp[(watering_current->designator) - 1][14];
		  watering_prcess1.nev[1] = watering_temp[(watering_current->designator) - 1][15];
		  watering_prcess1.nev[3] = '0';
		  watering_prcess1.nev[4] = '0';

		  ClearLcmScreen();				//Beállítom az öntözõ képernyõt.

		  Cursor(0,0);
		  StrAlign(watering_prcess1.nev, temp, ALIGN_LEFT);
		  PrintStr(temp);
	  }

	  RTC_ClearITPendingBit(RTC_IT_ALRA);
	  EXTI_ClearITPendingBit(EXTI_Line17);
  }

  else if((RTC_GetITStatus(RTC_IT_ALRB) != RESET)/* && (!(day_counter % watering_current->nev[6]))*/)	//Öntözés program lejártakor lefutó kód
  {
	  RTC_Alarm_IRQH_a = ((((RTC->ALRMAR & RTC_ALRMAR_HT) >> 20) * 600) + (((RTC->ALRMAR & RTC_ALRMAR_HU) >> 16) * 60) + (((RTC->ALRMAR & RTC_ALRMAR_MNT) >> 12) * 10) + (((RTC->ALRMAR & RTC_ALRMAR_MNU) >> 8)));
	  RTC_Alarm_IRQH_b = ((((RTC->ALRMBR & RTC_ALRMBR_HT) >> 20) * 600) + (((RTC->ALRMBR & RTC_ALRMBR_HU) >> 16) * 60) + (((RTC->ALRMBR & RTC_ALRMBR_MNT) >> 12) * 10) + (((RTC->ALRMBR & RTC_ALRMBR_MNU) >> 8)));

	  if((!(day_counter % (watering_current->nev[6] - ASCII_OFFSEET))) || ((RTC_Alarm_IRQH_a > RTC_Alarm_IRQH_b) && (!(((day_counter == 9) ? 1 : (day_counter - 1)) % (watering_current->nev[6] - ASCII_OFFSEET)))))
	  {
		  Output_Off((Output_all));

		  watering_prcess1.nev[0] = '0';
		  watering_prcess1.nev[1] = '0';
		  watering_prcess1.nev[3] = '0';
		  watering_prcess1.nev[4] = '0';

		  if(&(*menu_current) == &watering_prcess1)	//ha még mindig a Öntözés képernyõn van, a program lejártával visszamegy egy szintet.
		  {
			  ClearLcmScreen();

			  menu_level--;
			  menu_current = &menu_level_current[menu_level];
			  menu_first = &menu_level_first[menu_level];

			  DisplayFill(*menu_current, *menu_first);
		  }

		  Watering_Next_Set();
		  RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
/*
	watering_temporary2 = &watering[1];
    alarm_temp = 0;

    for(watering_i = 0; watering_i < 6; watering_i++)	//végigmegyek a hat öntözési lehetõség között. Megkeresem azt, amelyik idõpontja nagyobb a pillanatnyi idõnél, de a lehetõ legkevesebbel.
    {
    	if((((watering_temp[(watering_temporary2->designator) - 1][8] - ASCII_OFFSEET) * 100000 + (watering_temp[(watering_temporary2->designator) - 1][9] - ASCII_OFFSEET) * 10000 + (watering_temp[(watering_temporary2->designator) - 1][11] - ASCII_OFFSEET) * 1000 + (watering_temp[(watering_temporary2->designator) - 1][12] - ASCII_OFFSEET) * 100) > ((((RTC->TR & TIME_HOUR_BCD_1) >> TIME_HOUR_BCD_1_OFFSET) * 100000) + (((RTC->TR & TIME_HOUR_BCD_2) >> TIME_HOUR_BCD_2_OFFSET) * 10000) + (((RTC->TR & TIME_MINUTE_BCD_1) >> TIME_MINUTE_BCD_1_OFFSET) * 1000) + (((RTC->TR & TIME_MINUTE_BCD_2) >> TIME_MINUTE_BCD_2_OFFSET) * 100) + (((RTC->TR & TIME_SECOND_BCD_1) >> TIME_SECOND_BCD_1_OFFSET) * 10) + (((RTC->TR & TIME_SECOND_BCD_2) >> TIME_SECOND_BCD_2_OFFSET))) &&  ((watering_temp[(watering_temporary2->designator) - 1][8] != 'x'))))
    	{
    		watering_i = 9;

    		if(!alarm_temp || (alarm_temp > ((watering_temp[(watering_temporary2->designator) - 1][8] - ASCII_OFFSEET) * 100000 + (watering_temp[(watering_temporary2->designator) - 1][9] - ASCII_OFFSEET) * 10000 + (watering_temp[(watering_temporary2->designator) - 1][11] - ASCII_OFFSEET) * 1000 + (watering_temp[(watering_temporary2->designator) - 1][12] - ASCII_OFFSEET)*100)))
    		{
    			alarm_temp = ((watering_temp[(watering_temporary2->designator) - 1][8] - ASCII_OFFSEET) * 100000 + (watering_temp[(watering_temporary2->designator) - 1][9] - ASCII_OFFSEET) * 10000 + (watering_temp[(watering_temporary2->designator) - 1][11] - ASCII_OFFSEET) * 1000 + (watering_temp[(watering_temporary2->designator) - 1][12] - ASCII_OFFSEET)*100);
    			watering_current = watering_temporary2;
    		}
    	}

    	watering_temporary2 = watering_temporary2->next;
    }

	if(watering_i == 9)
	{



		watering_temporary2 = &watering[1];

		for(watering_i = 0; watering_i < 6; watering_i++)	//végigmegyek a hat öntözési lehetõség között. Megkeresem azt, amelyik idõpontja nagyobb a pillanatnyi idõnél, de a lehetõ legkevesebbel.
		{
			if((((watering_temp[(watering_temporary2->designator) - 1][8] - ASCII_OFFSEET) * 1000 + (watering_temp[(watering_temporary2->designator) - 1][9] - ASCII_OFFSEET) * 100 + (watering_temp[(watering_temporary2->designator) - 1][11] - ASCII_OFFSEET) * 10 + (watering_temp[(watering_temporary2->designator) - 1][12] - ASCII_OFFSEET)) < ((((RTC->TR & TIME_HOUR_BCD_1) >> TIME_HOUR_BCD_1_OFFSET) * 100000) + (((RTC->TR & TIME_HOUR_BCD_2) >> TIME_HOUR_BCD_2_OFFSET) * 10000) + (((RTC->TR & TIME_MINUTE_BCD_1) >> TIME_MINUTE_BCD_1_OFFSET) * 1000) + (((RTC->TR & TIME_MINUTE_BCD_2) >> TIME_MINUTE_BCD_2_OFFSET) * 100) + (((RTC->TR & TIME_SECOND_BCD_1) >> TIME_SECOND_BCD_1_OFFSET) * 10) + (((RTC->TR & TIME_SECOND_BCD_2) >> TIME_SECOND_BCD_2_OFFSET))) &&  ((watering_temp[(watering_temporary2->designator) - 1][8] != 'x'))))
			{
				if(!alarm_temp || (alarm_temp > ((watering_temp[(watering_temporary2->designator) - 1][8] - ASCII_OFFSEET) * 1000 + (watering_temp[(watering_temporary2->designator) - 1][9] - ASCII_OFFSEET) * 100 + (watering_temp[(watering_temporary2->designator) - 1][11] - ASCII_OFFSEET) * 10 + (watering_temp[(watering_temporary2->designator) - 1][12] - ASCII_OFFSEET))))
				{
					alarm_temp = ((watering_temp[(watering_temporary2->designator) - 1][8] - ASCII_OFFSEET) * 1000 + (watering_temp[(watering_temporary2->designator) - 1][9] - ASCII_OFFSEET) * 100 + (watering_temp[(watering_temporary2->designator) - 1][11] - ASCII_OFFSEET) * 10 + (watering_temp[(watering_temporary2->designator) - 1][12] - ASCII_OFFSEET));
					watering_current = watering_temporary2;
				}
			}

			watering_temporary2 = watering_temporary2->next;
		}
	}

    RTC_AlarmCmd(RTC_Alarm_A, DISABLE);
    RTC_AlarmCmd(RTC_Alarm_B, DISABLE);

    RTC_AlarmStructure.RTC_AlarmTime.RTC_H12     = RTC_H12_AM;
    RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = ((watering_temp[(watering_current->designator) - 1][8] - ASCII_OFFSEET) << 4 | (watering_temp[(watering_current->designator) - 1][9] - ASCII_OFFSEET));
    RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = ((watering_temp[(watering_current->designator) - 1][11] - ASCII_OFFSEET) << 4 | (watering_temp[(watering_current->designator) - 1][12] - ASCII_OFFSEET));
    RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = (0 << 4 | 0);
    RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
    RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;

    RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);

    alarm_temp = RTC->ALRMAR;

    RTC_ITConfig(RTC_IT_ALRA, ENABLE);

    RTC_AlarmCmd(RTC_Alarm_A, ENABLE);

    RTC_ClearFlag(RTC_FLAG_ALRAF);

    alarm_temp = ((watering_temp[(watering_current->designator) - 1][8] - ASCII_OFFSEET) * 36000 + (watering_temp[(watering_current->designator - 1)][9] - ASCII_OFFSEET) * 3600 + (watering_temp[(watering_current->designator) - 1][11] - ASCII_OFFSEET) * 600 + (watering_temp[(watering_current->designator) - 1][12] - ASCII_OFFSEET) * 60);
    alarm_temp += (((watering_temp[(watering_current->designator) - 1][14] - ASCII_OFFSEET) * 600) + ((watering_temp[(watering_current->designator - 1)][15] - ASCII_OFFSEET) * 60));

    RTC_AlarmStructure.RTC_AlarmTime.RTC_H12     = RTC_H12_AM;
    RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = (((alarm_temp / 36000) << 4) | ((alarm_temp / 3600) - ((alarm_temp / 36000) * 10)));

    alarm_temp -= ((((RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours & 0xF0) >> 4) * 36000) + ((RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours & 0xF) * 3600));

    RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = (((alarm_temp / 600) << 4) | ((alarm_temp / 60) - ((alarm_temp / 600) * 10)));

    alarm_temp -= ((((RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes & 0xF0) >> 4) * 600) + ((RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes & 0xF) * 60));

    RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = ((alarm_temp / 10) << 4 | (alarm_temp - ((alarm_temp / 10) * 10)));
    RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
    RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;

    RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_B, &RTC_AlarmStructure);

    RTC_ITConfig(RTC_IT_ALRB, ENABLE);

    RTC_AlarmCmd(RTC_Alarm_B, ENABLE);

    RTC_ClearFlag(RTC_FLAG_ALRBF);
    RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);

*/
	  }

    RTC_ClearITPendingBit(RTC_IT_ALRB);
    EXTI_ClearITPendingBit(EXTI_Line17);
  }
}

/*********************************A menuben a fel és le navigáló gombok IT függvényei************************/
/*
 *  A fel és a lefele navigáló gombok megszakításkezelõi is ebbe az EXTI osztályba tartoznak
 */

char menu_current_position = 0;
void EXTI9_5_IRQHandler(void)
{
//**************************************Input 1 interrupt kezelõ függvénye******************************************

if ( EXTI_GetITStatus(EXTI_Line6))              //Ez a megszakítás a menü kezelõ gombjához tartozik, amelyik a lefele léptetést csinálja
{
        if(menu_special_function)
        {
            switch(menu_special_function)
            {
            case MENU_SPECIAL_FUNCTION_TIME_DATE:
                DateChanger(MENU_DOWN);
                break;
            case MENU_SPECIAL_FUNCTION_ONTOZES:
                Watering(MENU_DOWN);
                break;

            default:
                break;
            }
        }

        else if(menu_current->next)
        {
            menu_current = menu_current->next;

            if(menu_current->designator >= ((menu_first->designator) + 3))
            {
                menu_temporary = menu_first->next;
                Cursor(1,0);
                StrAlign(menu_temporary->nev, temp, ALIGN_LEFT);
                PrintStr(temp);

                menu_temporary = menu_temporary->next;
                Cursor(2,0);
                StrAlign(menu_temporary->nev, temp, ALIGN_LEFT);
                PrintStr(temp);

                Cursor(3,0);
                StrAlign(menu_current->nev, temp, ALIGN_ARROW);
                PrintStr(temp);

                menu_first = menu_first->next;
            }
            else
            {
                Cursor((menu_current->designator - menu_first->designator), 0);
                menu_temporary = menu_current->previous;
                StrAlign(menu_temporary->nev, temp, ALIGN_LEFT);
                PrintStr(temp);

                Cursor(((menu_current->designator - menu_first->designator) + 1), 0);
                StrAlign(menu_current->nev, temp, ALIGN_ARROW);
                PrintStr(temp);
            }
        }
    EXTI_ClearITPendingBit(EXTI_Line6);
}

//**************************************Input 2 interrupt kezelõ függvénye******************************************
if ( EXTI_GetITStatus(EXTI_Line7))                      //Ez a megszakítás a menü kezelõ gombjához tartozik, amelyik a felfele léptetést csinálja
{
    if(menu_special_function)
    {
        switch(menu_special_function)
        {
        case MENU_SPECIAL_FUNCTION_TIME_DATE:
            DateChanger(MENU_UP);
            break;
        case MENU_SPECIAL_FUNCTION_ONTOZES:
            Watering(MENU_UP);
            break;

        default:
            break;
        }
    }

    else if(menu_current->designator > 0)
        {
            menu_current = menu_current->previous;
            if(menu_current->designator < menu_first->designator)
            {
                Cursor(1,0);
                StrAlign(menu_current->nev, temp, ALIGN_ARROW);
                PrintStr(temp);

                menu_temporary = menu_current->next;
                Cursor(2,0);
                StrAlign(menu_temporary->nev, temp, ALIGN_LEFT);
                PrintStr(temp);

                menu_temporary = menu_temporary->next;
                Cursor(3,0);
                StrAlign(menu_temporary->nev, temp, ALIGN_LEFT);
                PrintStr(temp);
                menu_first = menu_current;
            }
            else
            {
                Cursor(((menu_current->designator - menu_first->designator) + 1), 0);
                StrAlign(menu_current->nev, temp, ALIGN_ARROW);
                PrintStr(temp);

                menu_temporary = menu_current->next;
                Cursor(((menu_current->designator - menu_first->designator) + 2), 0);
                StrAlign(menu_temporary->nev, temp, ALIGN_LEFT);
                PrintStr(temp);
            }
        }
        EXTI_ClearITPendingBit(EXTI_Line7);
}
}

/*********************************Ha megnyomta a menupont kiválasztó gombot ez fut le.************************/
/*
 * Három esetet kell szétválasztani:
 *                                  1. Ha az aktuális menüpontnak van .down része, azaz van alpontja, akkor az alpont szerinti képernyõt kell behozni.
 *                                  2. Ha nincs alpontja, akkor viszont függvény kapcsolódik hozzá. Ekkor a függvényt kell lefuttatni.
 *                                  3. Ha egy almenüpontban vagyunk, és éppen a 0-s designatoru (...) elemre kattintunk rá, visszalépni a fõmenübe.
 * */


//******************************************RENOVÁLÁS ALATT!!**************************************************

void EXTI3_IRQHandler(void)
{
    if ( EXTI_GetITStatus(EXTI_Line3))
    {
        //*******************************RENOVÁLÁS ALATT******************
        if(menu_special_function)
        {
            switch(menu_special_function)
            {
            case MENU_SPECIAL_FUNCTION_TIME_DATE:
                DateChanger(MENU_ENTER);
                break;
            case MENU_SPECIAL_FUNCTION_ONTOZES:
                Watering(MENU_ENTER);
                break;

            default:
                break;
            }
        }

        //*******************************RENOVÁLÁS ALATT******************

        else if(menu_current->down && (menu_level < MENU_LEVEL_MAX))                    //1. eset: Van az adott menüpontnak alpontja
        {
            ClearLcmScreen();

            Cursor(0,0);
            StrAlign(menu_current->nev, temp, ALIGN_CENTER);
            PrintStr(temp);

            menu_temporary = menu_current->down;
            Cursor(1,0);
            StrAlign(menu_temporary->nev, temp, ALIGN_ARROW);
            PrintStr(temp);

            if(menu_temporary->next)
            {
                menu_temporary = menu_temporary->next;
                Cursor(2,0);
                PrintStr(menu_temporary->nev);

                if(menu_temporary->next)
                {
                    menu_temporary = menu_temporary->next;
                    Cursor(3,0);
                    PrintStr(menu_temporary->nev);
                }
            }

            menu_level_first[menu_level] = *menu_first;
            menu_level_current[menu_level] = *menu_current;
            menu_first = menu_current = menu_current->down;     //Az almenü elsõ pontjára állítom az almenü aktuálisan kiválasztott változóját.
            menu_level++;                                           //Egy jelzõ karakter, ami azt mutatja, hogy éppen egy almenüben vagyunk
        }

        //********************************************************RENOVÁLÁS ALATT******************

        else if((menu_level != 0) && (menu_current->designator == 0))   //3. eset:  Ha vissza akarok lépni egy alpontból
        {
            /* Úgy látom, hogy kell egy új változót, egy chart bevezetni, ami arra szolgál, hogy elmentem az almenüpontba lépéskor, hogy az
            almenüpont hányadik sorban van a kijelzõn. Ezzel azt csinálom, hogy ahmikor vissza akarok lépni a fõmenübe, ugyan az lesz a fõmenû
            képernyõjének az állása, mint az almenübe lépéskor.*/
            ClearLcmScreen();

            menu_level--;
            menu_current = &menu_level_current[menu_level];
            menu_first = &menu_level_first[menu_level];

            DisplayFill(*menu_current, *menu_first);
        }
        //***************************************************************************RENOVÁLÁS ALATT******************
        else if(menu_current->fgvnev != 0)                          //2. eset: Ha a menüpont kiválasztásával egy függvényt akarunk lefuttatni.
        {
            menu_current->fgvnev(menu_current->designator);
        }
    }

    EXTI_ClearITPendingBit(EXTI_Line3);
}
//******************************************RENOVÁLÁS ALATT!!**************************************************


//                  Input 4 interrupt kezelõ függvénye

void EXTI2_IRQHandler(void)
{
    if ( EXTI_GetITStatus(EXTI_Line2))
    {

    }

    EXTI_ClearITPendingBit(EXTI_Line2);
}

//                  Input 5 interrupt kezelõ függvénye

void EXTI1_IRQHandler(void)
{
    if ( EXTI_GetITStatus(EXTI_Line1))
    {

    }

    EXTI_ClearITPendingBit(EXTI_Line1);
}

//                  Input 6 interrupt kezelõ függvénye

void EXTI0_IRQHandler(void)
{
    if ( EXTI_GetITStatus(EXTI_Line0))
    {

    }

    EXTI_ClearITPendingBit(EXTI_Line0);
}




