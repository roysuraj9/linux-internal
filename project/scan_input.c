/*
Name : Suraj Roy
Date 16/01/2023
Description : Implement a minimalistic shell, mini-shell(msh) as part of the Linux Internal module.
*/

#include"main.h"
pid_t pid;
void scan_input(char *prompt, char *input_string)
{
       //variable declaration
       char *command = '\0';
       int command_type, status;

       while(1)
       {
	      memset(input_string, '\0', 25);
	      printf(ANSI_COLOR_RED"[%s]$:"ANSI_COLOR_RESET,prompt);
	      //clear the output buffer
	      fflush(stdout);

	      scanf("%[^\n]s",input_string);
	      //clear the input buffer
	      getchar();

	      //Customize the prompt
	      if(!(strncmp("PSI=", input_string, 4)))
	      {
		     if(input_string[4] != ' ')
		     {
			    strcpy(prompt,&input_string[4]);
			    //clear the input string
			    memset(input_string,'\0',25);
			    continue;
		     }
		     printf("Command not found\n");
	      }
	      //To get the command 
	      command = get_command(input_string);
	      //printf("command is %s\n", command);
	      //check whether the command is internal or external
	      command_type = check_command_type(command);
	      //printf("command_type is %d\n", command_type);
	      if(command_type == EXTERNAL)
	      {
		     pid = fork();
		     if(pid == 0)
		     {
			    //child process
			    system(input_string);
			    exit(0);
		     }
		     else if(pid > 0)
		     {
			    //Parent
			    wait(&status);
			    if(WIFEXITED(status))
			    {
				   printf("Child with pid %d terminated normally\n", pid);
			    }
		     }
		     else
		     {
			    printf("fork failed\n");
			    exit(1);
		     }
	      }
	      //call the function to implement echo commands
	      echo(input_string, status);
	      //Internal_commands
	      execute_internal_commands(input_string);
       }

}
