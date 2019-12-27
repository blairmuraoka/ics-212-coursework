hw3b: hw3db.o hw3b.o hw3_getaddress.o
	gcc -o hw3b hw3b.o hw3db.o hw3_getaddress.o
	
hw3b.o: hw3b.c record.h
	gcc -c hw3b.c
	
record.o: hw3db.c record.h
	gcc -c hw3db.c
    
hw3_getaddress.o: hw3_getaddress.c
	gcc -c hw3_getaddress.c
	
clean:
	rm hw3b *.o