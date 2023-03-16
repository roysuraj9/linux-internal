/*
Name : Suraj Roy
Date 14/01/2023
Description : Implement communication between two different processes using SHM
Sample Input : ./sender 
Sample output : 
Enter a string :gohan
Writing to Shared memory ...
Reading from shared memory NAHOG
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <ctype.h>
#define SMSIZE 100

int main()
{
       int shmid;
       char *shm, *p;
       key_t key;

       // Key can be hardcoded, but use the same in reader & writer 
       key = 'B';
	
       // Create a shared memory 
       shmid = shmget(key, SMSIZE, IPC_CREAT | 0664);
       if (shmid < 0)
       {
	      perror("shmget");
	      exit(1);
       }

       // Attach to shared memory 
       shm = shmat(shmid, NULL, 0);
       if (shm < 0)
       {
	      perror("shmat");
	      exit(0);
       }
	
       //take input from user
       printf("Enter a string :");
       scanf("%s", shm);
	
       //converting lowercase to uppercase
       p = shm;
       while(*p)
       {
	      *p = toupper(*p);	
	      p++;
       }
       printf("Writing to Shared memory ...\n");
       sleep(6);
       printf("Reading from shared memory %s\n", shm);
	
       //Detach from shm
       shmdt(shm);
}
