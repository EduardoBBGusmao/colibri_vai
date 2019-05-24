#include "const.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct car {
	char dongle[20];
	char customer[20];
	char started_at[20];
	char finished_at[20];
	float minute;
	float consumption;
	float mileage;
	float cost;
	float kml;
	struct car* next_car;
};

struct car* read_line(struct car* car_p);
struct car* insert_bottom(char* headers[9],struct car* head);
char* find_hearders();

