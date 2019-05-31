CC=gcc
EXEC=output
output: read_csv.o stdcsv.o
	$(CC) read_csv.o stdcsv.o -o output

read_csv.o: read_csv.c
	$(CC) -c read_csv.c

stdcsv.o: stdcsv.c
	$(CC) -c stdcsv.c
        
clean:
	rm -rf *.o
	 
valgrind:
	valgrind -v --track-origins=yes --leak-check=full --show-reachable=yes --log-file='test/valgrind-out.txt' ./output
