/*
Name : Suraj Roy
Date : 27/12/2022
Description : WAP to avoid child becoming zombie without blocking parent
Sample Input : ./a.out
Sample Output : 
parent is running
parent is running
parent is running
parent is running
parent is running
Child 12130 terminated normally with exit status 0 parent terminating
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
       //declare vaiable
       pid_t pid;
       
       // Create a child process using fork()
       pid = fork();
       
       // parent, pid -> child pid
       if(pid > 0 )
       {
	      int status;
	      // check if child is exited or terminated
	      while(waitpid(pid, &status, WNOHANG) == 0)
	      {
		     printf("parent is running\n");
		     sleep(1);
	      }
	      
	      //check exit status of child
	      if(WIFEXITED(status))
	      {
		     printf("Child %d terminated normally with exit status %d parent terminating\n", pid, WEXITSTATUS(status));
	      }
	      exit(1);

       }
       
       //child, fork returns 0
       //make child sleep
       else if(pid == 0)
       {
	      sleep(5);
	      exit(0);
       }
       
       // fork returned -1 (failed)
       else
       {
	      perror("fork");
	      exit(1);
       }
 
       return 0;
}
