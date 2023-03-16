/*
Name : Suraj Roy
Date 14/01/2023
Description : Implement communication between three processes using PIPE, FIFO and SHM
Sample Input : ./receiver 
Sample output : 
Reading from Shared memory...
String scanned from SHM - KING
 */

#include "main.h"

int main()
{
       int shmid, len;
       char *shm, temp, buffer[50], *myfifo = "myfifo";
       //use the same key as in writer
       key_t key = 'S';
    
       shmid = shmget(key, SHMSIZE, 0);
       if(shmid < 0)
       {
      	      printf("ERROR : Shared memory not created, Execute 150 first\n");
      	      return 0;
       }
       else
       {
    
      	      //attach to shared memory
      	      shm = shmat(shmid, NULL, 0);

      	      printf("Reading from Shared memory...\n");
	      sscanf(shm, "%s", buffer);
	      printf("String scanned from SHM - %s\n", buffer);
	      shmdt(NULL);
	      
	      // delete the shared memory 
	      shmctl(shmid, IPC_RMID, NULL);
       }
       
       // reverse the string 
       len = strlen(buffer);
       for(int i = 0; i < len / 2;i++)
       {
      	      temp = buffer[i];
      	      buffer[i] = buffer[len - 1 - i];
      	      buffer[len - 1 - i] = temp;
       }

       // store the string in the FIFO 
       mkfifo(myfifo, 0666);
       //open the file in writemod
       int fd = open(myfifo, O_WRONLY);
       write(fd, buffer, strlen(buffer) + 1);
    
       close(fd);
       return 0;
}
