/*
Name : Suraj Roy
Date 20/01/2023
Description : WAP to sum and maximum of a given array using multiple threads.Synchronize threads using mutex.
Sample Input : Enter the size of array :90
Sample Output : max = 90  sum = 4095
*/

#include<stdio.h>
#include<pthread.h>
#include<string.h>

/* structure */
typedef struct
{
	int val;
	int limit;
        int *arr;
}sum_t;

pthread_mutex_t lock;

//declare global variable
int global_sum, global_max;

/* function read by thread to calculate parital factorial */
void *sum_max(void *param)
{
       /* void pointer to required pointer type */
       sum_t *data = param;
       int i;
	
       //acquire the lock before entering CS
       pthread_mutex_lock(&lock);

       /* loop to iterate through values */
       for(i = 0; i < data -> limit; i++)
       {
	      global_sum += (data -> val) - i;
	      
	      //finding max value
	      if(global_max < data -> val)
	      {
     		     global_max = data -> val;
	      }	
       }
       //Unlock so that other threads can access CS
       pthread_mutex_unlock(&lock);

       return NULL;
}

int main()
{
       //declaration
       int val, i, arr[500];
       //read user input
       printf("Enter the size of array :");
       scanf("%d",&val);
       if(val < 0)
       {
	      printf("Error: Enter positive number\n");
	      return 0;
       }
       //enter element in array to user enter value
       for(int i = 0 ; i < val; i++)
       {
	      arr[i] = i + 1;
       }
		
       //thread count
       int count = 5; 
       //array of thread ids
       pthread_t tid[count];  
       //array of structures
       sum_t data[count];   
       //clearing the structure array
       memset(&data, 0, sizeof(data)); 
       memset(&arr, 1, sizeof(arr));
	
       /* loop to run multiple threads */
       for(i = 0; i < count; i++)
       {
	      /* initializing the structure to passed as an argument to the function */
	      data[i].arr = &arr[i];
	      data[i].val = val - i * count;
	      
	      /* conditions for getting limit */
	      //last thread and excess values
	      if(i == count - 1 && data[i].val > count)   
	      {
     		     data[i].limit = data[i].val;
	      }
      
	      //value less than or equal to 0
	      else if(i <= count - 1 && data[i].val <= 0) 
	      {
		     data[i].limit = 0;
	      }
      
	      //value less than count
	      else if(i <= count - 1 && data[i].val < count) 
	      {
		     data[i].limit = val % count;
	      }
      	      else
	      {	
		     data[i].limit = count;
	      }
      	      /* creating a thread which will execute the sum_max function */
	      pthread_create(&tid[i], NULL, sum_max, &data[i]);
       }
	
       /* loop for main thread to wait for other threads */
       for(i = 0; i < count; i++)
       {
	      pthread_join(tid[i],NULL);
       }

       /* display output */
       printf("max = %d  sum = %d\n", global_max, global_sum);
       return 0;
}
