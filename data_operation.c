#include "include/stdcsv.h"
#include "include/data_operation.h"

/*
 * This file contains functions that 
 * returns tips to improve car autonomy 
 *
 */

int* check_autonomy(struct car* car_info, int autonomy[5])
{
        autonomy[0] = 85;
        autonomy[1] = 1;
        autonomy[2] = 2;
        autonomy[3] = 3;
        autonomy[4] = 4;
	return autonomy;
}

struct car* get_trips_period(struct car* car_info, struct car* this_trip, char* reference_start, char* reference_finished)
{
	struct car* current = car_info -> next_car;
        struct car* temp = this_trip;
        
        while (current != NULL){
        	if (data_range(current -> started_at, current -> finished_at, reference_start, reference_finished)) {
        	 
                        char* headers[4] = {current->dongle, current->customer, current->started_at, current->finished_at};
        	        float headers_float[5];
        	        headers_float[0] = current->minute;
 			headers_float[1] = current->consumption;
 			headers_float[2] = current->mileage;
 			headers_float[3] = current->cost;
 			headers_float[4] = current->kml;
        	        
        	        this_trip = insert_bottom(headers_float, headers, this_trip);
        	        
        		
			}
		current = current ->next_car;
        }
        return this_trip;
}

int date_to_days(char* date)
{

        char day[3];
        char mounth[3];
        char year[5];
        int day_num;
        int mounth_num;
        int year_num;
        int days = 0;
        
        day[0] = date[0];
        day[1] = date[1];
        day[2] = '\0';
        mounth[0] = date[3];
        mounth[1] = date[4];
        mounth[2] = '\0';
        
        for(int i = 6; i<10; i++){
                year[i-6] = date[i];
        }
        year[4] = '\0';
        day_num = atoi(day);
        mounth_num = atoi(mounth);
        year_num = atoi(year);
        days = day_num;
        for (int i = 1; i < mounth_num; i++){
                days = days + mounth_days(i, year_num);
        }    
        for (int i = 0; i < year_num; i++){
                days = days + leap_year(year_num);
        }
        days = days + year_num;
                
        return days;
}

int mounth_days(int mounth, int year)
{
        if (mounth == 1 || mounth == 3 || mounth == 5 || mounth == 7 || mounth == 8 || mounth == 10 || mounth == 12){
                return 31;
        } else if (mounth == 2 && leap_year(year) == 366) {
                return 29;
        } else if (mounth == 2) {
                return 28;
        } else {
                return 30;
        }       
}

int leap_year(int year)
{
        if (year % 4 == 0 && (year % 100 !=0 || year % 400 == 0)){
                return 366;
        }
        return 365;
}

int data_range(char* trip_date_start, char* trip_date_finished, char* request_start_date, char* request_finished_date)
{
        if(date_to_days(request_start_date) <= date_to_days(trip_date_start) && 
           date_to_days(trip_date_finished) < date_to_days(request_finished_date) &&
           date_to_days(request_finished_date) > date_to_days(trip_date_start)){
                return 1;
        	 }
        return 0;
}


struct car* choose_data_range (struct car* car_info, struct car* temp)
{
        char* start_data = malloc(11*sizeof(char)); 
        char* finish_data = malloc(11*sizeof(char));     
        
        scanf("%s", start_data);
        scanf("%s", finish_data);
        temp = get_trips_period(car_info,temp, start_data, finish_data);
        free(start_data);
        free(finish_data);
        
        return temp;
}

void print_perfomance(struct car* car_info)
{
        print_list(car_info);
        int* autonomy;
        autonomy = check_autonomy(car_info, autonomy);
        
        printf("\nFoi obtido %d%% do seu desempenho ideal\n", (autonomy[0]));
        printf("A troca de marcha foi feita %d vezes de modo equivocado\n", (autonomy[1]+autonomy[2]));
        printf("A marcha foi trocada %d vezes de maneira antecipadamente\n", autonomy[1]);
        printf("A marcha foi trocada %d vezes de maneira tardiamente\n", autonomy[2]);
        printf("%d acerelações bruscas\n", autonomy[3]);
        printf("%d frenagens bruscas\n", autonomy[4]);

}
