/*
Name : Suraj Roy
Date 14/01/2023
Description : Implement communication between three processes using PIPE, FIFO and SHM
Sample Input : ./writer 
Sample output : 
Enter a string : king
Write over
String read from pipe - KING
String copied to the shared memory
Reading from FIFO...
String read from FIFO - GNIK
 */
 
#include "main.h"

int main()
{
       //declare variables
       char string[50], buffer[50];
       int shmid, pipe_fd[2], status, fd;
       char *shm, buff = 'A', *myfifo = "myfifo";
       key_t key = 'S';
    
       //checking pipe created or not
       if(pipe(pipe_fd) == -1)
       {
      	      printf("ERROR\n");
      	      return 0;
       }
      
       printf("Enter a string : ");
       scanf("%s", string);
    
       //creating process
       pid_t pid = fork();
       
       //child process
       if(pid == 0)
       {
      	      //closing write end and reading pipe
      	      close(pipe_fd[1]);

      	      //read from pipe and convert string to uppercase	
      	      for(int i = 0; buff != 0; i++)
      	      {
		     if(read(pipe_fd[0], &buff, 1) == 0)
		     {
	    		    break;
		     }   
		     buffer[i] = toupper(buff);
	      }
	      close(pipe_fd[0]);
	      printf("String read from pipe - %s\n", buffer);
	      
	      //create a shared memory and store the string 
      	      shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666);

      	      if(shmid < 0)
      	      {
		     printf("ERROR : Shared memory not created");
		     return 0;
      	      }
      	      else
      	      {
	 	     //attach and store the string 
		     shm = shmat(shmid, NULL, 0);
		     strcpy(shm, buffer);
	      }
       }
       //parent process
       else if( pid > 0)
       {
	      //close read and write string to pipe 
	      close(pipe_fd[0]);
	      write(pipe_fd[1], string, strlen(string) + 1);
	      
	      close(pipe_fd[1]);
	      printf("Write over\n");

      	      //wait for child process to terminate
      	      wait(&status);
	
      	      printf("String copied to the shared memory\n");
      
	      //reading string from FIFO
      	      printf("Reading from FIFO...\n");

      	      fd = open(myfifo, O_RDONLY);
      	      read(fd, string, SHMSIZE);

      	      printf("String read from FIFO - %s\n", string);
      	      close(fd);
       }
       else
       {
      	      printf("ERROR : FORK FAILURE");
       }
}
