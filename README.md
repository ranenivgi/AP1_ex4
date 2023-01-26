# Advanced Programming 1
## Exercise 4:

In this exercise we created an interaction between a server and a client. <br />

The server's job is to create a new thread for each client. As a result, it will to be able to handle multiple clients simultaneously. Then, it will activate the CLI for each client. The CLI's job is to receive an input from the client and activate commands. <br />

The client's job is to run 2 different threads, the first receiving data from the server and the second is sending to the server data from the user. This way we can send messages in parallel to receiving messages from the server. <br />

We used the Command design pattern in order to make the server able to seperate the commands. We created the abstract class `Command` which each command subclass implements, and then stored them in an array which is also used as a menu, which allowed us to activate them given an index from the client. <br />


## Running
To run the program follow these: <br />
 &emsp;1. Type `make` to activate the makefile<br />
 &emsp;2. Type `./server.out port` to activate the server<br />
 &emsp;3. In a separate terminal, type `./client.out server_ip port` to activate the client<br />

&emsp;`port` - the connection port <br />
&emsp;`server_ip` - the server ip the client is trying to connect <br />

## Commands
- In the `UploadData` command, both the classified and unclassified files must follow these rules:<br />
&emsp;1. the file cannot be empty <br />
&emsp;2. each line must contain X numbers <br />
&emsp;3. in each line, the X numbers should appear as many as the previous line and must be greater than 0 <br />
In addition, the classified file must follow this rule: <br />
&emsp;4. after the number, each line must contain the classification <br />

- In the `AlgorithmSettings` command the user must enter `K-neighbors algorithm` following these rules: <br />
  - `K-neighbors` - number of neighbors for KNN algorithm (must be positive - if it's floating point number it will be automaticlly round down) <br />
  - `algorithm` - the distance algorithm (AUC-euclidean, MAN-manhattan, CHB-chebyshev, CAN-canberra, MIN-minkowski) <br />
  
  Each of the two parts described above must be seperated with one space only! <br />

- Before the `ClassifyData` command make sure to upload data first. Note that we chose the minimum between `K-neighbors` and database size. <br />

- Before the `DisplayResults` command make sure to upload and classify data first. <br />

- Before the `DownloadResults` command make sure to upload data first. In this command the user enters folder's path and the command creates a txt file named `ClassifiedResults.txt` in the given folder. The command writes to the file the classification of the unclassified CSV file. Please make sure to enter correct folder's path. <br />
  
<ins>Vector distances notes:</ins> <br />

&emsp;1. in minkowski distance, we chose `P = 2` as a default (can be changed manually in the function). <br />
&emsp;2. if we divide by `0` in canberra distance algorithm we return `0`

Please make sure to insert valid data! (or the program will be manually closed)
