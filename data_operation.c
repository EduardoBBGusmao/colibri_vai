#include "include/stdcsv.h"
#include "include/data_operation.h"

/*
 * This file contains functions that 
 * returns tips to improve car autonomy 
 *
 */
 struct car* check_autonomy(struct car* car_info)
{
	return car_info;
}

struct car* get_trips_period(struct car* car_info, struct car* this_trip, char* reference_start, char* reference_finished)
{
	struct car* current = car_info -> next_car;
        struct car* temp = this_trip;
        
        while (current != NULL){
        	if (data_range(current -> started_at, current -> finished_at, reference_start, reference_finished)) {
        	 
                        struct car* info_period = (struct car*)malloc(sizeof(struct car));
                        char* dongle_id = (char*)malloc(20*sizeof(char));
                        char* customer = (char*)malloc(20*sizeof(char));
	                char* date_start = malloc(11*sizeof(char)); 
	                char* date_finish = malloc(11*sizeof(char)); 
        	        
        	        strcpy(dongle_id, current->dongle);
        	        strcpy(customer, current->customer);
        	        strcpy(date_start, current->started_at); 
        	        strcpy(date_finish, current->finished_at); 
        	        
        	        info_period -> dongle = dongle_id;
        	        info_period -> customer = customer;
        	        info_period -> started_at = date_start;
        	        info_period -> finished_at = date_finish;
        	        info_period -> minute = current->minute;
        	        info_period -> consumption = current->consumption;
        	        info_period -> mileage = current->mileage;
        	        info_period -> cost = current->cost;
        	        info_period -> kml = current->kml;
        	        info_period -> trip_info = current->trip_info;  
        	        info_period -> next_car = NULL;    
        	        
        	        temp -> next_car = info_period;
        		temp = temp -> next_car;
        		
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
        for(int i =6; i<10; i++){
                year[i-6] = date[i];
        }
        year[5] = '\0';
        day_num = atoi(day);
        mounth_num = atoi(mounth);
        year_num = atoi(year);
        days = day_num;
        printf ("%d/%d/%d ", day_num, mounth_num, year_num);
        
        for (int i = 1; i < mounth_num; i++){
                days = days + mounth_days(i, year_num);
        }    
        for (int i = 0; i < year_num; i++){
                days = days + leap_year(year_num);
        }
        days = days + year_num;
        printf("days = %d\n", days);
        
        return days;
}

int mounth_days(int mounth, int year)
{
        if (mounth == 1 || mounth == 3 || mounth == 5 || mounth == 7 || mounth == 8 || mounth == 10 || mounth == 12){
                return 31;
        } else if (mounth == 2 && leap_year(year)) {
                return 29;
        } else if (mounth == 2) {
                return 28;
        } else {
                return 30;
        }       
}

int leap_year(int year){
        if (year % 4 == 0 && (year % 100 !=0 || year % 100 == 0)){
                return 1;
        }
        return 0;
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


