/*
 * lcd.h
 *
 *  Created on: 2013.07.01.
 *      Author: Gergo
 */

#ifndef LCD_H_
#define LCD_H_

#include "stm32f4xx.h"

#define     LCM_OUT               GPIOE->ODR
#define     LCM_IN                GPIOE->IDR

// connect RW leg to GND, and power supply rails to +5V and gnd
// Define symbolic LCM - MCU pin mappings
// We've set DATA PIN TO 4,5,6,7 for easy translation
//
#define     LCM_PIN_RS            GPIO_Pin_3          // P1.0
#define     LCM_PIN_EN            GPIO_Pin_8          // P1.1
#define     LCM_PIN_D7            GPIO_Pin_7          // P1.7
#define     LCM_PIN_D6            GPIO_Pin_6          // P1.6
#define     LCM_PIN_D5            GPIO_Pin_5          // P1.5
#define     LCM_PIN_D4            GPIO_Pin_4          // P1.4
#define     LCM_PIN_RW            GPIO_Pin_9

GPIO_InitTypeDef  GPIO_InitStructure;
#define     LCM_PIN_MASK  ((LCM_PIN_RS | LCM_PIN_EN | LCM_PIN_D7 | LCM_PIN_D6 | LCM_PIN_D5 | LCM_PIN_D4 | LCM_PIN_RW))

#define     FALSE                       0
#define     TRUE                        1

#define ALIGN_LEFT                      1
#define ALIGN_RIGHT                     2
#define ALIGN_CENTER                    3
#define ALIGN_ARROW                     4

#define MENU_LEVEL_MAX                  5

#define MENU_SPECIAL_FUNCTION_TIME_DATE 1
#define MENU_SPECIAL_FUNCTION_ONTOZES   2

//*********************************A LENYOMHATÓ GOMBOK KÓDJAI
#define MENU_DOWN                       7
#define MENU_UP                         8
#define MENU_ENTER                      9

#define DATE_CHANGER_FUNCTION_DATE      1
#define DATE_CHANGER_FUNCTION_TIME      2

#define ASCII_OFFSEET                   48
//*********************************A LENYOMHATÓ GOMBOK KÓDJAI

typedef struct MenuElement
{
    char * nev;
    char designator;
    int (*fgvnev)();
    struct MenuElement * next;
    struct MenuElement * previous;
    struct MenuElement * up;
    struct MenuElement * down;
} MenuElement_Typedef;


void __delay_cycles(int a);
void PulseLcm();
void SendByte(char ByteToSend, int IsData);
void ReceiveStatus(char * ByteToReceive);
void Cursor(char Row, char Col);
void ClearLcmScreen();
void InitializeLcm(void);
void StrAlign(char * Text, char * Temp, char Mode);
void PrintStr(char * Text);
void dec2bcd(int value, char * temp);
void DisplayFill(MenuElement_Typedef menu_current, MenuElement_Typedef menu_first);

#endif /* LCD_H_ */
