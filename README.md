# Advanced Programming 1
## Exercise 1:

- To compile the program there are two options: <br />
 &emsp;1. Type `make` to activate the makefile, and then type `./a.out k file_path algorithm` to run the program <br />
 &emsp;2. Write the compling command: `g++ *.cpp -std=c++11` and then type `./a.out k file_path algorithm` to run the program <br />
Note: <br />
&emsp;`k` - number of neighbors (must be positive int)<br />
&emsp;`file_path` - the file path <br />
&emsp;`algorithm` - the distance algorithm (AUC-euclidean, MAN-manhattan, CHB-chebyshev, CAN-canberra, MIN-minkowski) <br />

- In minkowski distance, we chose `P = 2` as a default (can be changed manually in the function).
- If we divide by `0` in canberra distance algorithm we return `0`
- In our program, there is double check for valid input (one is enforced by the stringstream and the other by regex).<br />
The input will not be allowed if it doesn't follow these rules: <br />
&emsp;1. string of numbers <br />
&emsp;2. the string should start with at least one number <br />
&emsp;3. the numbers can be floating point and negative <br />
&emsp;4. the numbers must be spereated by only once space <br />
&emsp;5. at least one number in the string <br />
- In our program, there is file input validation which must follow these rules: <br />
&emsp;1. the file cannot be empty <br />
&emsp;2. each line must contain X numbers followed by 1 string <br />
&emsp;3. in each line, the X numbers should appear as many as the previous line and must be greater than 0 <br />
In addition: both vectors (user's input and file's) must be the same size <br />
