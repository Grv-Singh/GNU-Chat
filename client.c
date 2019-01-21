// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <math.h>
#define PORT 8080
  
int main(int argc, char const *argv[])
{
    int p = 3;
    int q = 7;

    int phi = (p-1)*(q-1);
	
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char hello[1024];
    char buffer[1024];    
    int n,e;
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
	
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
	
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

	printf("Enter your message: \n\t");
	scanf("%s",hello);
	int i=0;
	while(i<strlen(hello)){
		// Encryption c = (msg ^ e) % n
		hello[i] = (char)fmod(pow((int)hello[i],e),n);				
		i++;
	}
	printf("%s",hello);	

    send(sock , hello , strlen(hello) , 0 );
    printf("\nMessage sent\n");
    valread = read( sock , buffer, 1024);
	
	int j=0;
	while(buffer[j]!='\0'){		
		// Decryption m = (c ^ d) % n
		buffer[j] = (char)fmod(pow((int)buffer[j], d), n);
		j++;
	}

	printf("\nResponse = %s\n", buffer);
    return 0;
}
