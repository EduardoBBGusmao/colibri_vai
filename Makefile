
output: read_csv.o stdcsv.o
	gcc read_csv.o stdcsv.o -o output

read_csv.o: read_csv.c
	gcc -c read_csv.c

stdcsv.o: stdcsv.c
	gcc -c stdcsv.c
        
clean:
	rm *.o output
