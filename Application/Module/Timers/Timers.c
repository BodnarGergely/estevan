/*
 * Timers.c
 *
 *  Created on: 2014.07.16.
 *      Author: Gergo
 */


#include "ADC_Driver.h"
#include "Timers.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_rtc.h"
#include "FLASH.h"

extern uint16_t aADCDualConvertedValue[10];
volatile uint16_t ADCConvertedValues[ADC_PACKAGE_MAX_NUMBER][12];

void TimerConfig()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  	// APB1 -> 42 MHz, Timer -> 84 MHz

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 41999;
	TIM_TimeBaseStructure.TIM_Prescaler = 999;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM3, ENABLE);
}

void TIM3_IRQHandler(void)
{
	static int i = 0;
	static uint8_t interruptStatus = 0;
	int j = 0;


	RTC_TimeTypeDef RTC_TimeStruct;
	RTC_DateTypeDef RTC_DateStruct;


	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{

		STM_EVAL_LEDToggle(LED4);
		STM_EVAL_LEDToggle(LED5);
		STM_EVAL_LEDToggle(LED6);

		if(interruptStatus == 0)
		{
			ADC_SoftwareStartConv(ADC1);
			interruptStatus++;
		}
		else
		{
			RTC_GetTime(RTC_Format_BCD, &RTC_TimeStruct);
			RTC_GetDate(RTC_Format_BCD, &RTC_DateStruct);


			if(i < ADC_PACKAGE_MAX_NUMBER)
				i++;
			else
			{
				i = 0;
				//CopyToFlash((uint16_t*)ADCConvertedValues, (ADC_PACKAGE_MAX_NUMBER * SIZE_OF_PACK));
				CopyToFlashTest((uint16_t*)ADCConvertedValues, (ADC_PACKAGE_MAX_NUMBER * SIZE_OF_PACK));
			}

			for(j = 0; j < NUMBER_OF_CONVERSIONS; j++)
				ADCConvertedValues[i][j + 2] = aADCDualConvertedValue[j];

			ADCConvertedValues[i][0] = (((RTC_DateStruct.RTC_Year) << 8) | (RTC_DateStruct.RTC_Month));
			ADCConvertedValues[i][1] = (((RTC_DateStruct.RTC_Date & 0x1F) << 11) | ((RTC_TimeStruct.RTC_Hours & 0x1F) << 6) | (RTC_TimeStruct.RTC_Minutes & 0x3F));

			interruptStatus = 0;
		}

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
   }
}
