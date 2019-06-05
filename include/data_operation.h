int date_to_days(char* date);
struct car* get_trips_period(struct car* car_info, struct car* this_trip, char* reference_start, char* reference_finished);
struct car* check_autonomy(struct car* car_info);
int leap_year(int year);
int mounth_days(int mounth, int year);
int data_range(char* trip_date_start, char* trip_date_finished, char* request_start_date, char* request_finished_date);
