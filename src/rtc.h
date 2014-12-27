/*
 * rtc.h
 *
 *  Created on: 2013.07.01.
 *      Author: Gergo
 */

#ifndef RTC_H_
#define RTC_H_

#define DATE_JEAR_BCD_1_OFFSET      20
#define DATE_JEAR_BCD_1             (0xF << DATE_JEAR_BCD_1_OFFSET)
#define DATE_JEAR_BCD_2_OFFSET      16
#define DATE_JEAR_BCD_2             (0xF << DATE_JEAR_BCD_2_OFFSET)

#define DATE_MONTH_BCD_1_OFFSET     12
#define DATE_MONTH_BCD_1            (0X1 << DATE_MONTH_BCD_1_OFFSET)
#define DATE_MONTH_BCD_2_OFFSET     8
#define DATE_MONTH_BCD_2            (0xF << DATE_MONTH_BCD_2_OFFSET)

#define DATE_DATE_BCD_1_OFFSET      4
#define DATE_DATE_BCD_1             (0x3 << DATE_DATE_BCD_1_OFFSET)

#define DATE_DATE_BCD_2_OFFSET      0
#define DATE_DATE_BCD_2             (0x7 << DATE_DATE_BCD_2_OFFSET)



#define TIME_HOUR_BCD_1_OFFSET      20
#define TIME_HOUR_BCD_1             (0x3 << TIME_HOUR_BCD_1_OFFSET)
#define TIME_HOUR_BCD_2_OFFSET      16
#define TIME_HOUR_BCD_2             (0xf << TIME_HOUR_BCD_2_OFFSET)

#define TIME_MINUTE_BCD_1_OFFSET    12
#define TIME_MINUTE_BCD_1           (0x7 << TIME_MINUTE_BCD_1_OFFSET)
#define TIME_MINUTE_BCD_2_OFFSET    8
#define TIME_MINUTE_BCD_2           (0xF << TIME_MINUTE_BCD_2_OFFSET)

#define TIME_SECOND_BCD_1_OFFSET    4
#define TIME_SECOND_BCD_1           (0x7 << TIME_SECOND_BCD_1_OFFSET)
#define TIME_SECOND_BCD_2_OFFSET    0
#define TIME_SECOND_BCD_2           (0xF << TIME_SECOND_BCD_2_OFFSET)


void RTC_Config(void);

#endif /* RTC_H_ */
