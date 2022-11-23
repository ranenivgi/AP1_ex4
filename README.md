# Advanced Programming 1
Cancel changes
## Exercise 1:

- To compile the program there are two options: <br />
 &emsp;1. Type `make` to activate the makefile, and then type `./a.out` to run the program <br />
 &emsp;2. Write the compling command: `g++ main.cpp VectorDistances.cpp` and then type `./a.out` to run the program

- In minkowski distance, we chose `P = 2` as a default (can be changed manually in the function).
- If we divide by `0` in canberra distance algorithm we return `0`
- In our program, a valid input is: <br />
&emsp;1. two strings of numbers <br />
&emsp;2. the numbers (can be floating point and negative) spereated by only once space (starting with a number) <br />
&emsp;3. at least one number in each string <br />
&emsp;4. both strings have the same amount of numbers <br />
