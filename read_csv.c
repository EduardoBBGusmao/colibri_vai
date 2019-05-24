#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdcsv.h"

void print_list(struct car* car_info);

int main(){

	struct car* car_info = (struct car*)malloc(sizeof(struct car));
	
	car_info = read_line(car_info);
	print_list(car_info);
	free(car_info);
}


// memory leak errors valgrind test
void print_list(struct car* car_info){
	struct car* temp = car_info;
		printf("aa\n");
	while (temp -> next_car != NULL){
		printf("dongle_id: %s || ", temp->dongle);
		printf("customer: %s || ", temp->customer);
		printf("started_at: %s || ", temp->started_at);
		printf("finished_at: %s || ", temp->finished_at);
		printf("minute: %.2f || ", temp->minute);
		printf("consumption: %.3f || ", temp->consumption);
		printf("mileage: %.3f km || ", temp->mileage);
		printf("cost: R$ %.2f || ", temp->cost);
		printf("kml: %.2f || ", temp->kml);
		printf("\n");
		if(temp -> next_car != NULL);
		temp = temp -> next_car;
	}
	free(temp);
}








