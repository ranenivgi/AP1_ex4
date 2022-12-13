a.out: main.o VectorDistances.o Knn.o
	g++ -std=c++11 main.o VectorDistances.o Knn.o -o a.out

main.o: main.cpp VectorDistances.cpp Knn.cpp
	g++ -std=c++11 -c main.cpp

VectorDistances.o: VectorDistances.cpp 
	g++ -std=c++11 -c VectorDistances.cpp

Knn.o: Knn.cpp
	g++ -std=c++11 -c Knn.cpp

clean:
	rm *.o run