/*
Name : Suraj Roy
Date 16/01/2023
Description :  WAP to avoid child become zombie by using signal handlers
Sample Input : ./a.out 22:44
Sample output :
Alarm set to 22:44 hrs for today
Wake up..Alarm..!!
Select
1. Snooze 
2. Quit
*/

#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int alarm_flag;

void handler(int signum)
{
       //check if SIGALRM is happened
       alarm_flag = 1;
}

int main(int argc, char *argv[])
{
       //check whether user passed input or not
       if(argc < 2)
       {
	      printf("Error: No arguments passed\nUsage: ./alarm  [dd/mm/yy]\n");
	      return 0;
       }
       //getting current time
       time_t cur_time = time(NULL);
       //declare variable
       int  alarm_time, choice, snooze;
       struct tm *time, user_time;
       
       //clear user_time
       memset(&user_time, 0, sizeof(user_time));

       //when time only passed
       if(argc == 2)
       {
	      printf("Alarm set to %s hrs for today\n", argv[1]);
	      time = localtime(&cur_time);

	      strptime(argv[1], "%H:%M%S", &user_time);
	      //getting information of day ,month, year
	      user_time.tm_mday = time -> tm_mday;
	      user_time.tm_mon = time -> tm_mon;
	      user_time.tm_year = time -> tm_year;
       }
       //if complete data is passed along with time
       else
       {
	      printf("Alarm set to %s hrs for %s\n", argv[1], argv[2]);
	      strptime(argv[1], "%H:%M:%S", &user_time);
	      strptime(argv[2], "%Y:%m:%d", &user_time);
       }
       //finding the user time
       alarm_time = mktime(&user_time);

       //check alarm time is smaller than current time then fail
       if(alarm_time < cur_time)
       {
	      printf("Error: Invalid time \n");
	      return 0;
       }
       
       alarm_time = alarm_time - cur_time;
       
       //register SIGALRM signal
       signal(SIGALRM, handler);
       alarm(alarm_time);

       //on alarm time
       while(1)
       {
	      if(alarm_flag)
	      {
		     alarm_flag =0;

		     //ask user to snooze or exit
		     printf("Wake up..Alarm..!!\n1. Snooze \n2. Quit\noption\n");
		     scanf("%d", &choice);
		     switch(choice)
		     {
			    case 1:
				   printf("Enter Snooze time (in seconds) : ");
				   scanf("%d", &snooze);
				   signal(SIGALRM, handler);
				   alarm(snooze);
				   break;
			    case 2:
       				   exit(1);
       				   break;
		     }
	      }
       }
}
