#include "const.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct trip {
	float average_speed;
	float average_rpm;
};

struct car {
	char* dongle;
	char* customer;
	char* started_at;
	char* finished_at;
	float minute;
	float consumption;
	float mileage;
	float cost;
	float kml;
	struct trip trip_info;
	struct car* next_car;
};
        
struct car* read_line(struct car* car_p);
struct car* insert_bottom(char* headers[9],struct car* head);
void print_list(struct car* car_info);
struct trip trip_average();
char* convert_date(char* string);
