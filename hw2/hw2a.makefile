objects = hw2.o

default: hw2a

hw2a: hw2.o
        gcc -o hw2a hw2a.c
hw2a.o: hw2a.c
        gcc -c hw2a.c
clean:
        rm -f hw2a hw2a.o