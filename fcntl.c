/*
Name : Suraj Roy
Date 07/01/2023
Description : WAP to understand advanced file control system calls
Sample Input : ./a.out f1.txt
Sample output :
PARENT PROCESS: locked file
PARENT PROCESS: writing to file f1.txt
PARENT PROCESS: unlocked file
CHILD PROCESS: locked file
CHILD PROCESS: writing to file f1.txt
CHILD PROCESS: unlocked file
 */

#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
       if(argc > 0)
       {
	      printf("Error: Insufficient arguments\nUsage: ./a.out <destination file>\n");
	      return 0;

       }
       //open file for writing
       int fd = open(argv[1], O_CREAT | O_WRONLY,0664);
    
       //initialize the flock fl
       struct flock fl; 
       //clearing fl
       memset(&fl, 0, sizeof(fl));
       
       //create a new process
       int pid = fork();

       //parent process
       if(pid > 0)
       {
	      //lock file for writing 
	      fl.l_type = F_WRLCK;
 	      fcntl(fd, F_SETLKW, &fl);
 	      
 	      printf("PARENT PROCESS: locked file\n");
 	      printf("PARENT PROCESS: writing to file %s\n", argv[1]);
 	      
 	      //write in given file
 	      char line[] = "Prime numbers upto 15 : ";
	      write(fd, line, strlen(line));
	      
	      char buff[10];
	      int flag = 0;


	      //write prime numbers upto 15 in given file
	      for(int i = 2; i <= 15; i++)
	      {
		     for(int j = 2; j < i; j++)
		     {
			    if(i % j == 0)
			    {
				   flag = 1;
				   break;
			    }
	     	     }
 		     if(flag == 0)
		     {
			    sprintf(buff, "%d ", i );
 			    write(fd, buff, strlen(buff));
		     }
	 	     flag = 0;
	      }
	      
	      printf("PARENT PROCESS: unlocked file\n");
	      //unlock the file
	      fl.l_type = F_UNLCK;
       }
       //child process
       else if(pid == 0)
       {
	      //lock file for writing 
	      fl.l_type =  F_WRLCK;
	      fcntl(fd, F_SETLKW, &fl);
	      
	      printf("CHILD PROCESS: locked file\n");
	      printf("CHILD PROCESS: writing to file %s\n", argv[1]);

	      //write in given file
	      char line[] = "\nFibonacci series upto 10 : ";
	      write(fd, line, strlen(line));
	      
	      int num1 = 0, num2 = 1, num3 = 0;
	      char buff[10];
      
	      //write fibonacci series upto 10 in given file
      	      while(num1 <= 10)
      	      {
	 	     sprintf(buff, "%d ", num1);
		     write(fd, buff, strlen(buff));
		     num3 = num1 + num2;
		     num1 = num2;
		     num2 = num3;
	      }

	      printf("CHILD PROCESS: unlocked file\n");
	      //unlock the file
	      fl.l_type = F_UNLCK;
       }
       else
       {
	      perror("fork failure\n");
	      exit(0);
       }
       //close file
       close(fd);
}
