#include "stdcsv.h"
struct car* read_line(struct car* car_p){

	struct car* car_info = car_p;
	FILE *new_file;
	new_file = fopen(file_vai, "r");
	if(!new_file){
	        printf("Error to open file ");
	        exit(1);
	}
	        
	char line[128];
	
	fgets ( line, sizeof line, new_file );
	
	
	while (fgets (line, sizeof line, new_file) != NULL){
		static int count = 0;
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
	struct car* new_node = (struct car*) malloc(sizeof(struct car));
	
 	float min = atof(headers[4]);
 	float cons = atof(headers[5])/1000;
 	float mil=atof(headers[6])/1000;
 	float val = atof(headers[7]);
 	float km= atof(headers[8])/1000;
 	
	while (current_node->next_car != NULL) {
		current_node = current_node->next_car;
	}
	
	strcpy(new_node -> dongle, headers[0]);
	strcpy(new_node -> customer, headers[1]);
	strcpy(new_node -> started_at, headers[2]);
	strcpy(new_node -> finished_at, headers[3]);
	new_node -> minute = min;
	new_node -> consumption = cons;
	new_node -> mileage = mil;
	new_node -> cost = val;
	new_node -> kml = km;
	new_node->next_car= NULL;
	
	if (current_node != NULL){
		current_node->next_car = new_node;
		
	} else {
		head = new_node;
	}
	
	free(new_node);
	//free(current_node);
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


