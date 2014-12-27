/*
 * list.h
 *
 *  Created on: 2013.07.01.
 *      Author: Gergo
 */

#ifndef LIST_H_
#define LIST_H_

#include "stm32f4xx.h"

typedef struct Watering
{
    char *nev;
    char designator;
    int (*fgvnev)();
    struct MenuElement * next;
    struct MenuElement * previous;
    struct MenuElement * up;
    struct MenuElement * down;

    char Watering_time[6];
    char Watering_lenght;
    char Watering_channel;
    char Watering_error;
} Watering_Typedef;

#define     WATERING_MAX_ELEMENT        7


#endif /* LIST_H_ */
