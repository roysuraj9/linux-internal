/*
Name : Suraj Roy
Date 14/01/2023
Description :  WAP to avoid child become zombie by using signal handlers
Sample Input : ./a.out 
Sample output : Child  terminated with exit code 0
 */

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void handler(int signum, siginfo_t *info, void *data)
{
       //check signum is equal to SIGCHLD
       if(signum == SIGCHLD)
       {
	      printf("Child  terminated with exit code %d\n", info->si_status);
       }
}

int main()
{
       pid_t pid;

       //structure sigaction
       struct sigaction act;
       
       //register SIGSEGV
       act.sa_sigaction = handler;
       act.sa_flags = SA_SIGINFO | SA_NOCLDSTOP;

       sigaction(SIGCHLD, &act, NULL);

       //create new process
       pid = fork();

       //child process
       if( pid == 0)
       {
	      sleep(2);
       }
       //parent
       else if(pid > 0)
       {
	      sleep(5);
       }
       else
       {
	      printf("ERROR : fork");
       }
       return 0;
}
