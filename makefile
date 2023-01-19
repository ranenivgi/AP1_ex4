# Makefile for running two programs

# Choose the compiler.
CC = g++ -std=c++11
# Have the right clean command.
ifeq ($(OS),Windows_NT)
	CLN=del
else
	CLN=rm
endif

BUILD_FILES := server/Knn.o
BUILD_FILES += server/TCPServer.o
BUILD_FILES += client/TCPClient.o
BUILD_FILES += server/VectorDistances.o
BUILD_FILES += server/ProcessFile.o


all: $(BUILD_FILES) server.o client.o
	$(CC) $(BUILD_FILES) server.o -o server.out
	$(CC) $(BUILD_FILES) client.o -o client.out

run: $(BUILD_FILES) server.o client.o
	$(CC) $(BUILD_FILES) server.o -o server.out & $(CC) $(BUILD_FILES) client.o -o client.out

# Build the algs folder
%.o: %.cpp %.h
	$(CC) -c -o $@ $<

server.o: server/main.cpp
	$(CC) -c -o server.o server/main.cpp
client.o: client/main.cpp
	$(CC) -c -o client.o client/main.cpp

# Clean command
clean:
	$(CLN) *.o server.out client.out
