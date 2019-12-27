hw5: main.o iofunctions.o
	gcc -o hw5 main.o iofunctions.o
    
iofunctions.o: iofunctions.c account.h
	gcc -c iofunctions.c
	
main.o: main.c account.h
	gcc -c main.c
	
clean:
	rm hw5 *.o