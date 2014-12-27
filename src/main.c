#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "lcd.h"
#include "rtc.h"
#include "inputs.h"
#include "outputs.h"
#include "list.h"
#include "stm32f4xx_rtc.h"
#include "Timers.h"
#include "ADC_Driver.h"
#include "Flash.h"
/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/

__IO uint32_t   uwLsiFreq = 0;
__IO uint32_t   uwCaptureNumber = 0;
__IO uint32_t   uwPeriodValue = 0;




 /* Private function prototypes -----------------------------------------------*/
 /* Private functions ---------------------------------------------------------*/



//Láncolt lista elemei

MenuElement_Typedef menu_MENU;
MenuElement_Typedef menu_outputs_on;
MenuElement_Typedef menu_outputs_on0;
MenuElement_Typedef menu_outputs_on1;
MenuElement_Typedef menu_outputs_on2;
MenuElement_Typedef menu_outputs_on3;
MenuElement_Typedef menu_outputs_on4;
MenuElement_Typedef menu_outputs_on5;
MenuElement_Typedef menu_outputs_on6;
MenuElement_Typedef menu_outputs_on7;
MenuElement_Typedef menu_outputs_on8;
MenuElement_Typedef menu_outputs_on9;
MenuElement_Typedef menu_outputs_on10;
MenuElement_Typedef menu_outputs_off;
MenuElement_Typedef menu_outputs_off0;
MenuElement_Typedef menu_outputs_off1;
MenuElement_Typedef menu_outputs_off2;
MenuElement_Typedef menu_outputs_off3;
MenuElement_Typedef menu_outputs_off4;
MenuElement_Typedef menu_outputs_off5;
MenuElement_Typedef menu_outputs_off6;
MenuElement_Typedef menu_outputs_off7;
MenuElement_Typedef menu_outputs_off8;
MenuElement_Typedef menu_outputs_off9;
MenuElement_Typedef menu_outputs_off10;
MenuElement_Typedef menu_time;
MenuElement_Typedef menu_time0;
MenuElement_Typedef menu_date;
MenuElement_Typedef menu_current_time;
MenuElement_Typedef menu_ontozes;
MenuElement_Typedef menu_ingyen_sor;
MenuElement_Typedef menu_utkozes;

MenuElement_Typedef * menu_first;
MenuElement_Typedef * menu_current;
MenuElement_Typedef menu_level_first[MENU_LEVEL_MAX];
MenuElement_Typedef menu_level_current[MENU_LEVEL_MAX];

MenuElement_Typedef * menu_temporary;
MenuElement_Typedef * menu_temporary2;
MenuElement_Typedef * menu_temporary3;

MenuElement_Typedef watering_settings_0;
MenuElement_Typedef watering_delete;
MenuElement_Typedef watering_new;
MenuElement_Typedef watering_edit;
MenuElement_Typedef watering_prcess1;		//Az öntözõ képernyõnéél van szerepe. Ez fog megjelenni az öntözõképenyõ elsõ soraként.
MenuElement_Typedef watering_prcess2;		//Az öntözõ képernyõnéél van szerepe. Ez fog megjelenni az öntözõképenyõ második soraként.

Watering_Typedef watering[WATERING_MAX_ELEMENT];
Watering_Typedef * watering_current;
Watering_Typedef * watering_temporary;
Watering_Typedef * watering_temporary2;


RTC_AlarmTypeDef RTC_AlarmStructure;
extern  RTC_InitTypeDef RTC_InitStructure;

char menu_level;
char menu_special_function;
char temp [17];
char watering_i;
char watering_j;
char datechanger_date[9];
char watering_lenght[3];
int day_counter;

int OutputOn(char param)
{
    Output_On(param);

    return 0;
}

int OutputOff(char param)
{
    Output_Off(param);

    return 0;
}
/*
 * TimeCompare
 *
 * A függvény eldönti, hogy megy-e öntözõ program.
 * Visszatérési értéke: +0, ha megy,
 * 						+1, ha nem.
 * */

char watering_temp[6][17];	//Az öntözési programok egyes paramétereit tárolom benne. Az öntözés kezdete: (8-12 bit, hossza: 14, 15.bit)

int TimeCompare(Watering_Typedef * watering_current)	//0-val tér vissza, ha éppen megy egy program, 1-el, ha nem.
{
    int temp1;
    int temp2;

    temp1 = ((watering_temp[(watering_current->designator - 1)][8] - ASCII_OFFSEET) * 36000 + (watering_temp[(watering_current->designator - 1)][9] - ASCII_OFFSEET) * 3600 + (watering_temp[(watering_current->designator - 1)][11] - ASCII_OFFSEET) * 600 + (watering_temp[(watering_current->designator - 1)][12] - ASCII_OFFSEET) * 60);
    temp2 = (((RTC->TR & TIME_HOUR_BCD_1) >> TIME_HOUR_BCD_1_OFFSET) * 36000 + ((RTC->TR & TIME_HOUR_BCD_2) >> TIME_HOUR_BCD_2_OFFSET) * 3600 + ((RTC->TR & TIME_MINUTE_BCD_1) >> TIME_MINUTE_BCD_1_OFFSET) * 600 + ((RTC->TR & TIME_MINUTE_BCD_2) >> TIME_MINUTE_BCD_2_OFFSET) * 60 + ((RTC->TR & TIME_SECOND_BCD_1) >> TIME_SECOND_BCD_1_OFFSET) * 10 + ((RTC->TR & TIME_SECOND_BCD_2) >> TIME_SECOND_BCD_2_OFFSET));

    if((temp1 <= temp2) && ((temp1 + ((watering_temp[(watering_current->designator - 1)][14] - ASCII_OFFSEET) * 600) + ((watering_temp[(watering_current->designator - 1)][15] - ASCII_OFFSEET) * 60)) >= temp2))
        temp1 = 0;
    else
    	temp1 = 1;
    return temp1;
}

int TimeCompare2(Watering_Typedef * watering_current, Watering_Typedef * watering_other)
{
    int tempc1;
    int tempc2;
    int tempo1;
    int tempo2;

    tempc1 = ((datechanger_date[0] - ASCII_OFFSEET) * 36000 + (datechanger_date[1] - ASCII_OFFSEET) * 3600 + (datechanger_date[3] - ASCII_OFFSEET) * 600 + (datechanger_date[4] - ASCII_OFFSEET) * 60);
    tempo1 = ((watering_temp[(watering_other->designator - 1)][8] - ASCII_OFFSEET) * 36000 + (watering_temp[(watering_other->designator - 1)][9] - ASCII_OFFSEET) * 3600 + (watering_temp[(watering_other->designator - 1)][11] - ASCII_OFFSEET) * 600 + (watering_temp[(watering_other->designator - 1)][12] - ASCII_OFFSEET) * 60);
    tempc2 = (tempc1 + ((watering_lenght[0] - ASCII_OFFSEET) * 600) + ((watering_lenght[1] - ASCII_OFFSEET) * 60));
    tempo2 = (tempo1 + ((watering_temp[(watering_other->designator - 1)][14] - ASCII_OFFSEET) * 600) + ((watering_temp[(watering_other->designator - 1)][15] - ASCII_OFFSEET) * 60));

    if((tempc1 <= tempo1 && tempo1 <= tempc2) || (tempc1 <= tempo2 && tempo2 <= tempc2) || (tempo1 <= tempc1 && tempc1 <= tempo2) || (tempo1 <= tempc2 && tempc2 <= tempo2))
    	return 0;
    else
    	return 1;
}

//***************************************MEGÍRÁS ALATT**********************************
// A másodperc kiírás / mentés rossz!!
// A time beállításánál nem korlátozza az órát!!
//Meg kell írni a nap beállításának lehetõségét is az öntözés végett!!
char datechanger_i;
char datechanger_function;
char datechanger_temp;

int alarm_temp;

void Watering_Next_Set()
{
	watering_j = 0;
	watering_temporary2 = &watering[1];
	alarm_temp = 0;

    for(watering_i = 0; watering_i < 6; watering_i++)	//végigmegyek a hat öntözési lehetõség között. Megkeresem azt, amelyik idõpontja nagyobb a pillanatnyi idõnél, de a lehetõ legkevesebbel.
    {
    	if((((watering_temp[(watering_temporary2->designator) - 1][6] - ASCII_OFFSEET) * 86400 + (watering_temp[(watering_temporary2->designator) - 1][8] - ASCII_OFFSEET) * 36000 + (watering_temp[(watering_temporary2->designator) - 1][9] - ASCII_OFFSEET) * 3600 + (watering_temp[(watering_temporary2->designator) - 1][11] - ASCII_OFFSEET) * 600 + (watering_temp[(watering_temporary2->designator) - 1][12] - ASCII_OFFSEET) * 60) > ((day_counter * 86400) + (((RTC->TR & TIME_HOUR_BCD_1) >> TIME_HOUR_BCD_1_OFFSET) * 36000) + (((RTC->TR & TIME_HOUR_BCD_2) >> TIME_HOUR_BCD_2_OFFSET) * 3600) + (((RTC->TR & TIME_MINUTE_BCD_1) >> TIME_MINUTE_BCD_1_OFFSET) * 600) + (((RTC->TR & TIME_MINUTE_BCD_2) >> TIME_MINUTE_BCD_2_OFFSET) * 60)) &&  ((watering_temp[(watering_temporary2->designator) - 1][8] != 'x'))))
    	{
    		watering_j = 1;

    		if(!alarm_temp || (alarm_temp > ((watering_temp[(watering_temporary2->designator) - 1][6] - ASCII_OFFSEET) * 86400 + (watering_temp[(watering_temporary2->designator) - 1][8] - ASCII_OFFSEET) * 36000 + (watering_temp[(watering_temporary2->designator) - 1][9] - ASCII_OFFSEET) * 3600 + (watering_temp[(watering_temporary2->designator) - 1][11] - ASCII_OFFSEET) * 600 + (watering_temp[(watering_temporary2->designator) - 1][12] - ASCII_OFFSEET) * 60)))
    		{
    			alarm_temp = ((watering_temp[(watering_temporary2->designator) - 1][6] - ASCII_OFFSEET) * 86400 + (watering_temp[(watering_temporary2->designator) - 1][6] - ASCII_OFFSEET) * 86400 + (watering_temp[(watering_temporary2->designator) - 1][8] - ASCII_OFFSEET) * 36000 + (watering_temp[(watering_temporary2->designator) - 1][9] - ASCII_OFFSEET) * 3600 + (watering_temp[(watering_temporary2->designator) - 1][11] - ASCII_OFFSEET) * 600 + (watering_temp[(watering_temporary2->designator) - 1][12] - ASCII_OFFSEET) * 60);
    			watering_current = watering_temporary2;
    		}
    	}
    	watering_temporary2 = watering_temporary2->next;
    }

	if(watering_j == 0)
	{
		watering_temporary2 = &watering[1];

		for(watering_i = 0; watering_i < 6; watering_i++)	//végigmegyek a hat öntözési lehetõség között. Megkeresem azt, amelyik idõpontja nagyobb a pillanatnyi idõnél, de a lehetõ legkevesebbel.
		{
			if((((watering_temp[(watering_temporary2->designator) - 1][6] - ASCII_OFFSEET) * 86400 + (watering_temp[(watering_temporary2->designator) - 1][8] - ASCII_OFFSEET) * 36000 + (watering_temp[(watering_temporary2->designator) - 1][9] - ASCII_OFFSEET) * 3600 + (watering_temp[(watering_temporary2->designator) - 1][11] - ASCII_OFFSEET) * 600 + (watering_temp[(watering_temporary2->designator) - 1][12] - ASCII_OFFSEET) * 60) < ((day_counter * 86400) + (((RTC->TR & TIME_HOUR_BCD_1) >> TIME_HOUR_BCD_1_OFFSET) * 36000) + (((RTC->TR & TIME_HOUR_BCD_2) >> TIME_HOUR_BCD_2_OFFSET) * 3600) + (((RTC->TR & TIME_MINUTE_BCD_1) >> TIME_MINUTE_BCD_1_OFFSET) * 600) + (((RTC->TR & TIME_MINUTE_BCD_2) >> TIME_MINUTE_BCD_2_OFFSET) * 60)) &&  ((watering_temp[(watering_temporary2->designator) - 1][8] != 'x'))))
			{
				if(!alarm_temp || (alarm_temp > ((watering_temp[(watering_temporary2->designator) - 1][6] - ASCII_OFFSEET) * 86400 + (watering_temp[(watering_temporary2->designator) - 1][8] - ASCII_OFFSEET) * 36000 + (watering_temp[(watering_temporary2->designator) - 1][9] - ASCII_OFFSEET) * 3600 + (watering_temp[(watering_temporary2->designator) - 1][11] - ASCII_OFFSEET) * 600 + (watering_temp[(watering_temporary2->designator) - 1][12] - ASCII_OFFSEET) * 60)))
				{
					alarm_temp = ((watering_temp[(watering_temporary2->designator) - 1][6] - ASCII_OFFSEET) * 86400 + (watering_temp[(watering_temporary2->designator) - 1][8] - ASCII_OFFSEET) * 36000 + (watering_temp[(watering_temporary2->designator) - 1][9] - ASCII_OFFSEET) * 3600 + (watering_temp[(watering_temporary2->designator) - 1][11] - ASCII_OFFSEET) * 600 + (watering_temp[(watering_temporary2->designator) - 1][12] - ASCII_OFFSEET) * 60);
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
}


int DateChanger(char param)
{
    if(param == menu_date.designator)
    {
        datechanger_i = 0;
        menu_special_function = MENU_SPECIAL_FUNCTION_TIME_DATE;
        datechanger_function = menu_date.designator;

        ClearLcmScreen();

        datechanger_date[0]=(((RTC->DR & DATE_JEAR_BCD_1) >> DATE_JEAR_BCD_1_OFFSET) + ASCII_OFFSEET);
        datechanger_date[1]=(((RTC->DR & DATE_JEAR_BCD_2) >> DATE_JEAR_BCD_2_OFFSET) + ASCII_OFFSEET);
        datechanger_date[2]=':';
        datechanger_date[3]=(((RTC->DR & DATE_MONTH_BCD_1) >> DATE_MONTH_BCD_1_OFFSET) + ASCII_OFFSEET);
        datechanger_date[4]=(((RTC->DR & DATE_MONTH_BCD_2) >> DATE_MONTH_BCD_2_OFFSET) + ASCII_OFFSEET);
        datechanger_date[5]=':';
        datechanger_date[6]=(((RTC->DR & DATE_DATE_BCD_1) >> DATE_DATE_BCD_1_OFFSET) + ASCII_OFFSEET);
        datechanger_date[7]=(((RTC->DR & DATE_DATE_BCD_2) >> DATE_DATE_BCD_2_OFFSET) + ASCII_OFFSEET);
        datechanger_date[8]='\0';

        Cursor(0, 0);
        PrintStr(menu_date.nev);

        Cursor(2, 0);
        PrintStr(datechanger_date);
        Cursor(2, 0);
    }
    else if(param == menu_current_time.designator)
    {
        datechanger_i = 0;
        menu_special_function = MENU_SPECIAL_FUNCTION_TIME_DATE;
        datechanger_function = menu_current_time.designator;

        ClearLcmScreen();

        datechanger_date[0]=(((RTC->TR & TIME_HOUR_BCD_1) >> TIME_HOUR_BCD_1_OFFSET) + ASCII_OFFSEET);
        datechanger_date[1]=(((RTC->TR & TIME_HOUR_BCD_2) >> TIME_HOUR_BCD_2_OFFSET) + ASCII_OFFSEET);
        datechanger_date[2]=':';
        datechanger_date[3]=(((RTC->TR & TIME_MINUTE_BCD_1) >> TIME_MINUTE_BCD_1_OFFSET) + ASCII_OFFSEET);
        datechanger_date[4]=(((RTC->TR & TIME_MINUTE_BCD_2) >> TIME_MINUTE_BCD_2_OFFSET) + ASCII_OFFSEET);
        datechanger_date[5]=':';
        datechanger_date[6]=(((RTC->TR & TIME_SECOND_BCD_1) >> TIME_SECOND_BCD_1_OFFSET) + ASCII_OFFSEET);
        datechanger_date[7]=(((RTC->TR & TIME_SECOND_BCD_2) >> TIME_SECOND_BCD_2_OFFSET) + ASCII_OFFSEET);
        datechanger_date[8]='\0';

        Cursor(0, 0);
        PrintStr(menu_current_time.nev);

        Cursor(2, 0);
        PrintStr(datechanger_date);
        Cursor(2, 0);
    }

    else if(param == MENU_ENTER)
    {
        datechanger_i++;
        if(datechanger_i == 2 || datechanger_i == 5)
            datechanger_i++;
        Cursor(2, datechanger_i);
    }

    else if(param == MENU_DOWN)
    {
        if(datechanger_function == menu_current_time.designator)
        {
            if(datechanger_i == 0)
                {
                    datechanger_date[datechanger_i] = ((datechanger_date[datechanger_i] >= '2') ? '0' : (datechanger_date[datechanger_i] + 1));
                    datechanger_date[datechanger_i + 1] = '0';
                }
            else if(datechanger_i == 1)
            {
                if(datechanger_date[0] == '2')
                    datechanger_date[datechanger_i] = ((datechanger_date[datechanger_i] >= '3') ? '0' : (datechanger_date[datechanger_i] + 1));
                else
                    datechanger_date[datechanger_i] = ((datechanger_date[datechanger_i] >= '9') ? '0' : (datechanger_date[datechanger_i] + 1));
            }
            else if(datechanger_i == 3 || datechanger_i == 6)
                datechanger_date[datechanger_i] = ((datechanger_date[datechanger_i] == '5') ? '0' : (datechanger_date[datechanger_i] + 1));
            else
                datechanger_date[datechanger_i] = ((datechanger_date[datechanger_i] == '9') ? '0' : (datechanger_date[datechanger_i] + 1));
        }

        else if(datechanger_function == menu_date.designator)
        {
            if(datechanger_i == 3)
                {
                    datechanger_date[datechanger_i] = ((datechanger_date[datechanger_i] >= '1') ? '0' : (datechanger_date[datechanger_i] + 1));
                    datechanger_date[datechanger_i + 1] = ((datechanger_date[datechanger_i] == '0') ? '1' : '0');
                }
            else if(datechanger_i == 4)
            {
                if(datechanger_date[3] == '0')
                    datechanger_date[datechanger_i] = ((datechanger_date[datechanger_i] >= '9') ? '1' : (datechanger_date[datechanger_i] + 1));
                else if(datechanger_date[3] == '1')
                    datechanger_date[datechanger_i] = ((datechanger_date[datechanger_i] >= '2') ? '0' : (datechanger_date[datechanger_i] + 1));
            }
            else if(datechanger_i == 6)
            {
                datechanger_temp = (((datechanger_date[0] - ASCII_OFFSEET) * 10) + ((datechanger_date[1] - ASCII_OFFSEET)));

                if(((datechanger_temp % 4) == 0) && ((datechanger_date[3] - ASCII_OFFSEET) == 0) && ((datechanger_date[4] - ASCII_OFFSEET) == 2))   //ha szökõév van és február hónap
                    datechanger_date[datechanger_i] = ((datechanger_date[datechanger_i] >= '2') ? '0' : (datechanger_date[datechanger_i] + 1));

                else
                    datechanger_date[datechanger_i] = ((datechanger_date[datechanger_i] >= '3') ? '0' : (datechanger_date[datechanger_i] + 1));
                datechanger_date[datechanger_i + 1] = (datechanger_date[datechanger_i] == '0') ? '1' : '0';
            }
            else if(datechanger_i == 7)
            {
                if( ((datechanger_date[3] - ASCII_OFFSEET) == 0) && ((datechanger_date[4] - ASCII_OFFSEET) == 2))       //ha február van
                {
                    if(((datechanger_temp % 4) == 0))                                           //ha ez egy szökõév
                        datechanger_date[datechanger_i] = ((datechanger_date[datechanger_i] >= '9') ? ((datechanger_date[datechanger_i - 1] == '0') ? '1' : '0') : (datechanger_date[datechanger_i] + 1));
                    else
                        datechanger_date[datechanger_i] = ((datechanger_date[datechanger_i] >= '8') ? ((datechanger_date[datechanger_i - 1] == '0') ? '1' : '0') : (datechanger_date[datechanger_i] + 1));
                }

                else if(((datechanger_date[3] == '0') && (datechanger_date[4] == '4')) || ((datechanger_date[3] == '0') && (datechanger_date[4] == '6')) || ((datechanger_date[3] == '0') && (datechanger_date[4] == '8')) || ((datechanger_date[3] == '1') && (datechanger_date[4] == '1')))   //Ha a hónap 31 napos               {
                {
                    if(datechanger_date[6] == '3')
                        datechanger_date[datechanger_i] = '0';
                    else
                        datechanger_date[datechanger_i] = ((datechanger_date[datechanger_i] >= '9') ? ((datechanger_date[datechanger_i - 1] == '0') ? '1' : '0') : (datechanger_date[datechanger_i] + 1));
                }

                else        //ha 31 napos a hónap
                {
                    if(datechanger_date[6] == '3')
                        datechanger_date[datechanger_i] = ((datechanger_date[datechanger_i] >= '1') ? '0' : (datechanger_date[datechanger_i] + 1));
                    else
                        datechanger_date[datechanger_i] = ((datechanger_date[datechanger_i] >= '9') ? ((datechanger_date[datechanger_i - 1] == '0') ? '1' : '0') : (datechanger_date[datechanger_i] + 1));
                }
            }
            else
                datechanger_date[datechanger_i] = ((datechanger_date[datechanger_i] == '9') ? '0' : (datechanger_date[datechanger_i] + 1));
        }
        Cursor(2, 0);
        PrintStr(datechanger_date);
        Cursor(2, datechanger_i);
    }

    else if(param == MENU_UP)
    {
        if(datechanger_i == 3 || datechanger_i == 6)
            datechanger_date[datechanger_i] = ((datechanger_date[datechanger_i] == '0') ? (5 + ASCII_OFFSEET) : (datechanger_date[datechanger_i] - 1));
        else
            datechanger_date[datechanger_i] = ((datechanger_date[datechanger_i] == '0') ? (9 + ASCII_OFFSEET) : (datechanger_date[datechanger_i] - 1));

        Cursor(2, 0);
        PrintStr(datechanger_date);
        Cursor(2, datechanger_i);
    }

    if(datechanger_i == 8)
    {
/*        RCC_RTCCLKCmd(DISABLE);
          RCC_LSEConfig(RCC_LSE_OFF);
          PWR_BackupAccessCmd(DISABLE);
          RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, DISABLE);

          RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

          PWR_BackupAccessCmd(ENABLE);

          RCC_BackupResetCmd(ENABLE);
          RCC_BackupResetCmd(DISABLE);

          RCC_LSEConfig(RCC_LSE_ON);
          while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
          {
          }
          RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

          RCC_RTCCLKCmd(ENABLE);

          RTC_WaitForSynchro();

          RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
          RTC_InitStructure.RTC_SynchPrediv  = 0xFF;
          RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
          RTC_Init(&RTC_InitStructure);

          RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits);
          RTC_SetWakeUpCounter(0x0);
          RTC_ITConfig(RTC_IT_WUT, ENABLE);*/

        DisplayFill(*menu_current, *menu_first);

        //**********************************************************************************

        RTC_WriteProtectionCmd(DISABLE);
        RTC_EnterInitMode();

        //**********************************************************************************

        if(datechanger_function == menu_date.designator)
        {
            RTC_DateTypeDef RTC_DateStructure;

            RTC_DateStructure.RTC_Year  = (((datechanger_date[0] - ASCII_OFFSEET) << 4)  | (datechanger_date[1] - ASCII_OFFSEET));
            RTC_DateStructure.RTC_Month = (((datechanger_date[3] - ASCII_OFFSEET) << 4)  | (datechanger_date[4] - ASCII_OFFSEET));
            RTC_DateStructure.RTC_Date  = (((datechanger_date[6] - ASCII_OFFSEET) << 4)  | (datechanger_date[7] - ASCII_OFFSEET));

            RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);
            RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
        }

        else if(datechanger_function == menu_current_time.designator)
        {
            RTC_TimeTypeDef  RTC_TimeStructure;

            RTC_TimeStructure.RTC_Hours   = (((datechanger_date[0] - ASCII_OFFSEET) << 4)  | (datechanger_date[1] - ASCII_OFFSEET));
            RTC_TimeStructure.RTC_Minutes = (((datechanger_date[3] - ASCII_OFFSEET) << 4)  | (datechanger_date[4] - ASCII_OFFSEET));
            RTC_TimeStructure.RTC_Seconds = (((datechanger_date[6] - ASCII_OFFSEET) << 4)  | (datechanger_date[7] - ASCII_OFFSEET));

            RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);
        }
        //**********************************************************************************

        RTC_ExitInitMode();
        RTC_WaitForSynchro();
        //Megnézni, hogy az új idõpont belül van-e a jelenlegi öntözéses cikluson. Ha belül van, hagyom, ha nem megkeressük a kövit, és azzá váltjuk a jelenlegit
//        if(!TimeCompare(watering_current))
 //       {
            OutputOff(Output_all);
/*            watering_i = 0;
            watering_temporary2 = &watering[0];
            watering_temporary2 = watering_temporary2->next;
            while(watering_temporary2->next)
            {
                if(((watering_temporary2->Watering_time[0] - ASCII_OFFSEET) * 100000 + (watering_temporary2->Watering_time[1] - ASCII_OFFSEET) * 10000 + (watering_temporary2->Watering_time[2] - ASCII_OFFSEET) * 1000 + (watering_temporary2->Watering_time[3] - ASCII_OFFSEET) * 100 + (watering_temporary2->Watering_time[4] - ASCII_OFFSEET) * 10 + (watering_temporary2->Watering_time[5] - ASCII_OFFSEET)) > ((((RTC->TR & TIME_HOUR_BCD_1) >> TIME_HOUR_BCD_1_OFFSET) * 100000) + (((RTC->TR & TIME_HOUR_BCD_2) >> TIME_HOUR_BCD_2_OFFSET) * 10000) + (((RTC->TR & TIME_MINUTE_BCD_1) >> TIME_MINUTE_BCD_1_OFFSET) * 1000) + (((RTC->TR & TIME_MINUTE_BCD_2) >> TIME_MINUTE_BCD_2_OFFSET) * 100) + (((RTC->TR & TIME_SECOND_BCD_1) >> TIME_SECOND_BCD_1_OFFSET) * 10) + (((RTC->TR & TIME_SECOND_BCD_2) >> TIME_SECOND_BCD_2_OFFSET))))
                {
                    watering_i = 1;
                    break;
                }
                else
                    watering_temporary2 = watering_temporary2->next;
            }
            if(watering_i || (((watering_temporary2->Watering_time[0] - ASCII_OFFSEET) * 100000 + (watering_temporary2->Watering_time[1] - ASCII_OFFSEET) * 10000 + (watering_temporary2->Watering_time[2] - ASCII_OFFSEET) * 1000 + (watering_temporary2->Watering_time[3] - ASCII_OFFSEET) * 100 + (watering_temporary2->Watering_time[4] - ASCII_OFFSEET) * 10 + (watering_temporary2->Watering_time[5] - ASCII_OFFSEET)) > ((((RTC->TR & TIME_HOUR_BCD_1) >> TIME_HOUR_BCD_1_OFFSET) * 100000) + (((RTC->TR & TIME_HOUR_BCD_2) >> TIME_HOUR_BCD_2_OFFSET) * 10000) + (((RTC->TR & TIME_MINUTE_BCD_1) >> TIME_MINUTE_BCD_1_OFFSET) * 1000) + (((RTC->TR & TIME_MINUTE_BCD_2) >> TIME_MINUTE_BCD_2_OFFSET) * 100) + (((RTC->TR & TIME_SECOND_BCD_1) >> TIME_SECOND_BCD_1_OFFSET) * 10) + (RTC->TR & TIME_SECOND_BCD_2) >> TIME_SECOND_BCD_2_OFFSET)))
                watering_current = watering_temporary2;
            else
            {
                watering_temporary2 = &watering[0];
                watering_current = watering_temporary2->next;
            }*/
            Watering_Next_Set();
    //    }

        //**********************************************************************************
        datechanger_function = 0;
        menu_special_function = 0;
    }
    return 0;
}

char watering_function;
void ReDesignator()
{
    while(menu_temporary->previous)
        menu_temporary = menu_temporary->previous;

    menu_current = menu_temporary;
    menu_first = menu_temporary;

/*    watering_i = 1;
    while(menu_temporary->next)
    {
        (menu_temporary->next)->designator = watering_i;
        watering_i++;
        menu_temporary = menu_temporary->next;
    }
*/
/*    if(watering_function == watering_delete.designator)
    {*/
        ClearLcmScreen();
        DisplayFill(*menu_current, *menu_first);

        datechanger_function = 0;
        menu_special_function = 0;
  /*  }*/

}


/*Watering:
 * Ezt a függvényt hívom meg minden öntözõ programmal kapcsolatos beavatkozásnál:
 * 		-törlés
 * 		-szerkesztés
 * */

char watering_channel[2];
char watering_temp[6][17];
char watproc1_text[6];	//Öntözési képernyõhöz tartozó tömb. Tartalmát jelenítem meg az öntözési képernyõn.
char watering_process2[6];

int Watering(char param)
{
    if(param == watering_delete.designator || param == watering_edit.designator)
    {
        menu_special_function = MENU_SPECIAL_FUNCTION_ONTOZES;
        watering_i = 0;

        menu_level--;
        menu_current = &menu_level_current[menu_level];
        menu_first = &menu_level_first[menu_level];
        watering_temporary = &watering[(menu_current->designator)];
    }

    if(param == watering_delete.designator)
    {
    	if(!TimeCompare(watering_temporary))
    	{
    		OutputOff(Output_all);
    	    watering_prcess1.nev[0] = '0';
    	    watering_prcess1.nev[1] = '0';
    	    watering_prcess1.nev[3] = '0';
    	    watering_prcess1.nev[4] = '0';
    	}

    	watering_temp[watering_temporary->designator - 1][8] = watering_temp[watering_temporary->designator - 1][9] = watering_temp[watering_temporary->designator - 1][11] = 'x';
    	watering_temp[watering_temporary->designator - 1][6] = '1';
    	watering_temp[watering_temporary->designator - 1][12] = watering_temp[watering_temporary->designator - 1][14] = watering_temp[watering_temporary->designator - 1][15] = 'x';

    	Watering_Next_Set();

        ClearLcmScreen();

        menu_level--;
        menu_current = &menu_level_current[menu_level];
        menu_first = &menu_level_first[menu_level];

        DisplayFill(*menu_current, *menu_first);
        menu_special_function = 0;
    }

    else if(param == watering_edit.designator)
    {
        ClearLcmScreen();

        watering_function = watering_edit.designator;

        datechanger_date[0] = (watering_temp[watering_temporary->designator - 1][8] <= '9' && watering_temp[watering_temporary->designator - 1][8] >= '0') ? watering_temp[watering_temporary->designator - 1][8] : '0';
        datechanger_date[1] = (watering_temp[watering_temporary->designator - 1][9] <= '9' && watering_temp[watering_temporary->designator - 1][9] >= '0') ? watering_temp[watering_temporary->designator - 1][9] : '0';
        datechanger_date[3] = (watering_temp[watering_temporary->designator - 1][11] <= '9' && watering_temp[watering_temporary->designator - 1][11] >= '0') ? watering_temp[watering_temporary->designator - 1][11] : '0';
        datechanger_date[4] = (watering_temp[watering_temporary->designator - 1][12] <= '9' && watering_temp[watering_temporary->designator - 1][12] >= '0') ? watering_temp[watering_temporary->designator - 1][12] : '0';
        datechanger_date[6] = datechanger_date[7] = '0';
        datechanger_date[2] = datechanger_date[5] = ':';
        datechanger_date[8]='\0';

        watering_lenght[0] = (watering_temp[watering_temporary->designator - 1][14] <= '9' && watering_temp[watering_temporary->designator - 1][14] >= '0') ? watering_temp[watering_temporary->designator - 1][14] : '0';
        watering_lenght[1] = (watering_temp[watering_temporary->designator - 1][15] <= '9' && watering_temp[watering_temporary->designator - 1][15] >= '0') ? watering_temp[watering_temporary->designator - 1][15] : '0';
        watering_lenght[2] = '\0';

        watering_channel[0] = (watering_temp[watering_temporary->designator - 1][6] <= '9' && watering_temp[watering_temporary->designator - 1][6] >= '1') ? watering_temp[watering_temporary->designator - 1][6] : '1';
        watering_channel[1] = '\0';

        Cursor(0, 0);
        PrintStr(watering_edit.nev);

        Cursor(1, 0);
        PrintStr(watering_channel);

        Cursor(2, 0);
        PrintStr(datechanger_date);

        Cursor(3, 0);
        PrintStr(watering_lenght);
        Cursor(1, 0);
    }


    else if(param == MENU_ENTER)
    {
        if(watering_i == 0)
        {
            watering_i++;
            Cursor(2, (watering_i) - 1);
        }

        else if(watering_i < 8)
        {
            watering_i++;

            if(watering_i == 3 || watering_i == 6)
                watering_i++;
            Cursor(2, (watering_i - 1));
        }

        else if(watering_i >= 8 )
        {
            watering_i++;
            Cursor(3, (watering_i - 9));
        }
    }

    else if(param == MENU_DOWN)
    {
        if(watering_i == 0)
        {
            watering_channel[0] = (watering_channel[0] >= '9') ? '1' : (watering_channel[0] + 1);
        }
        else if(watering_i == 1)
            {
                datechanger_date[0] = ((datechanger_date[0] >= '2') ? '0' : (datechanger_date[0] + 1));
                datechanger_date[1] = '0';
            }
        else if(watering_i == 2)
        {
            if(datechanger_date[0] == '2')
                datechanger_date[1] = ((datechanger_date[1] >= '3') ? '0' : (datechanger_date[1] + 1));
            else
                datechanger_date[1] = ((datechanger_date[1] >= '9') ? '0' : (datechanger_date[1] + 1));
        }
        else if(watering_i == 4 || watering_i == 7)
            datechanger_date[watering_i - 1] = ((datechanger_date[watering_i - 1] == '5') ? '0' : (datechanger_date[watering_i - 1] + 1));
        else if(watering_i == 5 || watering_i == 8)
            datechanger_date[watering_i - 1] = ((datechanger_date[watering_i - 1] == '9') ? '0' : (datechanger_date[watering_i - 1] + 1));
        else if(watering_i == 9 || watering_i == 10)
            watering_lenght[watering_i - 9] = ((watering_lenght[watering_i - 9] == '9') ? '0' : (watering_lenght[watering_i - 9] + 1));


        if(watering_i == 0)
        {
            Cursor(1, 0);
            PrintStr(watering_channel);
            Cursor(1, 0);
        }

        else if(watering_i < 9)
        {
            Cursor(2, 0);
            PrintStr(datechanger_date);
            Cursor(2, watering_i - 1);
        }
        else
        {
            Cursor(3, 0);
            PrintStr(watering_lenght);
            Cursor(3, watering_i - 9);
        }
    }

    if(watering_i == 11)
    {
        watering_temporary2 = &watering[1];
        alarm_temp = 0;
        watering_j = 0;

        for(watering_i = 0; watering_i < 6; watering_i++)
        {
        	if((watering_temporary != watering_temporary2) && (!TimeCompare2(watering_temporary, watering_temporary2)))
        	{
                ClearLcmScreen();

                Cursor(0,0);
                StrAlign(menu_utkozes.nev, temp, ALIGN_CENTER);
                PrintStr(temp);
                menu_level_first[menu_level] = *menu_first;
                menu_level_current[menu_level] = *menu_current;
                menu_first = menu_current = menu_current->down;
                menu_level++;
                menu_special_function = 0;

                return 0;
        	}
        	watering_temporary2 = watering_temporary2->next;
        }

    	watering_temp[(watering_temporary->designator) - 1][8] = datechanger_date[0];
    	watering_temp[(watering_temporary->designator) - 1][9] = datechanger_date[1];
    	watering_temp[(watering_temporary->designator) - 1][11] = datechanger_date[3];
    	watering_temp[(watering_temporary->designator) - 1][12] = datechanger_date[4];

        watering_temp[(watering_temporary->designator) - 1][6] = watering_channel[0];

        watering_temp[(watering_temporary->designator) - 1][14] = watering_lenght[0];
        watering_temp[(watering_temporary->designator) - 1][15] = watering_lenght[1];


        menu_temporary3 = watering_temporary;
        menu_temporary = menu_temporary3;
        menu_current = menu_temporary;

        ReDesignator();

        watering_temporary2 = &watering[1];
        alarm_temp = 0;
        watering_j = 0;

        for(watering_i = 0; watering_i < 6; watering_i++)
        {
        	if(!TimeCompare(watering_temporary2))		//Ha van egy aktív program. Ekkor ugyan a tömb része az új öntözés, mégsem fogjuk megnézni, hogy melyik a következõ program, hiszen ekkor már megy egy.
        	{
        		watering_i = 9;

        		break;
        	}
        	watering_temporary2 = watering_temporary2->next;
        }

      	if(watering_i != 9)											//Ha nincs aktív program
        {
      		Watering_Next_Set();
      		RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);


      	/*	watering_temporary2 = &watering[1];

            for(watering_i = 0; watering_i < 6; watering_i++)	//végigmegyek a hat öntözési lehetõség között. Megkeresem azt, amelyik idõpontja nagyobb a pillanatnyi idõnél, de a lehetõ legkevesebbel.
            {
            	if((((watering_temp[(watering_temporary2->designator) - 1][8] - ASCII_OFFSEET) * 100000 + (watering_temp[(watering_temporary2->designator) - 1][9] - ASCII_OFFSEET) * 10000 + (watering_temp[(watering_temporary2->designator) - 1][11] - ASCII_OFFSEET) * 1000 + (watering_temp[(watering_temporary2->designator) - 1][12] - ASCII_OFFSEET) * 100) > ((((RTC->TR & TIME_HOUR_BCD_1) >> TIME_HOUR_BCD_1_OFFSET) * 100000) + (((RTC->TR & TIME_HOUR_BCD_2) >> TIME_HOUR_BCD_2_OFFSET) * 10000) + (((RTC->TR & TIME_MINUTE_BCD_1) >> TIME_MINUTE_BCD_1_OFFSET) * 1000) + (((RTC->TR & TIME_MINUTE_BCD_2) >> TIME_MINUTE_BCD_2_OFFSET) * 100) + (((RTC->TR & TIME_SECOND_BCD_1) >> TIME_SECOND_BCD_1_OFFSET) * 10) + (((RTC->TR & TIME_SECOND_BCD_2) >> TIME_SECOND_BCD_2_OFFSET))) &&  ((watering_temp[(watering_temporary2->designator) - 1][8] != 'x'))))
            	{
            		watering_j = 1;

            		if(!alarm_temp || (alarm_temp > ((watering_temp[(watering_temporary2->designator) - 1][8] - ASCII_OFFSEET) * 100000 + (watering_temp[(watering_temporary2->designator) - 1][9] - ASCII_OFFSEET) * 10000 + (watering_temp[(watering_temporary2->designator) - 1][11] - ASCII_OFFSEET) * 1000 + (watering_temp[(watering_temporary2->designator) - 1][12] - ASCII_OFFSEET)*100)))
            		{
            			alarm_temp = ((watering_temp[(watering_temporary2->designator) - 1][8] - ASCII_OFFSEET) * 100000 + (watering_temp[(watering_temporary2->designator) - 1][9] - ASCII_OFFSEET) * 10000 + (watering_temp[(watering_temporary2->designator) - 1][11] - ASCII_OFFSEET) * 1000 + (watering_temp[(watering_temporary2->designator) - 1][12] - ASCII_OFFSEET)*100);
            			watering_current = watering_temporary2;
            		}
            	}

            	watering_temporary2 = watering_temporary2->next;
            }

        	if(watering_j == 0)
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

            RTC_ClearFlag(RTC_FLAG_ALRBF);*/

        }

        menu_special_function = 0;
    }
    return 0;
}




int main(void)
{
    //***********************************INICIALIZÁLÁS********************************
	watering_temp[0][0] = 'T';
	watering_temp[0][1] = 'e';
	watering_temp[0][2] = 'r';
	watering_temp[0][3] = '1';
	watering_temp[0][4] = 'S';
	watering_temp[0][5] = 'N';
	watering_temp[0][6] = 'x';
	watering_temp[0][7] = ' ';
	watering_temp[0][8] = 'x';
	watering_temp[0][9] = 'x';
	watering_temp[0][10] = ':';
	watering_temp[0][11] = 'x';
	watering_temp[0][12] = 'x';
	watering_temp[0][13] = ' ';
	watering_temp[0][14] = 'x';
	watering_temp[0][15] = 'x';
	watering_temp[0][16] = '\0';

	watering_temp[1][0] = 'T';
	watering_temp[1][1] = 'e';
	watering_temp[1][2] = 'r';
	watering_temp[1][3] = '2';
	watering_temp[1][4] = 'S';
	watering_temp[1][5] = 'N';
	watering_temp[1][6] = 'x';
	watering_temp[1][7] = ' ';
	watering_temp[1][8] = 'x';
	watering_temp[1][9] = 'x';
	watering_temp[1][10] = ':';
	watering_temp[1][11] = 'x';
	watering_temp[1][12] = 'x';
	watering_temp[1][13] = ' ';
	watering_temp[1][14] = 'x';
	watering_temp[1][15] = 'x';
	watering_temp[1][16] = '\0';

	watering_temp[2][0] = 'T';
	watering_temp[2][1] = 'e';
	watering_temp[2][2] = 'r';
	watering_temp[2][3] = 'C';
	watering_temp[2][4] = 's';
	watering_temp[2][5] = 'N';
	watering_temp[2][6] = 'x';
	watering_temp[2][7] = ' ';
	watering_temp[2][8] = 'x';
	watering_temp[2][9] = 'x';
	watering_temp[2][10] = ':';
	watering_temp[2][11] = 'x';
	watering_temp[2][12] = 'x';
	watering_temp[2][13] = ' ';
	watering_temp[2][14] = 'x';
	watering_temp[2][15] = 'x';
	watering_temp[2][16] = '\0';

	watering_temp[3][0] = 'K';
	watering_temp[3][1] = 'e';
	watering_temp[3][2] = 'r';
	watering_temp[3][3] = 't';
	watering_temp[3][4] = '1';
	watering_temp[3][5] = 'N';
	watering_temp[3][6] = 'x';
	watering_temp[3][7] = ' ';
	watering_temp[3][8] = 'x';
	watering_temp[3][9] = 'x';
	watering_temp[3][10] = ':';
	watering_temp[3][11] = 'x';
	watering_temp[3][12] = 'x';
	watering_temp[3][13] = ' ';
	watering_temp[3][14] = 'x';
	watering_temp[3][15] = 'x';
	watering_temp[3][16] = '\0';

	watering_temp[4][0] = 'K';
	watering_temp[4][1] = 'e';
	watering_temp[4][2] = 'r';
	watering_temp[4][3] = 't';
	watering_temp[4][4] = '2';
	watering_temp[4][5] = 'N';
	watering_temp[4][6] = 'x';
	watering_temp[4][7] = ' ';
	watering_temp[4][8] = 'x';
	watering_temp[4][9] = 'x';
	watering_temp[4][10] = ':';
	watering_temp[4][11] = 'x';
	watering_temp[4][12] = 'x';
	watering_temp[4][13] = ' ';
	watering_temp[4][14] = 'x';
	watering_temp[4][15] = 'x';
	watering_temp[4][16] = '\0';

	watering_temp[5][0] = 'C';
	watering_temp[5][1] = 's';
	watering_temp[5][2] = 'e';
	watering_temp[5][3] = 'r';
	watering_temp[5][4] = '1';
	watering_temp[5][5] = 'N';
	watering_temp[5][6] = 'x';
	watering_temp[5][7] = ' ';
	watering_temp[5][8] = 'x';
	watering_temp[5][9] = 'x';
	watering_temp[5][10] = ':';
	watering_temp[5][11] = 'x';
	watering_temp[5][12] = 'x';
	watering_temp[5][13] = ' ';
	watering_temp[5][14] = 'x';
	watering_temp[5][15] = 'x';
	watering_temp[5][16] = '\0';

	watproc1_text[0] = '0';
	watproc1_text[1] = '0';
	watproc1_text[2] = ':';
	watproc1_text[3] = '0';
	watproc1_text[4] = '0';
	watproc1_text[5] = '\0';

	watering_process2[0] = '0';
	watering_process2[1] = '0';
	watering_process2[2] = ':';
	watering_process2[3] = '0';
	watering_process2[4] = '0';
	watering_process2[5] = '\0';

    menu_MENU.designator=0;
    menu_MENU.nev="MENU";
    menu_MENU.next=0;
    menu_MENU.down=(&menu_outputs_on);
    menu_MENU.previous=0;
    menu_MENU.up=0;
    menu_MENU.fgvnev=0;

    menu_outputs_on.designator=0;
    menu_outputs_on.nev="Outputs On";
    menu_outputs_on.fgvnev=0; 						//talán ki sem kell tölteni, hiszen a down alapján fogom a függvény létezését eldönteni.
    menu_outputs_on.next=(&menu_outputs_off);
    menu_outputs_on.previous=0;
    menu_outputs_on.up=(&menu_MENU);
    menu_outputs_on.down=(&menu_outputs_on0);

    menu_outputs_off.designator=1;
    menu_outputs_off.nev="Outputs Off";
    menu_outputs_off.next=(&menu_time);
    menu_outputs_off.previous=(&menu_outputs_on);
    menu_outputs_off.up=0;
    menu_outputs_off.down=(&menu_outputs_off0);

    menu_time.designator=2;
    menu_time.nev="Time";
    menu_time.next=(&menu_ontozes);
    menu_time.previous=(&menu_outputs_off);
    menu_time.up=0;
    menu_time.down=&(menu_time0);

    menu_ontozes.designator=3;
    menu_ontozes.nev="Ontozes";
    menu_ontozes.next=(&menu_ingyen_sor);
    menu_ontozes.previous=(&menu_time);
    menu_ontozes.up=0;
    menu_ontozes.down=&watering[0];

    menu_ingyen_sor.designator=4;
    menu_ingyen_sor.nev="Ingyen Sor";
    menu_ingyen_sor.next=0;
    menu_ingyen_sor.previous=(&menu_ontozes);
    menu_ingyen_sor.up=0;
    menu_ingyen_sor.down=0;

    menu_time0.designator=0;
    menu_time0.nev="...";
    menu_time0.next=&(menu_date);
    menu_time0.previous=0;
    menu_time0.up=&(menu_time);
    menu_time0.down=0;

    menu_date.designator=1;
    menu_date.nev="Datum";
    menu_date.fgvnev=DateChanger;
    menu_date.next=&(menu_current_time);
    menu_date.previous=&(menu_time0);
    menu_date.up=0;
    menu_date.down=0;

    menu_current_time.designator=2;
    menu_current_time.nev="Ido";
    menu_current_time.fgvnev=DateChanger;
    menu_current_time.next=0;
    menu_current_time.previous=&(menu_date);
    menu_current_time.up=0;
    menu_current_time.down=0;

    menu_outputs_on0.designator=0;
    menu_outputs_on0.nev="...";
    menu_outputs_on0.next=(&menu_outputs_on1);
    menu_outputs_on0.previous=0;
    menu_outputs_on0.up=(&menu_outputs_on);
    menu_outputs_on0.down=0;

    menu_outputs_off0.designator=0;
    menu_outputs_off0.nev="...";
    menu_outputs_off0.next=(&menu_outputs_off1);
    menu_outputs_off0.previous=0;
    menu_outputs_off0.up=(&menu_outputs_off);
    menu_outputs_off0.down=0;

    menu_utkozes.designator=0;
    menu_utkozes.nev="Vigyazz Utkozes!";
    menu_utkozes.next=0;
    menu_utkozes.previous=0;
    menu_utkozes.up=&watering[0];
    menu_utkozes.down=0;

    watering[0].designator = 0;
    watering[0].nev="...";
    watering[0].next=(&watering[1]);
    watering[0].previous=0;
    watering[0].up=(&menu_ontozes);
    watering[0].down=0;

    watering[1].designator=1;
    watering[1].nev=&watering_temp[0];
    watering[1].next=(&watering[2]);
    watering[1].previous=(&watering[0]);
    watering[1].up=0;
    watering[1].down=&(watering_settings_0);
    watering[1].Watering_channel = 1;

    watering[2].designator=2;
    watering[2].nev=&watering_temp[1];
    watering[2].next=(&watering[3]);
    watering[2].previous=(&watering[1]);
    watering[2].up=0;
    watering[2].down=&(watering_settings_0);
    watering[2].Watering_channel = 2;

    watering[3].designator=3;
    watering[3].nev=&watering_temp[2];
    watering[3].next=(&watering[4]);
    watering[3].previous=(&watering[2]);
    watering[3].up=0;
    watering[3].down=&(watering_settings_0);
    watering[3].Watering_channel = 3;

    watering[4].designator=4;
    watering[4].nev=&watering_temp[3];
    watering[4].next=(&watering[5]);
    watering[4].previous=(&watering[3]);
    watering[4].up=0;
    watering[4].down=&(watering_settings_0);
    watering[4].Watering_channel = 4;

    watering[5].designator=5;
    watering[5].nev=&watering_temp[4];
    watering[5].next=(&watering[6]);
    watering[5].previous=(&watering[4]);
    watering[5].up=0;
    watering[5].down=&(watering_settings_0);
    watering[5].Watering_channel = 5;

    watering[6].designator=6;
    watering[6].nev=&watering_temp[5];
    watering[6].next=0;
    watering[6].previous=(&watering[5]);
    watering[6].up=0;
    watering[6].down=&(watering_settings_0);
    watering[6].Watering_channel = 6;

    watering_settings_0.designator=0;
    watering_settings_0.nev="...";
    watering_settings_0.next=&(watering_delete);
    watering_settings_0.previous=0;
    watering_settings_0.up=&watering[0];
    watering_settings_0.down=0;

    watering_delete.designator=1;
    watering_delete.nev="Torles";
    watering_delete.fgvnev=Watering;
    watering_delete.next=&(watering_edit);
    watering_delete.previous=&(watering_settings_0);
    watering_delete.up=0;
    watering_delete.down=0;

    watering_edit.designator=2;
    watering_edit.nev="Szerkesztes";
    watering_edit.fgvnev=Watering;
    watering_edit.next=0;
    watering_edit.previous=&(watering_delete);
    watering_edit.up=0;
    watering_edit.down=0;

    watering_prcess1.designator=0;
    watering_prcess1.nev=&watproc1_text;
    watering_prcess1.next=&(watering_prcess2);
    watering_prcess1.previous=0;
    watering_prcess1.up=&(menu_outputs_on);
    watering_prcess1.down=0;

    watering_prcess2.designator=1;
    watering_prcess2.nev=&watering_process2;
    watering_prcess2.next=0;
    watering_prcess2.previous=&(watering_prcess1);
    watering_prcess2.up=0;
    watering_prcess2.down=0;

    int a = 0, b = 0;
    day_counter = 1;
    menu_special_function = 0;
    menu_level = 0;

    while(a < 100)
    {
       __delay_cycles(100000);
       a++;
    }
    a=0;

    Inputs_Init();
    Outputs_Init();

    InitializeLcm();
    ClearLcmScreen();

    STM_EVAL_LEDInit(LED3);
    STM_EVAL_LEDInit(LED4);
    STM_EVAL_LEDInit(LED5);
    STM_EVAL_LEDInit(LED6);
    STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);

    //***********************************VÁRSKOZÁS A NYOMÓGOMBRA********************************

    while(STM_EVAL_PBGetState(BUTTON_USER) != SET)
    {
    }
    STM_EVAL_LEDOn(LED3);
    //***********************************KIINDULÁSI HELYZET FELVÉTELE********************************



    //*************************************flash prog






    //*************************************flash prog



    menu_first = &menu_outputs_on;
    menu_current = &menu_outputs_on;

    Cursor(0,0);
    StrAlign(menu_MENU.nev, temp, ALIGN_CENTER);
    PrintStr(temp);

    menu_temporary = menu_MENU.down;
    Cursor(1,0);
    StrAlign(menu_temporary->nev, temp, ALIGN_ARROW);
    PrintStr(temp);

    menu_temporary = menu_temporary->next;
    Cursor(2,0);
    PrintStr(menu_temporary->nev);

    menu_temporary = menu_temporary->next;
    Cursor(3,0);
    PrintStr(menu_temporary->nev);

    FlashReset();
    FlashSectorStampToDefault(SectorStampToDefaultMode_Only_First);
    ADC_Driver_Init();
    RTC_Config();
    RTC_WakeUpCmd(ENABLE);
    TimerConfig();

     b=0;
     while(b<100)
     {
         __delay_cycles(100000);
         b++;
     }

     //***********************************VÉGTELENÍTETT CIKLUS********************************
     while(1);
}





void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}



/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}




