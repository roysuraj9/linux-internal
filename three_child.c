/*
Name : Suraj Roy
Date 02/01/2022
Description : WAP to create three child from the same parent
Sample Input : ./a.out
Sample Output : 
Child 1 with pid 15177 created
Child 2 with pid 15178 created
Child 3 with pid 15179 created
Child 15177 exited with status 0 
Child 15178 exited with status 0 
Child 15179 exited with status 0 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main()
{

       //create child1
       int pid1 = fork();

       if(pid1 < 0)
       {
	      printf("Error: fork() failed");
	      return 1;
       }
       else if (pid1 == 0)
       {
	      //child1 process
	      printf("Child 1 with pid %d created\n", getpid());
	      //exit
	      exit(0);
       }
       //parent process
       else
       {
	      //create child2
	      int pid2 = fork();

	      if(pid2 < 0)
	      {
		     printf("Error: fork() failed");
		     return 1;
	      }
	      else if (pid2 == 0)
	      {
		     //child1 process
		     printf("Child 2 with pid %d created\n", getpid());
		     //exit
		     exit(0);
	      }
	      else
	      {
		     //create child3
		     int pid3 = fork();

		     if(pid3 < 0)
		     {
			    printf("Error: fork() failed");
			    return 1;
		     }
		     else if (pid3 == 0)
		     {
			    //child1 process
			    printf("Child 3 with pid %d created\n", getpid());

			    //exit
			    exit(0);
		     }
		     else
		     {
			    //parent process
			    int status, wpid, i = 0;
			    sleep(1);
		    
			    for(i = 0; i < 3; i++)
	    		    {
   				   //wait for children
				   wpid = wait(&status);

			   	   //check exit status of child
		   		   if(WIFEXITED(status))
	   			   {
  					  printf("Child %d exited with status %d\n", wpid, WEXITSTATUS(status));
			   	   }
		    	    }
	     	     }
      	      }
       }
       return 0;
}
