#include <iostream>
                         // Needed for memset (sets first num of bytes of the 
#include <string.h>        // block of memory pointed to by ptr to the specified
			 // value, interpreted as unsigned char)

#include <sys/socket.h>  // Needed for socket functions
#include <netdb.h>	 // Needed for socket functions
#include <unistd.h>      // for close(socketfd)

//[[[1]]] == Get addresses of host
int getaddrinfo(const char *node, const char *service, const struct addrinfo *host_info, struct addrinfo **res);
//[[[2]]] == Create a socket
int socket(int domain, int type, int protocol);
//[[[3]]] == Connect to google.com
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
//[[[4]]] == Send and receive data from google
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
ssize_t recv(int sockfd, void *buf, size_t len, int flags);

int main()
{
	
	int status;
	struct addrinfo host_info;	 // This will be the struct addrinfo() fills with data
	struct addrinfo *host_info_list; // Pointer to the linked list of host_info's 
					 // (multiple IP addresses for one host)

	// The MAN page of getaddressinfo() (which I gotta find) states "All other fields in the
	// structure pointed to by hints must contain either a 0 or a null pointer, as appropriate
	// When a struct is created in C++, it will be given a block of memory. This memory is not
	// necessary empty. Therefor I use the memset function to make sure all fields are NULL.
	memset(&host_info, 0, sizeof host_info);


	std::cout << "Setting up the structs..." << std::endl;

	host_info.ai_family = AF_UNSPEC;	// IP version not specified. Can be both.
	host_info.ai_socktype = SOCK_STREAM;    // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP

	// [[[[[[[2]]]]]]]
	// Now fill up the linked list of host_info structs with google's address information
	status = getaddrinfo("www.google.com", "80", &host_info, &host_info_list);

	// getaddrinfo returns 0 on success, or some other alue when an error occured
	// (translated into human readable text by the gai_strerror function)
	if (status !=0 ) std::cout << "awwwwww ssssnap. getaddrinfo error." << gai_strerror(status);

	//,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
	//,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Connecting to a server,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
	//,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
	
	int socket(int domain, int type, int protocol);
	std::cout << "Creating a socket!!!" << std::endl;
	int socketfd; // Socket descritpor (a TCP/IP assigned num that uniquely identifies a socket
		      // and TCP/IP connection)

	// Create a socket
	//[[[[[[[2]]]]]]]]	
	socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype, host_info_list->ai_protocol);

	if (socketfd == -1) std::cout << "No connection for j00.";

	// We are ready to connect to google.com, so we use the connect() system call
	//[[[[[[[3]]]]]]]]
	status = connect(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);

	if (status == -1) std::cout << "connect error!!!";
	
	// Send and receive data [using send() and recv() functions]
	std::cout << "send()ing message..." << std::endl;
	char *msg = "GET / HTTP/1.1\nhost: www.google.com\n\n";
	int len;
	ssize_t bytes_sent;
	len = strlen(msg);
	bytes_sent = send(socketfd, msg, len, 0);
	
	//If google's server sends data back to us, our socket will store this in a buffer. This buffer
	// can be read using the recv() call
	std::cout << "Waiting to receive data..." << std::endl;
	ssize_t bytes_received;
	char incoming_data_buffer[1000];
	bytes_received = recv(socketfd, incoming_data_buffer,1000,0);

	// if no data arrives, the program will just wait here until data arrives.
	
	if (bytes_received == 0)  std::cout << "Host shut down." << std::endl;
	if (bytes_received == -1) std::cout << "receieved error!!!" << std::endl;

	std::cout << bytes_received << " bytes recieved :" << std::endl;
	std::cout << incoming_data_buffer << std::endl;

	// Garbage collection. Frees memory used by linked list
	std::cout << "Receiving complete. Closing socket..." << std::endl;
	freeaddrinfo(host_info_list);
	close(socketfd);	

}


/*[[[1]]]*/ 
/***********************************************************************************
Writer   : Jeffrey Allen
Purpose  : Fill the struct "addrinfo" with data we need for 
           creating and connecting to my socket

Params   : *node      == Host want to connect to. Can be a hostname or IP
		   *service   == Port I want to connect to. Usually an int, but can also
	  		 be a service name like 'http'
		   *host_Info == Points to the addrinfo struct to fill
	   	   **res      == Points to the linked list of filled addrinfo structs

Return   : returns 0 if all succeeded or a non-zero in case of error

Reference: http://codebase.eu/tutorial/linux-socket-programming-c/#before_you_read 
***********************************************************************************/ 
int getaddrinfo(const char *node, const char *service, const struct addrinfo *host_info, struct addrinfo **res);




//[[[2]]] == Create a socket
/***********************************************************************************
Writer   : Jeffrey Allen
Purpose  : Fill the struct "addrinfo" with data we need for 
           creating and connecting to my socket

Params   : *node      == Host want to connect to. Can be a hostname or IP
		   *service   == Port I want to connect to. Usually an int, but can also
	  		 be a service name like 'http'
		   *host_Info == Points to the addrinfo struct to fill
	  	   **res      == Points to the linked list of filled addrinfo structs

Return   : returns 0 if all succeeded or a non-zero in case of error

Reference: http://codebase.eu/tutorial/linux-socket-programming-c/#before_you_read 
***********************************************************************************/ 
int socket(int domain, int type, int protocol);


//[[[3]]] == Connect to google.com
/***********************************************************************************
Writer   : Jeffrey Allen
Purpose  : Fill the struct "addrinfo" with data we need for 
           creating and connecting to my socket

Params   : *node      == Host want to connect to. Can be a hostname or IP
	  	   *service   == Port I want to connect to. Usually an int, but can also
	  		 be a service name like 'http'
	  	   *host_Info == Points to the addrinfo struct to fill
	  	   **res      == Points to the linked list of filled addrinfo structs

Return   : returns 0 if all succeeded or a non-zero in case of error

Reference: http://codebase.eu/tutorial/linux-socket-programming-c/#before_you_read 
***********************************************************************************/ 
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

//[[[4]]] == Send and receive data from google.com
/***********************************************************************************
Writer   : Jeffrey Allen
Purpose  : Send data to another socket 

Params   : sockfd : Socket descriptor the socket() call returns
		   buf	  : the message I want to send
		   len    : the length of the message. Equals strlen(buf)
		   flags  : Without this param, this call would be the same as write() call.
		            This param gives extra options. ***read send MAN page****

Return   : On success, returns num of chars sent. On error, -1 is returned, and
		   errorno is set appropriately. If I wanna know if my message was sent,
		   this value should be the same as strlen(buf)

Reference: http://codebase.eu/tutorial/linux-socket-programming-c/#before_you_read 
***********************************************************************************/ 
ssize_t send(int sockfd, const void *buf, size_t len, int flags);

/***********************************************************************************
Writer   : Jeffrey Allen
Purpose  : Reads data from buffer after a server responds

Params   : sockfd : Socket descriptor the socket() call returns
		   buf	  : The variable we want to store the data in (input buffer)
		   len    : amount of data the function will read from input buffer
		   flags  : ***Read the recv() MAN page***
		   Returns: This call returns the num of bytes received, or -1 if error
		            occured. The return value will be 0 when the peer has performed
				    an orderly shutdown.
					
					If no messages are available at the socket, the recv() call
					halts execution of your code and waits for a message to arrive.
					This behaviour is called "blocking." By default a socket is in
					blocking mode. A socket can also be in "non-blocking" mode so it
					will just continue if there is no data in buffer


Return   : On success, returns num of chars sent. On error, -1 is returned, and
		   errorno is set appropriately. If I wanna know if my message was sent,
		   this value should be the same as strlen(buf)

Reference: http://codebase.eu/tutorial/linux-socket-programming-c/#before_you_read 
***********************************************************************************/
ssize_t recv(int sockfd, void *buf, size_t len, int flags); 
