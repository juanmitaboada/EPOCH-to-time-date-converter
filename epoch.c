/*
EPOCH to human readable time and date converter for microcontrollers (PIC, AVR, Arduino, STM32)
Author: Siddharth Singh <sidsingh78@gmail.com>
Author: Juanmi Taboada <juanmi@juanmitaboada.com>
Ver:1.0
Date: Feb 25, 2019
*/

#include "epoch.h"

// Daylight saving time must be taken care of outside this function
// Remember to add or substract time zone to epoch before submiting it to this function (Example: epoch+=19800 ; //GMT +5:30 = +19800 seconds )
int epoch2date(unsigned long int epoch, unsigned int *year, unsigned short int *month, unsigned short int *day, unsigned short int *hour, unsigned short int *minute, unsigned short int *second, unsigned short int *day_of_week, unsigned short int *day_of_year) {

    static unsigned char month_days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    static unsigned char week_days[7] = {4,5,6,0,1,2,3}; //Thu=4, Fri=5, Sat=6, Sun=0, Mon=1, Tue=2, Wed=3

    unsigned char ntp_hour, ntp_minute, ntp_second, ntp_week_day, ntp_day, ntp_month, leap_days;
    unsigned short temp_days;
    unsigned int ntp_year, days_since_epoch, ntp_day_of_year; 

    unsigned int i;

    // Initialize
    leap_days=0; 

    // Calculate hour, minute & second
    ntp_second = epoch%60;
    epoch /= 60;
    ntp_minute = epoch%60;
    epoch /= 60;
    ntp_hour  = epoch%24;
    epoch /= 24;

    //number of days since epoch
    days_since_epoch = epoch;
    //Calculating WeekDay
    ntp_week_day = week_days[days_since_epoch%7];
    // ball parking year, may not be accurate!
    ntp_year = 1970+(days_since_epoch/365);

    // Calculating number of leap days since epoch/1970
    for (i=1972; i<ntp_year; i+=4) {
        if(((i%4==0) && (i%100!=0)) || (i%400==0)) {
            leap_days++;
        }
    }

    // Calculating accurate current year by (days_since_epoch - extra leap days)
    ntp_year = 1970 + ((days_since_epoch - leap_days)/365);
    ntp_day_of_year = ((days_since_epoch - leap_days)%365)+1;

    if(((ntp_year%4==0) && (ntp_year%100!=0)) || (ntp_year%400==0)) {
        month_days[1]=29;     // February = 29 days for leap years
    } else {
        month_days[1]=28; //February = 28 days for non-leap years 
    }

    temp_days=0;

    // Calculating current Month
    for (ntp_month=0 ; ntp_month <= 11 ; ntp_month++) {
        if (ntp_day_of_year <= temp_days) {
            break; 
        }
        temp_days = temp_days + month_days[ntp_month];
    }

    // Calculating current Date
    temp_days = temp_days - month_days[ntp_month-1];
    ntp_day = ntp_day_of_year - temp_days;

    // Asign results
    (*year) = ntp_year;
    (*month) = ntp_month;
    (*day) = ntp_day;
    (*hour) = ntp_hour;
    (*minute) = ntp_minute;
    (*second) = ntp_second;
    (*day_of_week) = ntp_week_day;
    (*day_of_year) = ntp_day_of_year;

    return 0;
}
