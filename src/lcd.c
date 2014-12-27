/*
 * lcd.c
 *
 *  Created on: 2013.07.01.
 *      Author: Gergo
 */


#include "lcd.h"

void __delay_cycles(int a)
{
    int i = 0;
    int f = 0;
    while(f<a)
    {
            while(i<60)
                {i++;}
        f++;
    }
}

void PulseLcm()
{
    LCM_OUT &= ~LCM_PIN_EN;
    __delay_cycles(400);
    LCM_OUT |= LCM_PIN_EN;
    __delay_cycles(400);
    LCM_OUT &= (~LCM_PIN_EN);
    __delay_cycles(400);
}

void SendByte(char ByteToSend, int IsData)
{
    LCM_OUT &= (~LCM_PIN_MASK);
    LCM_OUT |= (ByteToSend & 0xF0);

    if (IsData == TRUE)
    {
        LCM_OUT |= LCM_PIN_RS;
    }
    else
    {
        LCM_OUT &= ~LCM_PIN_RS;
    }
    PulseLcm();
    __delay_cycles(400);
    LCM_OUT &= (~LCM_PIN_MASK);
    LCM_OUT |= ((ByteToSend & 0x0F) << 4);

    if (IsData == TRUE)
    {
        LCM_OUT |= LCM_PIN_RS;
    }
    else
    {
        LCM_OUT &= ~LCM_PIN_RS;
    }

    PulseLcm();
    __delay_cycles(400);
}
void ReceiveStatus(char * ByteToReceive)
{
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    LCM_OUT &= (~(LCM_PIN_RS | LCM_PIN_EN | LCM_PIN_RW));
    LCM_OUT |= LCM_PIN_RW;
    LCM_OUT &= ~LCM_PIN_RS;

     *ByteToReceive = 0;
    PulseLcm();
    *ByteToReceive |= (LCM_IN & 0xF0);
    __delay_cycles(40000);

    LCM_OUT &= (~(LCM_PIN_RS | LCM_PIN_EN | LCM_PIN_RW));
    LCM_OUT |= LCM_PIN_RW;
    LCM_OUT &= ~LCM_PIN_RS;

    PulseLcm();
    *ByteToReceive |= ((LCM_IN & 0xF0) >> 4);
    __delay_cycles(40000);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}



void Cursor(char Row, char Col)
{
    char address;

    __delay_cycles(4000);

    if (Row == 0)
    {
        address = 0;
    }
    else if(Row == 1 )
    {
        address = 0x40;
    }
    else if(Row == 2 )
    {
        address = 0x10;
    }
    else
    {
        address = 0x50;
    }

    address |= Col;
    SendByte(0x80 | address, FALSE);

    __delay_cycles(4000);
}


void ClearLcmScreen()
{
    __delay_cycles(40000);
    SendByte(0x01, FALSE);
    __delay_cycles(40000);
    SendByte(0x02, FALSE);
    __delay_cycles(40000);
}

void InitializeLcm(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    LCM_OUT &= ~(LCM_PIN_MASK);

    __delay_cycles(32000);
    __delay_cycles(32000);
    __delay_cycles(32000);

    LCM_OUT &= ~LCM_PIN_RS;
    LCM_OUT &= ~LCM_PIN_EN;

    LCM_OUT = 0x20;
    PulseLcm();
    __delay_cycles(32000);
    LCM_OUT = 0x20;
    PulseLcm();
    __delay_cycles(32000);
    LCM_OUT = 0x20;
    PulseLcm();
    __delay_cycles(32000);

    SendByte(0x28, FALSE);
    SendByte(0x0E, FALSE);
    SendByte(0x01, FALSE);
    SendByte(0x06, FALSE);
}
void StrAlign(char * Text, char * Temp, char Mode)
{
    char i = 0, j = 0, k = 0;
    switch(Mode)
    {
    case 1:
        for(i=0; Text[i] != '\0'; i++)
            Temp[i] = Text[i];

        for(i; i < 16; i++)
            Temp[i] = ' ';
        Temp[16] = '\0';
        break;
    case 2:
        for(i=0; Text[i]!='\0'; i++);
        for(j=0; j < (16-i); j++)
            Temp[j] = ' ';
        for(j=0; j<i; j++)
            Temp[(15-j)] = Text[(i-1-j)];
        Temp[16] = '\0';
        break;
    case 3:
        for(i=0; Text[i] != '\0'; i++);
        j = ((16-i) >> 1);
        for(k=0; k<i; k++)
            Temp[j + i - 1 - k] = Text [i - 1 - k];
        for(k=0; k<j; k++)
            Temp[k] = ' ';
        for(k = (i+j); k<16; k++)
            Temp[k] = ' ';
        Temp[16] = '\0';
        break;
    case 4:
        for(i=0; Text[i] != '\0'; i++);
        for(k=0; k<i; k++)
            Temp[2 + i - 1 - k] = Text [i - 1 - k];
        for(k = (i+2); k<16; k++)
            Temp[k] = ' ';
        Temp[0] = '-';
        Temp[1] = '>';
        Temp[16] = '\0';
        break;
    default:
        break;
    }
}

void PrintStr(char * Text)
{
    char *c;

    c = Text;

    while ((c != 0) && (*c != 0))
    {
        SendByte(*c, TRUE);
        c++;
    }
    __delay_cycles(4000);
}

void dec2bcd(int value, char * temp) {
    char i=0, j=0, k=0;
    int divider = 1000000000;
       for(i = 10; i > 0; i--) {
               temp[(10-i)] = (char)(value/divider);
               if(temp[(10-i)]==0 && j==0 && k!=9)
               {k++;}
               else{
               j++; k++;}
               value -= temp[(10-i)]*divider;
               divider /= 10;
       }
}

MenuElement_Typedef display_fill_menu_temporary;
extern char temp [17];

void DisplayFill(MenuElement_Typedef menu_current, MenuElement_Typedef menu_first)
{
    display_fill_menu_temporary = menu_first;
    while(display_fill_menu_temporary.previous)
        display_fill_menu_temporary = *display_fill_menu_temporary.previous;
    display_fill_menu_temporary = *display_fill_menu_temporary.up;

    Cursor(0,0);
    __delay_cycles(40000);
    StrAlign(display_fill_menu_temporary.nev, temp, ALIGN_CENTER);
    PrintStr(temp);
    __delay_cycles(4000);

    Cursor(((menu_current.designator - menu_first.designator) + 1), 0);
    __delay_cycles(40000);
    StrAlign(menu_current.nev, temp, ALIGN_ARROW);
    PrintStr(temp);
    __delay_cycles(4000);

    if((menu_current.designator - menu_first.designator))
    {
        display_fill_menu_temporary = *(menu_current.previous);
        Cursor(((menu_current.designator - menu_first.designator)), 0);
        __delay_cycles(40000);
        StrAlign(display_fill_menu_temporary.nev, temp, ALIGN_LEFT);
        PrintStr(temp);
        __delay_cycles(4000);
    }

    if((menu_current.designator - menu_first.designator) == 2)
    {
        display_fill_menu_temporary = *(menu_current.previous);
        display_fill_menu_temporary = *(display_fill_menu_temporary.previous);

        Cursor(1, 0);
        __delay_cycles(40000);
        StrAlign(display_fill_menu_temporary.nev, temp, ALIGN_LEFT);
        PrintStr(temp);
        __delay_cycles(4000);
    }

    if(((menu_current.designator - menu_first.designator) + 1) < 3)
    {
        display_fill_menu_temporary = *(menu_current.next);
        Cursor(((menu_current.designator - menu_first.designator) + 2), 0);
        __delay_cycles(40000);
        StrAlign(display_fill_menu_temporary.nev, temp, ALIGN_LEFT);
        PrintStr(temp);
        __delay_cycles(4000);
    }

    if((((menu_current.designator - menu_first.designator) + 2) < 3) && (menu_current.next) && ((*menu_current.next).next))
    {
        display_fill_menu_temporary = *(menu_current.next);
        display_fill_menu_temporary = *(display_fill_menu_temporary.next);

        Cursor(3, 0);
        __delay_cycles(40000);
        StrAlign(display_fill_menu_temporary.nev, temp, ALIGN_LEFT);
        PrintStr(temp);
        __delay_cycles(4000);
    }
}
