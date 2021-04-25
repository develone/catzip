
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <time.h>

/* A C++ program to implement itoa() */
#include <iostream>
using namespace std;
  
/* A utility function to reverse a string  */
void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}
// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;
  
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
  
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
  
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
  
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
  
    str[i] = '\0'; // Append string terminator
  
    // Reverse the string
    reverse(str, i);
  
    return str;
}

// Driver program to test implementation of itoa()
int main()
{
    char str[100];
    int addr=0x01400000;
    int iSecret, iGuess;
    /* initialize random seed: */
    srand (time(NULL));
    
    cout << "Base:10 " << itoa(1567, str, 10) << endl;
    cout << "Base:10 " << itoa(-1567, str, 10) << endl;
    cout << "Base:2 " << itoa(1567, str, 2) << endl;
    cout << "Base:8 " << itoa(1567, str, 8) << endl;
    cout << "Base:16 " << itoa(1567, str, 16) << endl;
    
    int i;
   //char command "./arm-wbregs 0x01400000";
   //printf( "Memory size occupied by data : %d\n", sizeof(data));
   for (i=0; i<8191; i++){
      addr+=4;
      iSecret = rand() % 2147483648 + 0; 
      printf("addr 0x%x 0x%x\n",addr,iSecret);
      cout << "Base:10 " << itoa(iSecret, str, 10) << endl;
   }
   system("./arm-wbregs 0x01400000");
   
    return 0;
}
