#include <stdio.h>
#include <stdlib.h>
#include "../include/data_operation.h"

int main()
{
        int year = 1990;
        for (; year <= 2100; year++) {
                printf("%d is ",year);
                if (leap_year(year) == 0) {
                     printf(" not ");   
                }
                printf("a leap year.\n");
        }
        return 0;
}