#include "include/stdcsv.h"
#include "include/data_operation.h"
#include <time.h>

/*
 * This file contains functions that 
 * returns tips to improve car autonomy 
 *
 */

int* check_autonomy(struct car* car_info, int* autonomy)
{
        autonomy = malloc(5*sizeof(int));
        autonomy[0] = 85;
        autonomy[1] = 1;
        autonomy[2] = 2;
        autonomy[3] = 3;
        autonomy[4] = 4;
	return autonomy;
}

struct car* get_period(struct car* c_in,struct car* this_trip,char* st,char* fin)
{
	struct car* c = c_in;
        struct car* temp = this_trip;
        
        while (c != NULL){
        	if (data_range(c->started_at, c->finished_at, st, fin)) {
        	 
                        char* headers[4] = {c->dongle, c->customer, c->started_at, c->finished_at};
        	        float headers_float[5];
        	        headers_float[0] = c->minute;
 			headers_float[1] = c->consumption;
 			headers_float[2] = c->mileage;
 			headers_float[3] = c->cost;
 			headers_float[4] = c->kml;
        	        
        	        this_trip = insert_bottom(headers_float, headers, this_trip);
        	        
        		
			}
		c = c->next_car;
        }
        print_list(this_trip);
        return this_trip;
}

int date_to_days(char* date)
{
        char day[3];
        char month[3];
        char year[5];
        int day_num;
        int month_num;
        int year_num;
        int days = 0;
        
        day[0] = date[0];
        day[1] = date[1];
        day[2] = '\0';
        month[0] = date[3];
        month[1] = date[4];
        month[2] = '\0';
        
        for (int i = 6; i<10; i++) {
                year[i-6] = date[i];
        }
        
        year[4] = '\0';
        day_num = atoi(day);
        month_num = atoi(month);
        year_num = atoi(year);
        days = day_num;
        
        for (int i = 1; i < month_num; i++) {
                days = days + month_days(i, year_num);
        }    
        
        for (int i = 0; i < year_num; i++) {
                days = days + leap_year(year_num);
        }
        
        days = days + year_num;
                
        return days;
}

int month_days(int month, int year)
{
        if (month == 1 || month == 3 || month == 5 || month == 7 ||
            month == 8 || month == 10 || month == 12)
                return 31;
        else if (month == 2 && leap_year(year) == 366)
                return 29;
        else if (month == 2)
                return 28;
        else 
                return 30;
               
}

int leap_year(int year)
{
        if (year % 4 == 0 && (year % 100 !=0 || year % 400 == 0))
                return 366;
        
        return 365;
}

int data_range(char* date_st, char* date_fin, char* req_st, char* req_fin)
{
        if(date_to_days(req_st) <= date_to_days(date_st)) {
                if(date_to_days(date_fin) < date_to_days(req_fin)) {
                        if(date_to_days(req_fin) > date_to_days(date_st)){
                                return 1;
        
                        }
                }
        }
        return 0;
}
 
struct car* choose_data_range(struct car* car_info,struct car* temp,char* date)
{
        char* start_date; 
        char* finish_date;     
        int last_sunday;
	finish_date = today_date(finish_date);
        last_sunday= date_to_days(finish_date)-7+2990; 
        if (get_weekday(finish_date) == sunday)
        	start_date = days_to_date(last_sunday, start_date);
        else {
            	free(finish_date);
                printf("Escolha o periodo das viagens\n");
                printf("Digite a data de inicio: (ex. 15/12/2018) \n");
                
                start_date = malloc(11*sizeof(char));
                scanf("%s", start_date);
                
                printf("Digite a data de termino da viagem: (ex. 15/12/2018) \n");                
                finish_date = malloc(11*sizeof(char));
                scanf("%s", finish_date);
        }
        
        temp = get_period(car_info,temp, start_date, finish_date);
    	free(start_date);
        free(finish_date);
        
        
        return temp;
}

void print_perfomance(struct car* car_info)
{
        int* autonomy;
        autonomy = check_autonomy(car_info, autonomy);
        
        printf("\nFoi obtido %d%% do seu desempenho ideal\n", (autonomy[0]));
        printf("A troca de marcha foi feita ");
        printf("%d vezes de modo equivocado\n", (autonomy[1]+autonomy[2]));
        printf("A marcha foi trocada");
        printf(" %d vezes de maneira antecipadamente\n", autonomy[1]);
        printf("A marcha foi trocada");
        printf(" %d vezes de maneira tardiamente\n", autonomy[2]);
        printf("%d acerelações bruscas\n", autonomy[3]);
        printf("%d frenagens bruscas\n", autonomy[4]);
        free(autonomy);

}

int get_weekday(char * str) 
{
	struct tm tm;
	memset((void *) &tm, 0, sizeof(tm));
	
	if (strptime(str, "%d/%m/%Y", &tm)) {
		time_t t = mktime(&tm);
		if (t >= 0) 
      			return localtime(&t)->tm_wday;
    		
  	}
  	
  	return -1;
}

char* today_date(char* date)
{	
	char year[5];
	char month[3];
	char day[3];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	date = malloc(11*sizeof(char));
	
	sprintf(year, "%d", tm.tm_year+1900);
	year[4] = '\0';
	    
	sprintf(month, "%d", tm.tm_mon+1);
	
	if (tm.tm_mon+1 <10) {
	        month[1] = month[0];
	        month[0] = '0';
	}
	
	sprintf(day, "%d", tm.tm_mday);
	
	if (tm.tm_mday <10) {
	        day[1] = day[0];
	        day[0] = '0';
	}
	
	date[0] = day[0];
	date[1] = day[1];
	date[2] = '/';
	date[3] = month[0];
	date[4] = month[1];
	date[5] = '/';
	date[6] = year[0];
	date[7] = year[1];
	date[8] = year[2];
	date[9] = year[3];
	date[10] = '\0';
	
	return date;	
}

char* days_to_date(int g, char* date)
{
	char str_day[2];
	char str_m[2];
	char str_y[4];
	int y = (10000*g + 14780)/3652425;
	int ddd = g - (365*y + y/4 - y/100 + y/400);
	int mm;
	int mi;
	int dd;
	
        date = malloc(11*sizeof(char));       
	
	if (ddd < 0) {
		y = y - 1;
		ddd = g - (365*y + y/4 - y/100 + y/400);
	}
	
	mi = (100*ddd + 52)/3060;
	mm = (mi + 2)%12 + 1;
	
	y = y + (mi + 2)/12;
	
	dd = ddd - (mi*306 + 5)/10 + 1;
	
	sprintf(str_day, "%d", dd);
	
	if (dd <10) {
		str_day[1] = str_day[0];
		str_day[0] = '0';
	}
	
	sprintf(str_m,"%d", mm);
	
	if (mm <10){
		str_m[1] = str_m[0];
		str_m[0] = '0';
	}
	
	sprintf(str_y, "%d",y); 
	date[0] = str_day[0];
	date[1] = str_day[1];
	date[2] = '/';
	date[3] = str_m[0];
	date[4] = str_m[1];
	date[5] = '/';
	date[6] = str_y[0];
	date[7] = str_y[1];
	date[8] = str_y[2];
	date[9] = str_y[3];
	date[10] = '\0';
	
	return date;
}
