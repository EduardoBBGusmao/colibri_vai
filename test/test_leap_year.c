#include <stdio.h>
#include <stdlib.h>
#include "../include/data_operation.h"

int main()
{
        int year = 2098;
        for (; year <= 2100; year++) {
                //printf("%d is ",year);
                int is_leap_year = leap_year(year);
                if (is_leap_year == 0) {
                     //printf(" not ");   
                }
                //printf("a leap year.\n");
        }
        return 0;
}