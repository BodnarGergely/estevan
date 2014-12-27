/*
 * inputs.h
 *
 *  Created on: 2013.07.01.
 *      Author: Gergo
 */

#ifndef INPUTS_H_
#define INPUTS_H_

#include "stm32f4xx.h"

#define INPUT_PORT      GPIOD

#define INPUT_1_PIN     GPIO_Pin_6
#define INPUT_2_PIN     GPIO_Pin_7
#define INPUT_3_PIN     GPIO_Pin_3
#define INPUT_4_PIN     GPIO_Pin_2	//nem OK
#define INPUT_5_PIN     GPIO_Pin_1	//utcsó elötti
#define INPUT_6_PIN     GPIO_Pin_0	//utcsó


void Inputs_Init();


#endif /* INPUTS_H_ */
