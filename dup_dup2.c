/*
Name : Suraj Roy
Date 27/12/2022
Description :  WAP to understand usage of dup and dup2 system calls
 */
 
#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
       //declare variable
       int fd;

       //check valid agrument passed in cla
       if(argc != 2)
       {
	      printf("Invalid Input\n");
	      return -1;
       }

       //open file in write given by user in cla
       fd = open(argv[1], O_CREAT | O_WRONLY, 0664);
       
       //close stdout
       close(1);
       
       //using dup to create duplicate on unused lower descriptor
       //redirect printf out to a given file
       dup(fd);
       printf("Print this message into the file by dup\n");
       
       //using dup2 and redirect printf out to a given file
       dup2(fd, 1);
       printf("Print this message into the file by dup2\n");
       
       //close file
       close(fd);
}
