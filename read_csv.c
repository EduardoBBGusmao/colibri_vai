#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define file_vai "vai3.csv"
int contando = 0;
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


FILE* open_file(); 
struct car* read_line(struct car* car_info);
char* find_hearders();
void print_list(struct car* car_info);
struct car* insert_bottom(char* hearders[9],struct car* head);

int main(){

	char* head_line = find_hearders();
	struct car* car_info = (struct car*)malloc(sizeof(struct car));
	car_info = read_line(car_info);
	print_list(car_info);
}

struct car* read_line(struct car* car_p){

	struct car* car_info = car_p;
	FILE *new_file;
	new_file = fopen("vai2.csv", "r");
	char line[128];
	
	fgets ( line, sizeof line, new_file );
	//printf("%s", line);
	
	while (fgets (line, sizeof line, new_file) != NULL){
		static int count = 0;
		char *ptr = strtok(line, ",");
		char *headers[9];
		int i=0;
		
		struct car* temp = (struct car*)malloc(sizeof(struct car));
		
		while(ptr != NULL){	
			headers[i] = ptr;
			i++;
			ptr = strtok(NULL, ",");
		}
		
		car_info = insert_bottom(headers, car_p);
		free(temp);
	}
	return car_info;
	
}

struct car* insert_bottom(char* headers[9],struct car* head) {
	struct car* current_node = head;
	struct car* new_node;
 	float min = atof(headers[4]), cons = atof(headers[5]),mil=atof(headers[6]), val = atof(headers[7]), km= atof(headers[8]);
 	
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
	new_node->next_car= NULL;
	
	if (current_node != NULL)
		current_node->next_car = new_node;
	else
		head = new_node;
	
	return head;
}

char* find_hearders(){

	FILE *new_file;
	new_file = fopen("vai.csv", "r");
	char line[128];
	
	fgets ( line, sizeof line, new_file );
	char *ptr = strtok(line, ",");
	char *headers[9];
	int i=0;
	while(ptr != NULL){	
		headers[i] = ptr;
		printf("'%s'\n", headers[i]);
		i++;
		ptr = strtok(NULL, ",");
	}
	
	return headers[9];
	}

void print_list(struct car* car_info){
	struct car* temp = car_info;
		printf("aa\n");
	while (temp -> next_car != NULL){
		printf("dongle_id: %s || ", temp->dongle);
		printf("customer: %s || ", temp->customer);
		printf("started_at: %s || ", temp->started_at);
		printf("finished_at: %s || ", temp->finished_at);
		printf("minute: %.2f || ", temp->minute);
		printf("consumption: %.2f || ", temp->consumption);
		printf("mileage: %.2f || ", temp->mileage);
		printf("cost: %.2f || ", temp->cost);
		printf("kml: %.2f || ", temp->kml);
		printf("\n");
		temp = temp -> next_car;
	}
}


		/*
		temp -> dongle = headers[0];
		temp -> customer = headers[1];
		temp -> started_at = headers[2];
		temp -> finished_at = headers[3];
		temp -> minute = atof(headers[4]);
		temp -> consumption = atof(headers[5]);
		temp -> mileage = atof(headers[6]);
		temp -> cost = atof(headers[7]);
		temp -> kml = atof(headers[8]);
		temp -> next_car = NULL;
		
		if (count == 0){
			car_p = temp;
			
			count++;
		}
		else
			car_p -> next_car = temp;
		
		car_p = car_p -> next_car;*/
		






