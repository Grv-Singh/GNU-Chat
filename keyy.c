#include<stdio.h>
#include<math.h>
 
// Returns gcd of a and b
int gcd(int a, int h)
{
    int temp;
    while (1)
    {
        temp = a%h;
        if (temp == 0)
          return h;
        a = h;
        h = temp;
    }
}
 
// Code to demonstrate RSA algorithm
int main()
{
    // Two random prime numbers
    int p = 3;
    int q = 7;
 
    // First part of public key:
    int n = p*q;
 
    // Finding other part of public key.
    // e stands for encrypt
    int e = 2;
    int phi = (p-1)*(q-1);
    while (e < phi)
    {
        // e must be co-prime to phi and
        // smaller than phi.
        if (gcd(e, phi)==1)
            break;
        else
            e++;
    }

	FILE *fp;
	fp = fopen("publ_key.txt", "w");
	
	fprintf(fp, "%d\n", n);
	fprintf(fp, "%d", e);

	fclose(fp);
 
    return 0;
}
