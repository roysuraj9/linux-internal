/*
Name : Suraj Roy
Date 28/12/2022
Description : WAP to make zombie process become orphan, print status of each state
Sample Input : ./a.out 

Sample Output : 
A child created with pid 10082
Name:	a.out
Umask:	0002
State:	S (sleeping)
Name:	a.out
State:	Z (zombie)
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
       //declare variables
       pid_t pid, pid2, pid3;
       char path[50];
       int fd, line, data;

       //create child process
       pid = fork();

       if(pid > 0)
       {
	      printf("A child created with pid %d\n", getpid());
	      
	      //print status of child(sleeping)
	      sprintf(path, "/proc/%d/status", pid);

	      fd = open(path, O_RDONLY);
	      if(fd != -1)
	      {
		     line = 0;
       		     data = 1;
		     while(line < 3)
		     {
			    data = read(fd, path, 1);
			    write(1, path, data);
			    if(path[0] == '\n')
				   line++;
		     }
	      }
	      //make parent to sleep
	      sleep(4);
	      
	      //print status of child(zombie)
	      sprintf(path, "/proc/%d/status", pid);
	      
	      fd = open(path, O_RDONLY);
	      if(fd != -1)
	      {
		     line = 0;
		     data = 1;
		     while(line < 2)
		     {
			    data = read(fd, path, 1);
			    write(1, path, data);
			    if(path[0] == '\n')
				   line++;
		     }
	      }
	      
	      pid3 = getpid();
	      //create another child 2 process
	      pid2 = fork();
	      
	      if(pid2 > 0)
	      {
		     exit(1);
	      }
	      //child 2 process
	      else if(pid2 == 0)
	      {
		     sleep(2);
		     printf("Process %d cleared by init\n", pid3);
	      }

	      else
	      {
		     perror("fork");
		     exit(1);
	      } 
       }
       //making child 1 to sleep
       else if(pid == 0)
       {
	      sleep(2);
	      
       }
       //failure
       else
       {
	      perror("fork");
	      exit(1);
       }
       return 0;
}
