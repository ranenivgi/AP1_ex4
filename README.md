# Advanced Programming 1
## Exercise 3:

In this exercise we created an interaction between a server and a client. <br />
The server's job is to receive an input from the client includes unclassifed vector, distance algorithm to use and number of neighbors, and returns the type of the vector, following the KNN algorithm, to the client. It also receives 2 arguments, the file of the classifed vectors and the port it should connect to. <br />
The client's job is to receive the above input and send it to the server, and then it receives back the type of the vector from the server and prints it.
It also receives 2 arguments, the server's IP and the port it should connect to. <br />

- To compile the program follow these: <br />
 &emsp;1. Type `make` to activate the makefile<br />
 &emsp;2. Type `./server.out file_path port` to activate the server<br />
 &emsp;3. In a separate terminal, type `./client.out server_ip port` to activate the client<br />

<ins>Note:</ins> <br />
&emsp;`file_path` - the classified vectors file path, it must follow these rules:<br />
&emsp;&emsp;1. the file cannot be empty <br />
&emsp;&emsp;2. each line must contain X numbers followed by 1 string <br />
&emsp;&emsp;3. in each line, the X numbers should appear as many as the previous line and must be greater than 0 <br />
&emsp;&emsp;4. each line must contain the classification <br />

&emsp;`port` - the connection port <br />

&emsp;`server_ip` - the server ip the client is trying to connect <br />

&emsp;Please make sure to insert valid data! (or the program will be closed)

- The next step is to send to the client an input following this format: `vector algorithm K-neighbors`
  - `vector` - numbers input which needs to follow these rules: <br />
&emsp;&emsp;1. string of numbers <br />
&emsp;&emsp;2. the string should start with at least one number <br />
&emsp;&emsp;3. the numbers can be floating point and negative <br />
&emsp;&emsp;4. the numbers must be spereated by only once space <br />
&emsp;&emsp;5. at least one number in the string <br />
&emsp;&emsp;6. the numbers amout must match the vector's numbers' amout in the file <br />
  
  - `algorithm` - the distance algorithm (AUC-euclidean, MAN-manhattan, CHB-chebyshev, CAN-canberra, MIN-minkowski) <br />
  - `K-neighbors` - number of neighbors for KNN algorithm (must be positive - if it's floating point number it will be automaticlly round down) <br />
  Each of the three parts described above must be seperated with one space only!
  
<ins>Vector distances notes:</ins> <br />

&emsp;1. in minkowski distance, we chose `P = 2` as a default (can be changed manually in the function). <br />
&emsp;2. if we divide by `0` in canberra distance algorithm we return `0`
