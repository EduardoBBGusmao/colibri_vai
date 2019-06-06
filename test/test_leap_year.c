#include <stdio.h>
#include <stdlib.h>
#include "../include/data_operation.h"

int main()
{
        int year = 2098;
        for (; year <= 2100; year++) {
                //printf("%d is ",year);
                int isleapyear = leap_year(year);
                if (isleapyear == 0) {
                     printf(" not ");   
                }
                //printf("a leap year.\n");
        }
        return 0;
}
