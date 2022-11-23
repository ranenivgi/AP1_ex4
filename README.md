# Advanced Programming 1

EX1:

- To compile the program there are two options:
    1. Type "make" to activate the makefile, and then type "./a.out" to run the program
    2. Write the compling command: > g++ main.cpp VectorDistances.cpp, and then type "./a.out" to run the program

- In minkowski distance, we chose P = 2 as a default (can be changed manually in the function).
- If we divide by 0 in canberra distance algorithm we returned 0
- In our program, a valid input is:
    1. two strings of numbers
    2. the numbers (can be floating point and negative) spereated by only once space (starting with a number)
    3. at least one number in each string
    4. both strings have the same amount of numbers