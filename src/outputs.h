/*
 * outputs.h
 *
 *  Created on: 2013.07.01.
 *      Author: Gergo
 */

#ifndef OUTPUTS_H_
#define OUTPUTS_H_

#include "stm32f4xx.h"


#define LIMIT_SWITCH_COUNTER_WAIT 	(10)
#define PUMP_WAIT_1					(20)
#define PUMP_WAIT_2					(20)
#define WATERING_LKKT				2520


#define OUTPUT_1_PORT       GPIOC
#define OUTPUT_2_PORT       GPIOC
#define OUTPUT_3_PORT       GPIOC
#define OUTPUT_4_PORT       GPIOD
#define OUTPUT_5_PORT       GPIOD
#define OUTPUT_6_PORT       GPIOD
#define OUTPUT_7_PORT       GPIOD
#define OUTPUT_8_PORT       GPIOC
#define OUTPUT_9_PORT       GPIOC
#define OUTPUT_10_PORT      GPIOC

#define OUTPUT_1_PIN        GPIO_Pin_14
#define OUTPUT_2_PIN        GPIO_Pin_15
#define OUTPUT_3_PIN        GPIO_Pin_13
#define OUTPUT_4_PIN        GPIO_Pin_8
#define OUTPUT_5_PIN        GPIO_Pin_9
#define OUTPUT_6_PIN        GPIO_Pin_10
#define OUTPUT_7_PIN        GPIO_Pin_11
#define OUTPUT_8_PIN        GPIO_Pin_11
#define OUTPUT_9_PIN        GPIO_Pin_8
#define OUTPUT_10_PIN       GPIO_Pin_9

typedef enum
{
    Output_1 = 1,
    Output_2,
    Output_3,
    Output_4,
    Output_5,
    Output_6,
    Output_7,
    Output_8,
    Output_9,
    Output_10,
    Output_all
} Output_TypeDef;


void Outputs_Init();
void Output_On(Output_TypeDef Output);
void Output_Off(Output_TypeDef Output);
void Inputs_Init();

#endif /* OUTPUTS_H_ */
