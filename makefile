a.out: main.o VectorDistances.o
	g++ -std=c++11 main.o VectorDistances.o -o a.out

main.o: main.cpp VectorDistances.cpp 
	g++ -std=c++11 -c main.cpp

VectorDistances.o: VectorDistances.cpp 
	g++ -std=c++11 -c VectorDistances.cpp

clean:
	rm *.o run