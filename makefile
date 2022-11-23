a.out: main.o ex1.o
	gcc -Werror -o a.out main.o ex1.o

main.o: main.c ex1.h
	gcc -Werror -c -o main.o main.c

ex1.o: ex1.c
	gcc -Werror -c -o ex1.o ex1.c	

clean:
	rm -f *.o a.out
