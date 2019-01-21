// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <math.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
	
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024];
    char hello[1024];
    int n,e;

    // Two random prime numbers
    int p = 3;
    int q = 7;
 
    // Finding other part of public key.
    // e stands for encrypt
    double phi = (p-1)*(q-1);
	
	FILE *fptr;
	fptr = fopen("publ_key.txt", "r");
	
	if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

	//Getting Public Key	

	fscanf(fptr, "%d\n%d", &n, &e);
    	fclose(fptr);

	// Private key (d stands for decrypt)
    // choosing d such that it satisfies
    // d*e = 1 + k * totient
    int k = 2;  // A constant value
    double d = (1 + (k*phi))/e;  
     
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read( new_socket , buffer, 1024);
	
	int i=0;
	while(buffer[i]!='\0'){		
		// Decryption m = (c ^ d) % n
		buffer[i] = (char)fmod(pow((int)buffer[i], d), n);
		i++;
	}
	printf("%s",hello);

	printf("\nResponse = %s\n", buffer);
	printf("Enter your message: \n\t");
	scanf("%s",hello);
	
	// Encryption c = (msg ^ e) % n
	int j=0;
	while(hello[j]!='\0'){
		// Encryption c = (msg ^ e) % n
		hello[j] = (char)fmod(pow((int)hello[j], e), n);
		j++;
	}
	
	send(new_socket , hello , strlen(hello) , 0 );
    printf("Message sent\n");
    return 0;
}
