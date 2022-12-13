a.out: main.o VectorDistances.o Knn.o Initialization.o
	g++ -std=c++11 main.o VectorDistances.o Knn.o Initialization.o -o a.out

main.o: main.cpp VectorDistances.cpp Knn.cpp Initialization.cpp
	g++ -std=c++11 -c main.cpp

VectorDistances.o: VectorDistances.cpp 
	g++ -std=c++11 -c VectorDistances.cpp

Knn.o: Knn.cpp
	g++ -std=c++11 -c Knn.cpp

Initialization.o: Initialization.cpp
	g++ -std=c++11 -c Initialization.cpp
clean:
	rm *.o run