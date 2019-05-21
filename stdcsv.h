
#define file_vai "vai2.csv"
#define csv_delimiter ","

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

struct car* read_line(struct car* car_p){

	struct car* car_info = car_p;
	FILE *new_file;
	new_file = fopen(file_vai, "r");
	char line[128];
	
	fgets ( line, sizeof line, new_file );
	//printf("%s", line);
	
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
	}
	fclose(new_file);
	return car_info;
	
}

struct car* insert_bottom(char* headers[9],struct car* head) {
	struct car* current_node = head;
	struct car* new_node;
 	float min = atof(headers[4]), cons = atof(headers[5])/1000,mil=atof(headers[6])/1000, val = atof(headers[7]), km= atof(headers[8])/1000;
 	
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
	char *ptr = strtok(line, csv_delimiter);
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

