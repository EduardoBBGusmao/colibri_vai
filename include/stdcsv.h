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
struct car* insert_bottom(float headers_float[5], char* headers[4],struct car* head);
void print_list(struct car* car_info);
struct trip trip_average(char* reference);
char* convert_date(char* string);
void free_list(struct car* car_info);
struct car* insert_list(struct car* head, char* dongle_id, char* customer, char* date_start, char* date_end, float min, float cons, float mil, float val, float km, struct trip average_stats);
void print_node(struct car* temp);
