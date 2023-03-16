/*
Name : Suraj Roy
Date 02/01/2023
Description : WAP to create child process to execute command passed through command line
Sample Input : ./a.out date

Sample Output : 
This is the CHILD process, with id 15055
Tuesday 02 January 2023 02:14:12 PM IST
Child exited with status 0
 */
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
       int status;

       //validate command line arguments
       if(argc < 2)
       {
	      printf("Error : Please Pass the Command through CL.\nUsage : ./exec_child <command>\n");
	      return 0;
       }

       //create a child process using fork()
       int pid = fork();

       //parent process
       if(pid > 0)
       {
	      //checking child exit status 
	      wait(&status);

	      if(WIFEXITED(status))
	      {
		     printf("Child exited with status %d\n", WEXITSTATUS(status));
	      }
	      else
	      {
		     printf("Child terminated abnormally\n");
	      }
       }

       //child process
       else if(pid == 0)
       {
	      //print child process pid
	      printf("This is the CHILD process, with id %d\n", getpid());
	      //executed execlp and use cla input in execlp
	      execlp(argv[1], argv[1],(char *)NULL);
	      exit(0);
       }
       //failed
       else
       {
	      perror("fork");
	      exit(0);
       }
}
