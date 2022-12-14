a.out: main.o VectorDistances.o Knn.o ProcessFile.o
	g++ -std=c++11 main.o VectorDistances.o Knn.o ProcessFile.o -o a.out

main.o: main.cpp VectorDistances.cpp Knn.cpp ProcessFile.cpp
	g++ -std=c++11 -c main.cpp

VectorDistances.o: VectorDistances.cpp 
	g++ -std=c++11 -c VectorDistances.cpp

Knn.o: Knn.cpp
	g++ -std=c++11 -c Knn.cpp

ProcessFile.o: ProcessFile.cpp
	g++ -std=c++11 -c ProcessFile.cpp
clean:
	rm *.o run