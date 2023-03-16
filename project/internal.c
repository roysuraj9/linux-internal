/*
Name : Suraj Roy
Date 16/01/2023
Description : Implement a minimalistic shell, mini-shell(msh) as part of the Linux Internal module.
*/

#include"main.h"

void execute_internal_commands(char *input_string)
{
       //exit
       if(strncmp("exit", input_string, 4) == 0)
       { 
	      exit(1);
       }
       //pwd --> Print the present working directory
       if(strncmp("pwd", input_string, 4) == 0)
       {
	      system("pwd");
       }
       //cd --> change the directory eg : input_string[] = cd abc
       if(strncmp("cd", input_string, 2) == 0)
       {
	      int i = 3;
	      //check if extra blank space is present between cd and filename or not
	      //implement cd         abc 
	      while(*(input_string+i) == ' ')
	      {
		     i++;
	      }

	      chdir(&input_string[i]);
       }
}
