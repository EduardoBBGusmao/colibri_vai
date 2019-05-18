#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define file_vai "vai.csv"

struct car {
	char* dongle;
	char* customer;
	char* started_at;
	char* finished_at;
	int minute;
	int consumption;
	int mileage;
	int cost;
	int kml;
	struct car* next_car;
};


FILE* open_file(); 
struct car* read_line(struct car* car_info);
char* find_hearders();
void print_list(struct car* car_info);

int main(){
	char* head_line = find_hearders();
	struct car* car_info = (struct car*)malloc(sizeof(struct car));
	car_info = read_line(car_info);
	print_list(car_info);
}

struct car* read_line(struct car* car_p){

	struct car* car_info = car_p;
	FILE *new_file;
	new_file = fopen("vai.csv", "r");
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
			//printf("'%s'\n", headers[i]);
			i++;
			ptr = strtok(NULL, ",");
		}
		/*strcpy(temp -> dongle, headers[0]);
		strcpy(temp -> customer, headers[1]);
		strcpy(temp -> started_at, headers[2]);
		strcpy(temp -> finished_at, headers[3]);*/
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
		
		car_p = car_p -> next_car;
		}
	return car_info;
	
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
		printf("%d\n", temp->mileage);
		temp = temp -> next_car;
	}	
}








