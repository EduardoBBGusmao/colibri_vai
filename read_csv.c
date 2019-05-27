#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdcsv.h"

int main(){

	struct car* car_info = (struct car*)malloc(sizeof(struct car));
	
	car_info = read_line(car_info);
	//print_list(car_info);
	free(car_info);
	
}










