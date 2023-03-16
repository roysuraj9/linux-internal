/*
Name : Suraj Roy
Date 16/01/2023
Description : Implement a minimalistic shell, mini-shell(msh) as part of the Linux Internal module.
*/

#include"main.h"
//Extract thr command until space or new line is encounter :
//eg: input_string [] = ls l
//ls
char *get_command(char *input_string)
{
       static char command[25] = {'\0'};
       int i = 0;
       while(1)
       {
	      if(*input_string == ' ' || *input_string == '\0')
	      {
		     break;
	      }
	      command[i++] = (*input_string);
	      input_string++;
       }
       command[i] = '\0';
       return command;
}
