/*
Name : Suraj Roy
Date 11/01/2023
Description : Implement communication between three related processes using two pipe
Sample Input : ./a.out ls -l '|' grep "three" '|' wc
Sample output :             1       9      61
 */
 
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

//function protype
int validate_args(int argc, char *argv[],int *cmd2, int *cmd3);

int main(int argc, char *argv[])
{
       //declare variables
       int pipe1[2], pipe2[2], cmd2, cmd3, status, pid1, pid2, pid3, stdout_dup, stdin_dup;

       // error check CLA 
       if(argc < 4)
       {
      	      printf("ERROR : Usage ./a.out <command 1> '|' <command 2> '|' <command 3>\n");
      	      return 0;
       }	
       
       // validate CLA and find cmd2 and cmd3 is present or not
       if(validate_args(argc, argv, &cmd2, &cmd3) == -1)
       {
      	      printf("ERROR : Usage ./a.out <command 1> '|' <command 2> '|' <command 3>\n");
      	      return 0;
       }
       
       //checking pipe is created or not
       if(pipe(pipe1) == -1 || pipe(pipe2) == -1) 
       {
      	      printf("ERROR : Pipe. Exiting....\n");
      	      return 0;
       }

       //create duplicate of stdin and stdout
       stdout_dup = dup(1);
       stdin_dup = dup(0);
       
       
       //create child1 process
       pid1 = fork();
       
       //write to pipe1 
       if(pid1 == 0)
       {
              // close read end and duplicate write end with stdout	    
      	      close(pipe1[0]);
      	      dup2(pipe1[1], 1);
      	      //execute the command on the contents of the pipe1
      	      execvp(argv[1], &argv[1]);
      	      exit(1);	  
       }
       else if(pid1 > 0)
       {
	      // Wait for child1 to exit
      	      wait(&status);
	      if(WIFEXITED(status)) 
	      {
		     // Close pipe1 write
	       	     close(pipe1[1]);
	       	     //duplicate read end
		     dup2(pipe1[0], 0);
		 
		     //create child2
		     pid2 = fork();
	      }
      	      
      	      //read from pipe1 & write to pipe2
	      if(pid2 == 0)
	      {
		     //reading in pipe2	    
		     close(pipe2[0]);
		     dup2(pipe2[1], 1);
		     //execute the command on the contents of the pipe2
		     execvp(argv[cmd2], &argv[cmd2]);
		     exit(1);
	      }
	      else if(pid2 > 0)
	      {
		     
		     // Wait for child2 to exit
		     wait(&status);
		     if(WIFEXITED(status)) 
		     { 
			    //restore stdout and stdin
			    dup2(stdout_dup, 1);
			    dup2(stdin_dup, 0);
			    
			    //create child3 
			    pid3 = fork(); 
		     }
		
		     //read from pipe2 and print to stdout
		     if(pid3 == 0)
		     {
			    close(pipe2[1]); 
			    dup2(pipe2[0], 0);
			    
			    execvp(argv[cmd3], &argv[cmd3]);
			    exit(1);
		     }
		     else if(pid3 == -1)
		     {
			    printf("ERROR : Fork()\n");
		     }
		     else
		     {
	    		    sleep(1);
	 	     }
	      }
	      else
	      {	    
		     printf("ERROR : Fork()\n");
	      }
       }
       else
       {
      	      printf("ERROR : Fork()\n");
       }
    
       return 0;
}


//function validate args and find command 2 & 3
int validate_args(int argc, char *argv[],int *cmd2, int *cmd3)
{
       int flag = 0;
       
       //traverse to last of cla
       for(int i = 1;i < argc;i++)
       {
      	      //compare string
      	      if(strcmp(argv[i], "|") == 0)
      	      {
	 	     if(i != 1 && i + 1 < argc)
		     {
	    		    argv[i] = NULL;
		    	    if(!flag)
			    {
				   //command 2
				   *cmd2 = i + 1;
				   flag = 1;
			    }
			    else
			    {
				   //command 3
				   *cmd3 = i + 1;
				   flag = 2;
			    }
		     }	
	      }
       }
       return flag == 2 ? 1 : -1;
}
