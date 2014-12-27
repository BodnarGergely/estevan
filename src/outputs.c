/*
 * outputs.c
 *
 *  Created on: 2013.07.01.
 *      Author: Gergo
 */


#include "outputs.h"
#include "stm32f4xx.h"


void Outputs_Init()
{
      GPIO_InitTypeDef  GPIO_InitStructure;

      /* Output portok engedéélyezése */
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

      /* Output lábak inicializálása a C porton  */
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
      GPIO_Init(GPIOC, &GPIO_InitStructure);

      /* Output lábak inicializálása a D porton  */
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
      GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void Output_On(Output_TypeDef Output)
{
    switch(Output)
    {
        case Output_1:
            GPIO_SetBits(OUTPUT_1_PORT, OUTPUT_1_PIN);
        break;
        case Output_2:
            GPIO_SetBits(OUTPUT_2_PORT, OUTPUT_2_PIN);
        break;
        case Output_3:
            GPIO_SetBits(OUTPUT_3_PORT, OUTPUT_3_PIN);
        break;
        case Output_4:
            GPIO_SetBits(OUTPUT_4_PORT, OUTPUT_4_PIN);
        break;
        case Output_5:
            GPIO_SetBits(OUTPUT_5_PORT, OUTPUT_5_PIN);
        break;
        case Output_6:
            GPIO_SetBits(OUTPUT_6_PORT, OUTPUT_6_PIN);
        break;
        case Output_7:
            GPIO_SetBits(OUTPUT_7_PORT, OUTPUT_7_PIN);
        break;
        case Output_8:
            GPIO_SetBits(OUTPUT_8_PORT, OUTPUT_8_PIN);
        break;
        case Output_9:
            GPIO_SetBits(OUTPUT_9_PORT, OUTPUT_9_PIN);
        break;
        case Output_10:
            GPIO_SetBits(OUTPUT_10_PORT, OUTPUT_10_PIN);
        break;
    }
}
void Output_Off(Output_TypeDef Output)
{
    switch(Output)
    {
        case Output_1:
            GPIO_ResetBits(OUTPUT_1_PORT, OUTPUT_1_PIN);
        break;
        case Output_2:
            GPIO_ResetBits(OUTPUT_2_PORT, OUTPUT_2_PIN);
        break;
        case Output_3:
            GPIO_ResetBits(OUTPUT_3_PORT, OUTPUT_3_PIN);
        break;
        case Output_4:
            GPIO_ResetBits(OUTPUT_4_PORT, OUTPUT_4_PIN);
        break;
        case Output_5:
            GPIO_ResetBits(OUTPUT_5_PORT, OUTPUT_5_PIN);
        break;
        case Output_6:
            GPIO_ResetBits(OUTPUT_6_PORT, OUTPUT_6_PIN);
        break;
        case Output_7:
            GPIO_ResetBits(OUTPUT_7_PORT, OUTPUT_7_PIN);
        break;
        case Output_8:
            GPIO_ResetBits(OUTPUT_8_PORT, OUTPUT_8_PIN);
        break;
        case Output_9:
            GPIO_ResetBits(OUTPUT_9_PORT, OUTPUT_9_PIN);
        break;
        case Output_10:
            GPIO_ResetBits(OUTPUT_10_PORT, OUTPUT_10_PIN);
        break;
        case Output_all:
            GPIO_ResetBits(OUTPUT_1_PORT, OUTPUT_1_PIN);
            GPIO_ResetBits(OUTPUT_2_PORT, OUTPUT_2_PIN);
            GPIO_ResetBits(OUTPUT_3_PORT, OUTPUT_3_PIN);
            GPIO_ResetBits(OUTPUT_4_PORT, OUTPUT_4_PIN);
            GPIO_ResetBits(OUTPUT_5_PORT, OUTPUT_5_PIN);
            GPIO_ResetBits(OUTPUT_6_PORT, OUTPUT_6_PIN);
            GPIO_ResetBits(OUTPUT_7_PORT, OUTPUT_7_PIN);
            GPIO_ResetBits(OUTPUT_8_PORT, OUTPUT_8_PIN);
            GPIO_ResetBits(OUTPUT_9_PORT, OUTPUT_9_PIN);
            GPIO_ResetBits(OUTPUT_10_PORT, OUTPUT_10_PIN);
            break;

        default:
            break;
    }
}
