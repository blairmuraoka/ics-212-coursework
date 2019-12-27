hw7a: main.o iofunctions.o
	gcc -o hw7a main.o iofunctions.o -lm
    
iofunctions.o: iofunctions.c
	gcc -c iofunctions.c
	
main.o: main.c
	gcc -c main.c
	
clean:
	rm hw7a *.o