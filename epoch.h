/*
EPOCH to human readable time and date converter for microcontrollers (PIC, AVR, Arduino, STM32)
Author: Siddharth Singh <sidsingh78@gmail.com>
Author: Juanmi Taboada <juanmi@juanmitaboada.com>
Ver:1.0
Date: Feb 25, 2019
*/

#include <stdio.h>
#include <stdlib.h>

// Daylight saving time must be taken care of outside this function
// Remember to add or substract time zone to epoch before submiting it to this function (Example: epoch+=19800 ; //GMT +5:30 = +19800 seconds )
int epoch2date(unsigned long int epoch, unsigned int *year, unsigned short int *month, unsigned short int *day, unsigned short int *hour, unsigned short int *minute, unsigned short int *second, unsigned short int *day_of_week, unsigned short int *day_of_year);
