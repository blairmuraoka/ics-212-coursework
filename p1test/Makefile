project1: main.o iofunctions.o database.o menu.o
	gcc -o project1 main.o iofunctions.o database.o menu.o
	
database.o: database.c record.h
	gcc -c database.c
    
iofunctions.o: iofunctions.c record.h
	gcc -c iofunctions.c
	
main.o: main.c record.h
	gcc -c main.c
    
menu.o: menu.c record.h
	gcc -c menu.c
	
clean:
	rm project1 *.o