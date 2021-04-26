
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <time.h>

/* A C++ program to implement itoa() */
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

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
    std::string Wr,Rd,randval,nextaddr;
    unsigned int microseconds;
                       //0   1   2   3    4  5   6   7   8   9   0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8   9   0   1   2   3
    //char commandwr[]={ '.','/','a','r','m','-','w','b','r','e','g','s',' ','0','x','0','1','4','0','0','0','0','0',' ','0','x','1','9','e','1','3','a','a','f',' ','>',' ','W','r','.','t','x','t','\0' };
    std::string commandwr="./arm-wbregs 0x1400000 0x19e13aaf > Wr.txt\n";
    Wr = commandwr;
    cout << Wr  ; 
    
    
    //char commandrd[]={ '.','/','a','r','m','-','w','b','r','e','g','s',' ','0','x','0','1','4','0','0','0','0','0',' ','>',' ','R','d','.','t','x','t','\0' };
    std::string commandrd="./arm-wbregs 0x01400000  > Rd.txt\n";
    Rd = commandrd;
    cout << Rd; 
    int addr=0x01400000;
    string wrline, rdline;
    int iWrMem;
    /* initialize random seed: */
    
    srand (time(NULL));
    /*
    cout << "Base:10 " << itoa(1567, str, 10) << endl;
    cout << "Base:10 " << itoa(-1567, str, 10) << endl;
    cout << "Base:2 " << itoa(1567, str, 2) << endl;
    cout << "Base:8 " << itoa(1567, str, 8) << endl;
    cout << "Base:16 " << itoa(1567, str, 16) << endl;
    */
    int i;
   
   for (i=0; i<8191; i++){
      addr+=4;
      nextaddr = itoa(addr, str, 16);
      cout << nextaddr.length() << endl;
      cout << nextaddr << endl;
      iWrMem = rand() % 2147483648 + 0;
      cout << "Base:10 " << itoa(iWrMem, str, 16) << endl; 
      printf("addr 0x%x 0x%x\n",addr,iWrMem);
      cout << "Base:16 " << itoa(iWrMem, str, 16) << endl;
      randval = itoa(iWrMem, str, 16);
      cout << randval << endl;
      Wr.replace(15,7,nextaddr);
      if (randval.length() < 8 ) {
        cout << randval.length() << endl;
        //Wr.replace(26,7,randval);
        //Wr.replace(32,1," ");
      }
      else Wr.replace(25,8,randval);
      
      cout << randval.length() << endl;
      
      cout << Wr.length() << endl;
      cout << Wr << endl;
       
      
   }
   
   //system("./arm-wbregs 0x01400000 0x19e13aaf > Wr.txt");
   cout << Wr.length() << endl;
   char* cmdstr = const_cast<char*>(Wr.c_str());
   std::cout << cmdstr;
   system(cmdstr);
   //usleep(25000);
   //sleep(10);
   //std::this_thread::sleep_for (std::chrono::seconds(10));
   //for(i=0;i<2147483648;i++);
   //system(commandrd);
   /*01400000 (     RAM)-> 19e13aaf*/
   
   fstream myfile;
    
   myfile.open ("Wr.txt",ios::in);
   if (myfile.is_open())
   {
        while(getline(myfile, wrline))
        {
           cout << wrline << '\n';
           cout << wrline.substr (22,30) << '\n';
        }
        myfile.close();
  }
  myfile.open ("Rd.txt",ios::in);
   if (myfile.is_open())
   {
        while(getline(myfile, rdline))
        {
           cout << rdline << '\n';
           cout << rdline.substr (29,37) << '\n';
        }
        myfile.close();
  }
  return 0;
}
//g++ bkram-wr-rd.cpp -o bk
