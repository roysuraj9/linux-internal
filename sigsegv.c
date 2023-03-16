/*
Name : Suraj Roy
Date : 15/01/2023
Description : WAP to print the address which is causing Segmentation fault
Sample Input : ./a.out
Sample Output : 
Segmentation fault ..!! 
Address 0x10 caused error
*/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>

void handler(int signum, siginfo_t *siginfo, void *data)
{
       printf("Segmentation fault ..!! \nAddress %p caused error\n", siginfo->si_addr);
       exit(0);
}

int main()
{
       //sigaction structure
       struct sigaction act;

       //resetting variable
       memset(&act, 0, sizeof(act));

       //registering the handler
       act.sa_sigaction = handler;
       act.sa_flags = SA_SIGINFO;

       //register the signal handler for SIGSEGV signal
       sigaction(SIGSEGV, &act, NULL);
       
       //create the segmentation fault
       int *ptr = (int*)0x10;
       *ptr = 12;

       return 0;
}
