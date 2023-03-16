/*
Name : Suraj Roy
Date : 14/01/2023
Description : WAP to block certain signals from being received from command line.
*/

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void mysig_handler(int signum, siginfo_t *siginfo, void *data)
{
       printf("Signal number %d : \n", signum);
       int i = 20;
       while(i > 0)
       {
	      printf("I am in the handler\n");			
	      sleep(1);
	      i--;
       }
}

int main()
{
       struct sigaction newact;
       sigset_t set;

       newact.sa_flags = SA_SIGINFO;

       memset(&newact, 0, sizeof(newact)); //Clear memory
       newact.sa_sigaction = mysig_handler; //Assign your signal handler

       //Intialize the signal set
       sigemptyset(&set);

       //Add the signal 
       sigaddset(&set, SIGTERM);
       sigaddset(&set, SIGUSR1);
       sigaddset(&set, SIGABRT);
	
       newact.sa_mask = set;

       printf("PID of the process is %d\n", getpid());

       /* Register the signal handler for SIGINT signal */
       sigaction(SIGINT, &newact, NULL);
     
       while(1);
       return 0;
}
