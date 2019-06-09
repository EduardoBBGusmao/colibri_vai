#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/stdcsv.h"
#include "include/data_operation.h"

int main(){

	struct car* car_info = NULL;
	struct car* temp = NULL;
	
	car_info = read_line(car_info);
	temp = choose_data_range(car_info,temp);
	print_perfomance(temp);
	free_list(car_info);
        free_list(temp);     
}

