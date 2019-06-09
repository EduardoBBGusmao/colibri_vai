int date_to_days(char* date);
struct car* get_trips_period(struct car* car_info, struct car* this_trip, char* reference_start, char* reference_finished);
int* check_autonomy(struct car* car_info,int autonomy[5]);
int leap_year(int year);
int mounth_days(int mounth, int year);
int data_range(char* trip_date_start, char* trip_date_finished, char* request_start_date, char* request_finished_date);
void print_perfomance(struct car* car_info);
struct car* choose_data_range (struct car* car_info, struct car* temp,char date[11]);
char* today_date(char* date);
int get_weekday(char * str);
char* days_to_date(int g, char date[11]);

