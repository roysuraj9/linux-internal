/*
Name : Suraj Roy
Date 14/01/2023
Description : Implement communication between two different processes using SHM
Sample Input : ./receiver 
Sample output : 
Reading from shared memory : GOHAN
Writing to Shared memory ...
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
       char *shm, *p, *q, temp;
       key_t key;

       // Use the same key as in writer 
       key = 'B';

       // Get the shared memory, creation is already done 
       shmid = shmget(key,SMSIZE, 0664);
       if (shmid < 0)
       {
	      perror("shmget");
      	      exit(1);
       }

       // Attach to shared memory 
       shm = shmat(shmid,NULL,0);
       if (shm < 0)
       {
      	      perror("shmat");
      	      exit(0);
       }

       printf("Reading from shared memory : %s\n", shm);
	
       //reverse string
       p = shm;
       q = shm;
       while(*p)
       {	
	      p++;
       }
       p--;
       while(q < p)
       {
	      temp = *q;
	      *q = *p;
	      *p = temp;
	      q++;
	      p--;
       }
	
       printf("Writing to Shared memory ...\n");

       //Detach from shm
       shmdt(shm);
       //Remove shared memory
       shmctl(shmid,IPC_RMID,NULL);
}
