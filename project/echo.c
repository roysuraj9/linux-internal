/*
Name : Suraj Roy
Date 16/01/2023
Description : Implement a minimalistic shell, mini-shell(msh) as part of the Linux Internal module.
*/

#include"main.h"

void echo(char *input_string, int status)
{
       //echo $? --> how last command got terminated
       if(strncmp("echo $?", input_string, 7) == 0)
       {
	      printf("%d\n", status);
       }
       //echo$$ --> PID of the project
       if(strncmp("echo $$", input_string,7) == 0)
       {
	      printf("%d\n", getpid());
       }
       // echo $SHELL --> print the executable path
       if(strncmp("echo $SHELL",input_string, 11) == 0)
       {
	      system("pwd");
       }
       
}
