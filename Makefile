CC=gcc
EXEC=output
CFLAGS= -g -Wall -Wextra

output: read_csv.o stdcsv.o data_operation.o 
	$(CC) -g read_csv.o stdcsv.o data_operation.o -o output
	
read_csv.o: read_csv.c
	$(CC) -c read_csv.c

stdcsv.o: stdcsv.c
	$(CC) -c stdcsv.c
	
data_operation.o: data_operation.c
	$(CC) -c data_operation.c

test_leap_year.o: 'test/test_leap_year.c' 
	$(CC) -c 'test/test_leap_year.c'
	
clean:
	rm -rf *.o
        
valgrind:
	valgrind -v --track-origins=yes --leak-check=full --show-reachable=yes --log-file='test/valgrind-out.txt' ./output


