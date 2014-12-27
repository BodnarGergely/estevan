/*
 * ADC_Driver.h
 *
 *  Created on: 2014.07.16.
 *      Author: Gergo
 */

#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

#define NUMBER_OF_CONVERSIONS			10
#define SIZE_OF_OVERHEAD				2
#define SIZE_OF_PACK					(NUMBER_OF_CONVERSIONS + SIZE_OF_OVERHEAD)

void ADC_Driver_Init();
void DMA_Config(void);
void ADC_GPIO_Config(void);

#endif /* ADC_DRIVER_H_ */
