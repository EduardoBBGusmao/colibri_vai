#include "include/stdcsv.h"


/*
 *                                           
 * Functions to read csv files         
 * and put in linked lists             
 *
 */


struct car* read_line(struct car* car_p)
{
	char line[128];
	FILE *new_file;
	new_file = fopen(vai_file, "r");
	if(!new_file){
	        printf("Error to open file ");
	        exit(1);
	}


	while (fgets (line, sizeof line, new_file) != NULL){
		char *ptr = strtok(line, csv_delimiter);
		char *headers[9];
		int i=0;


		while(ptr != NULL){	
			headers[i] = ptr;
			i++;
			ptr = strtok(NULL, csv_delimiter);
		}

		car_p = insert_bottom(headers, car_p);
	}
	
	fclose(new_file);
	return car_p;

}

struct car* insert_bottom(char* headers[9],struct car* head) 
{
	struct car* current_node = head;
	struct car* new_node = (struct car*)malloc(sizeof(struct car));
 	float min = atof(headers[4]);
 	float cons = atof(headers[5])/1000;
 	float mil = atof(headers[6])/1000;
 	float val = atof(headers[7]);
 	float km = atof(headers[8])/1000;
	char* date_start = convert_date(headers[2]);
	char* date_end = convert_date(headers[3]);
        char* dongle_id = (char*)malloc(20*sizeof(char));
        char* customer = (char*)malloc(20*sizeof(char));
        
        if (!dongle_id){
        	printf("allocation not possible");
        	exit(1);
        } 
        if (!customer){
        	printf("allocation not possible");
        	exit(1);
        }
        if (!new_node){
        	printf("allocation not possible");
        	exit(1);
        }
     	
        strcpy(dongle_id, headers[0]);
        strcpy(customer, headers[1]);
        
	while (current_node != NULL && current_node->next_car != NULL) {
		current_node = current_node->next_car;
	}
	new_node -> dongle = dongle_id;
	new_node -> customer = customer;
	new_node -> started_at = date_start;
	new_node -> finished_at = date_end;
	new_node -> minute = min;
	new_node -> consumption = cons;
	new_node -> mileage = mil;
	new_node -> cost = val;
	new_node -> kml = km;
	new_node -> next_car= NULL;
	new_node -> trip_info = trip_average(); //not working

	if (current_node != NULL){
		current_node->next_car = new_node;
	} else {
		return new_node;
	}
	
	return head;

}
void print_list(struct car* car_info)
{
	struct car* temp = car_info->next_car;

	while (temp != NULL){
		printf("dongle_id: %s || ", *(&temp->dongle));
		printf("customer: %s || ", temp->customer);
		printf("started_at: %s || ", temp->started_at);
		printf("finished_at: %s || ", temp->finished_at);
		printf("minute: %.2f || ", temp->minute);
		printf("consumption: %.3f || ", temp->consumption);
		printf("speed average: %.2f km/hr || ", temp->trip_info.average_speed);
		printf("rpm average: %.2f rpm || ", temp->trip_info.average_rpm);
		printf("mileage: %.3f km || ", temp->mileage);
		printf("cost: R$ %.2f || ", temp->cost);
		printf("kml: %.2f || ", temp->kml);
		printf("\n");
		temp = temp -> next_car;
	};
	
}

struct trip trip_average()
{
	int count = 0;
	int i=0;
	float current_speed;
	float current_rpm;
	float a_speed = 0;
	float a_rpm = 0;
	FILE *new_file;
	new_file = fopen(trip_file, "r");
	struct trip current_average;

	if(!new_file){
	        printf("Error to open file ");
	        exit(1);
	}

	char line[128];

	fgets (line, sizeof line, new_file);

	while (fgets (line, sizeof line, new_file) != NULL){

		char *ptr = strtok(line, csv_delimiter);
		char *headers[3];

		while(ptr != NULL || i < 3){	
			headers[i] = ptr;
			i++;
			ptr = strtok(NULL, csv_delimiter);
		};
		current_speed = atof(headers[0]);
		current_rpm = atof(headers[1]);
		if (current_speed != 0){
		        count++;
		        a_speed = (a_speed*(count-1) + current_speed)/count;
		        a_rpm = (a_rpm*(count-1) + current_rpm)/count;
		}
		i=0;

	}

	fclose(new_file);
	
	current_average.average_speed = a_speed;
	current_average.average_rpm = a_rpm;
	return current_average;	

}

char* convert_date(char* string)
{
	char* date = malloc(11*sizeof(char)); 
	if (!date){
        	printf("allocation not possible");
        	exit(1);
        }
	
	for(int j = 0; j < 10; j++){
		date[j] = string[j];
	}
	date[10] = '\0';
	return date;
	
}

void free_list(struct car* car_info)
{
        struct car* curr = car_info;
	while((curr = car_info) != NULL){
	        car_info= car_info -> next_car;
	        free(curr->dongle);
	        free(curr->customer);
	        free(curr->started_at);
	        free(curr->finished_at);
	        free(curr);
	}
}
