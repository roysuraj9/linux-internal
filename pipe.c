/*
Name : Suraj Roy
Date 07/01/2023
Description : Implement communication between two related processes using one pipe
Sample Input : ./a.out date '|' wc
Sample output :       1       7      39
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int validate_args(int argc, char *argv[], int *cmd2);

int main(int argc, char *argv[])
{
       int p[2], cmd2, status, pid1, pid2;
      
       //check CLA
       if(argc < 4)
       {
	      printf("Error : Usage ./a.out <command 1> '|' <command 2>\n");
      	      return 0;
       }	

       //validate CLA
       if(validate_args(argc, argv, &cmd2) == -1)
       {
      	      printf("Error : Usage ./a.out <command 1> '|' <command 2>\n");
      	      return 0;
       }
       
       // create pipe
       if(pipe(p) == -1) 
       {
	      printf("Error : Pipe. Exiting....\n");
      	      return 0;
       }
       //create duplicate of stdout
       int stdout_dup = dup(1);
       
       //create new process
       pid1 = fork();
       
       // child 1 process 
       if(pid1 == 0)
       {
	      // close read end and duplicate write end with stdout	    
	      close(p[0]);
	      dup2(p[1], 1);
	      execvp(argv[1], &argv[1]);
      	      exit(1);	  
       }
       else if(pid1 > 0)
       {
	      // wait for child1 process to end
      	      if(wait(&status))
      	      {
	     	     //create another process
		     pid2 = fork();
	     	     // restore the stdout
		     dup2(stdout_dup, 1);
	      }
      	    
	      // child 2 process
	      if(pid2 == 0)
      	      {	
		     // close the write end
	     	     close(p[1]);
	     	     //duplicate the read end with stdin 
	     	     dup2(p[0], 0);
		     //execute the command on the contents of the pipe
		     execvp(argv[cmd2], &argv[cmd2]);
		     exit(1);
      	      }
	      else if(pid2 > 0)
      	      {	    
		     sleep(1);
      	      }
	      else
      	      {
	     	     printf("Error : Fork()\n");     
      	      }
       }
       else
       {
      	      printf("Error : Fork()\n");
       }
       return 0;
}

//logic find '|' and command 2 is present
int validate_args(int argc, char *argv[],int *cmd2)
{
       for(int i = 1; i < argc; i++)
       {
	      //compare character to "|"
	      if(strcmp(argv[i], "|") == 0)
	      {
		     //logic to find command 2
		     if(i != 1 && i + 1 < argc)
		     {
			    argv[i] = NULL;
			    *cmd2 = i + 1;
			    return 1;
		     }	
		     return -1;
	      }
       }	
       return -1;
}

