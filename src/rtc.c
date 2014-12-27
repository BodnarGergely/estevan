/*
 * rtc.c
 *
 *  Created on: 2013.07.01.
 *      Author: Gergo
 */


#include "rtc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_rtc.h"
#include "stm32f4_discovery.h"

    RTC_InitTypeDef RTC_InitStructure;
void RTC_Config(void)
{
//  RTC_AlarmTypeDef RTC_AlarmStructure;
    RTC_TimeTypeDef  RTC_TimeStructure;
    RTC_DateTypeDef RTC_DateStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    RTC_InitTypeDef RTC_InitStructure;


  /* Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to RTC */
  PWR_BackupAccessCmd(ENABLE);

  RCC_BackupResetCmd(ENABLE);
  RCC_BackupResetCmd(DISABLE);

  RCC_LSEConfig(RCC_LSE_ON);
  while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {
  }
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  //**********************************************Gergõ**************************************
/*
  RCC_LSICmd(ENABLE);
  while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
  {
  }
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
*/
  //**********************************************Gergõ**************************************

  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();

  /* Calendar Configuration with LSI supposed at 32KHz */
  RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
  RTC_InitStructure.RTC_SynchPrediv  = 0xFF; /* (32KHz / 128) - 1 = 0xFF*/
  RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
  RTC_Init(&RTC_InitStructure);

  EXTI_ClearITPendingBit(EXTI_Line17);
  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  // Enable the RTC Alarm Interrupt
  NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  // EXTI configuration
  EXTI_ClearITPendingBit(EXTI_Line22);
  EXTI_InitStructure.EXTI_Line = EXTI_Line22;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  // Enable the RTC Wakeup Interrupt
  NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  // Configure the RTC WakeUp Clock source: CK_SPRE (1Hz)

  RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits);
  RTC_SetWakeUpCounter(0x0);
  RTC_ITConfig(RTC_IT_WUT, ENABLE);

  //**********************************************Gergõ**************************************
/*  RTC_AlarmStructure.RTC_AlarmTime.RTC_H12     = RTC_H12_AM;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = 0x05;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = 0x20;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = 0x30;
  RTC_AlarmStructure.RTC_AlarmDateWeekDay = 0x31;
  RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
  RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;*/

  /* Configure the RTC Alarm A register */
 /* RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);*/

  /* Enable RTC Alarm A Interrupt */
/*  RTC_ITConfig(RTC_IT_ALRA, ENABLE);*/

  /* Enable the alarm */
/*  RTC_AlarmCmd(RTC_Alarm_A, ENABLE);*/

/*  RTC_ClearFlag(RTC_FLAG_ALRAF);*/

  RTC_DateStructure.RTC_Year = 0x14;
  RTC_DateStructure.RTC_Month = RTC_Month_August;
  RTC_DateStructure.RTC_Date = 0x8;
  RTC_DateStructure.RTC_WeekDay = RTC_Weekday_Friday;
  RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);

  RTC_TimeStructure.RTC_H12     = RTC_H12_PM;
  RTC_TimeStructure.RTC_Hours   = 0x00;
  RTC_TimeStructure.RTC_Minutes = 0x14;
  RTC_TimeStructure.RTC_Seconds = 0x00;
  RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);

  RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);

  //**********************************************Gergõ**************************************


  /* Enable Wakeup Counter */
//  RTC_WakeUpCmd(ENABLE);
}
