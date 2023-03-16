/*
Name : Suraj Roy
Date 16/01/2023
Description : Implement a minimalistic shell, mini-shell(msh) as part of the Linux Internal module.
*/

#include"main.h"

void extract_external_commands(char **external_commands)
{
       //Variable declaration
       int i = 0;
       int j = 0;
       char buffer[25] = {'\0'};
       char ch;
       //Open the file
       int fd = open("external_commands.txt", O_RDONLY);
       if(fd == -1)
       {
	      printf("Open failed\n");
	      exit(1);
       }
       //Read the commands one by one
       while(read(fd, &ch, 1) > 0)
       {
	      if(ch != '\n')
	      {
		     buffer[i++] = ch;
	      }
	      else
	      {
		     //Allocate sufficient memory
		     external_commands[j] = calloc(strlen(buffer)+1, sizeof(char));
		     //copy the contents
		     strcpy(external_commands[j++], buffer);
		     //Append null character at the end
		     external_commands[j] = '\0';
		     //clear the buffer
		     memset(buffer, '\0', 25);
		     i = 0;
	      }
       }
}
