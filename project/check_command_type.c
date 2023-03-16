/*
Name : Suraj Roy
Date 16/01/2023
Description : Implement a minimalistic shell, mini-shell(msh) as part of the Linux Internal module.
*/

#include"main.h"

int check_command_type(char *command)
{
       //List of builtin commands
       char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval","set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source", "exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", NULL};  
       
       //to check whether enter key is pressed
       if(strcmp(command, "\0") == 0)
       {
	      return NO_COMMAND;
       }
       
       //check whether the command is internal
       for(int i = 0; builtins[i] != NULL; i++)
       {
	      if(strcmp(command, builtins[i]) == 0)
	      {
		     return BUILTIN;
	      }
       }
       
       //to extract external commands
       char *external_commands[155] = {NULL};
       extract_external_commands(external_commands);
       for(int i = 0; external_commands[i] != NULL; i++)
       {
	      if(strcmp(command, external_commands[i]) == 0)
	      {
		     return EXTERNAL;
	      }
       }
}
