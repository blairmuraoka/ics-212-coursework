hw10: Animal.o main.o Animal.h
	g++ -o hw10 Animal.o main.o

Animal.o: Animal.cpp Animal.h
	g++ -c Animal.cpp

main.o: main.cpp Animal.h
	g++ -c main.cpp
	
clean:
	rm hw10 *.o