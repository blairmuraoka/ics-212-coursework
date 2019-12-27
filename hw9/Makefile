Homework9: Homework9.class Homework9.h Homework9.c Homework9.java
	gcc -fPIC -shared\
		-I/usr/jdk/jdk1.7.0_51/include\
		-I/usr/jdk/jdk1.7.0_51/include/solaris\
		-I/home04/b/bmura/ics212/hw9/\
		-o libHomework9.so Homework9.c
    
Homework9.class: Homework9.java
	javac Homework9.java

Homework9.h: Homework9.class
	javah Homework9
    
run: libHomework9.so
	java -Djava.library.path=. Homework9 
	
clean:
	rm *.class *.so *.h 