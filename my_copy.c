/*
Name : Suraj Roy
Date 27/12/2022
Description : Implement a cp(copy) command with –p option
Sample Input : ./a.out f1.txt f2.txt 
Sample Output : New dest.txt file is created and source.txt file will be copied to dest.txt file
 */
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUFF_SIZE 255

int my_copy(int source_fd, int dest_fd);

int main(int argc, char *argv[])
{
       //declare variable
       int source_fd, dest_fd;
       char choice;
       struct stat statbuf;
       
       //check on cla sufficient arguments is passed or not
       if(argc < 3)
       {
	      printf("Error: Insufficient arguments\nUsage: ./my_copy [option] <source file> <destination file>");
	      return 0;

       }

       //if -p is passed
       if(strcmp(argv[1], "-p") == 0)
       {
	      ///opening soure file 
       	      if((source_fd = open(argv[2], O_RDONLY)) == -1)
	      {
		     perror("open");
		     return -1;
	      }
	      //retiving source information
	      fstat(source_fd, &statbuf);
	      //open dest file with source file permission 
	      dest_fd = open(argv[3], O_CREAT | O_EXCL | O_WRONLY , statbuf.st_mode);
       }
       else
       {
       	      if((source_fd = open(argv[1], O_RDONLY)) == -1)
	      {
		     perror("open");
		     return -1;
	      }
	      //open dest file with default permission
	      dest_fd = open(argv[2], O_CREAT | O_EXCL | O_WRONLY, 0664);
       }


       //dest is already present
       if(dest_fd == -1)
       {
	      if(errno == EEXIST)
	      {
		     //ask user permission to overwrite
		     printf("File “dest.txt” already exist, do you want to overwrite?(y/n)\n");
		     scanf("%c", &choice);
		     if(choice == 'y')
		     {
			    printf("Copied data and permissions from source to destination file\n");
			    //if -p is passed then copy data and file permission to dest 
			    if(strcmp(argv[1], "-p") == 0)
			    {
				   dest_fd = open(argv[3], O_TRUNC | O_WRONLY);
				   //change dest file permission to source file permission
				   fchmod(dest_fd, statbuf.st_mode);
			
			    }
			    //if -p not passed just copied data
			    else
			    {
				   
				   dest_fd = open(argv[2], O_TRUNC | O_WRONLY);
			    }
		     }
		     //if user choice n then close source and dest file
		     else
		     {
			    printf("Source and dest file is closed. Data not copied.\n");
			    close(source_fd);
			    close(dest_fd);
			    return 0;
		     }

	      }

       }
       //dest is not present
       else
       {
	      //if -p is passed then copy data and file permission to dest
       	      if(strcmp(argv[1], "-p") == 0)
	      {
		     dest_fd = open(argv[3], O_TRUNC | O_WRONLY);
		     fchmod(dest_fd, statbuf.st_mode);
		     printf("New dest.txt file is created and source.txt file including permissions will be copied to dest.txt file\n");
	      }
	      //if -p not passed just copied data
	      else
	      {
		     dest_fd = open(argv[2], O_TRUNC | O_WRONLY);
		     printf("New dest.txt file is created and source.txt file will be copied to dest.txt file\n");
	      }
       }
       //call function to copy source to dest 
       my_copy( source_fd, dest_fd);
       //close files
       close(source_fd);
       close(dest_fd);
       return 0;
}

//copy data from source to dest
int my_copy(int source_fd, int dest_fd)
{
	int read_len = 0;
	char buff[BUFF_SIZE];

	//read the data from the source till end and copy
	while( ((read_len = read(source_fd, buff, BUFF_SIZE)) != -1 ) && (read_len != 0))
	{
		if( write(dest_fd, buff, read_len) == -1 )
		{
			perror("write");
			close(source_fd);
			close(dest_fd);
			return -1;
		}
	}

	return 0;
}
