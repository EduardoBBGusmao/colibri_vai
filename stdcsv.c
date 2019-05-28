#include "stdcsv.h"

struct car* read_line(struct car* car_p){

	struct car* car_info = car_p;
	FILE *new_file;
	new_file = fopen(vai_file, "r");
	if(!new_file){
	        printf("Error to open file ");
	        exit(1);
	}
	        
	char line[128];
	
	fgets ( line, sizeof line, new_file );
	
	
	while (fgets (line, sizeof line, new_file) != NULL){
		char *ptr = strtok(line, csv_delimiter);
		char *headers[9];
		int i=0;
		
		struct car* temp = (struct car*)malloc(sizeof(struct car));
		
		while(ptr != NULL){	
			headers[i] = ptr;
			i++;
			ptr = strtok(NULL, csv_delimiter);
		}
		
		car_info = insert_bottom(headers, car_p);
		free(temp);
		free(ptr);		
	}
	
	fclose(new_file);
	return car_info;
	
}

struct car* insert_bottom(char* headers[9],struct car* head) 
{
	struct car* current_node = head;
	struct car* new_node;
 	float min = atof(headers[4]);
 	float cons = atof(headers[5])/1000;
 	float mil=atof(headers[6])/1000;
 	float val = atof(headers[7]);
 	float km= atof(headers[8])/1000;
 	
	while ( current_node != NULL && current_node->next_car != NULL) {
		current_node = current_node->next_car;
	}
	
	new_node = (struct car*) malloc(sizeof(struct car));
	strcpy(new_node -> dongle, headers[0]);
	strcpy(new_node -> customer, headers[1]);
	strcpy(new_node -> started_at, headers[2]);
	strcpy(new_node -> finished_at, headers[3]);
	new_node -> minute = min;
	new_node -> consumption = cons;
	new_node -> mileage = mil;
	new_node -> cost = val;
	new_node -> kml = km;
	new_node -> next_car= NULL;
	//new_node -> trip_info = trip_average(); not working
	
	if (current_node != NULL){
		current_node->next_car = new_node;
	} else {
		head = new_node;
	}
	// free(new_node); not working
	return head;
	
}
void print_list(struct car* car_info)
{
	struct car* temp = car_info;
	
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
	};
	free(temp);
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
	
	fgets ( line, sizeof line, new_file );
	
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
		count++;
		a_speed = (a_speed*(count-1) + current_speed)/count;
		a_rpm = (a_rpm*(count-1) + current_rpm)/count;
		i=0;
		
	}
	fclose(new_file);
	current_average.average_speed = a_speed;
	current_average.average_rpm = a_rpm;
	return current_average;	
	        
}
