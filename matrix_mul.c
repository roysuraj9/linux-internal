/*
Name : Suraj Roy
Date : 20/01/2023
Description : WAP to multiply two matrices using multiple threads
Sample Input :
Enter M1 rows and columns
3 3
enter M2 rows and columns
3 3
Enter M1 values
1 2 3 1 2 3 1 2 3
Enter M2 values
1 2 3 1 2 3 1 2 3

Sample Output :
result is
   6  12  18
   6  12  18
   6  12  18


*/
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int allocated_mat(int ***matrix, short row, short col);

typedef struct thread_data
{
       short m1_row;
       short m1_col;
       short m2_col;
       int **matrix1;
       int **matrix2;
       int **result;
       short cur_row;
}thread_data_t;

thread_data_t mul;

//thread function
void *thread(void *ptr)
{
       int i = mul.cur_row;
       mul.cur_row++;
       for(int j = 0; j < mul.m2_col; j++)
       {
	      mul.result[i][j] = 0;
      
	      for(int k = 0; k < mul.m1_col; k++)
	      {
		     mul.result[i][j] += mul.matrix1[i][k] * mul.matrix2[k][j];
	      }
       }
}

int main()
{
       int i, j;
       short m2_row;
       
       //prompting the user to enter
       printf("Enter M1 rows and columns\n");
       scanf("%hd %hd", &mul.m1_row, &mul.m1_col);

       printf("enter M2 rows and columns\n");
       scanf("%hd %hd", &m2_row, &mul.m2_col);

       if(mul.m1_col != m2_row)
       {
	      printf("failure\n");
	      return 0 ;
       }
       
       //allocate the memory dynamically for matrix
       allocated_mat(&mul.matrix1, mul.m1_row, mul.m1_col);
       allocated_mat(&mul.matrix2, mul.m1_col, mul.m2_col);
       allocated_mat(&mul.result, mul.m1_row, mul.m2_col);

       //enter element in matrix1 from user
       printf("Enter M1 values\n");
       for(i = 0; i < mul.m1_row; i++)
       {
	      for(j = 0; j < mul.m1_col; j++)
	      {
		     scanf("%d", &(mul.matrix1[i][j]));
	      }
       }

       //enter element in matrix2
       printf("Enter M2 values\n");
       for(i = 0; i < mul.m1_col; i++)
       {
	      for(j = 0; j < mul.m2_col; j++)
	      {
		     scanf("%d", &(mul.matrix2[i][j]));
	      }
       }

       //number of threads to create
       pthread_t tid[mul.m1_row];

       /* Create thread one */
       for(i = 0; i < mul.m1_row; i++)
       {
	      if ((errno = pthread_create(&tid[i], NULL, thread, NULL )) !=     0)
	      {
		     perror("pthread_create()");
		     exit(1);
	      }
       }

       for(i = 0; i < mul.m1_row ; i++)
       {
	      pthread_join(tid[i], NULL);
       }

       printf("\nresult is\n");
       //logic for printing matrix
       for(i = 0; i < mul.m1_row; i++)
       {
	      for(j = 0; j < mul.m2_col; j++)
	      {
		     printf("%3d", mul.result[i][j]);
	      }
 	      printf("\n");
       }
}
int allocated_mat(int ***matrix, short row, short col)
{

       int **mat = malloc(row  *  sizeof(int *));
       for(int i = 0; i < col; i++)
       {
	      *(mat + i) = malloc(col * sizeof(int *));
       }
       *matrix = mat;
}
