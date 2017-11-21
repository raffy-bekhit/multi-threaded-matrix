
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define M 2
#define K 2
#define N 1

#define TYPE int


int matrixA[M][K]= {{1,4}, {1,1}};  //hardcoded matrices for trail.
int matrixB[K][N]= {{3},{4}};
int matrixC[M][N];
int matrixB_rows=K;
int matrixB_columns = N;

void* calculate_row(int* );                        //prototypes for the used functions.


int main()
{

    int i,j;                                               //loop for assigning a thread to each and every element that will be calculated in the new matrix
    int error_flag;
    pthread_t threads_array[M];
    pthread_attr_t attr_array[M];
    int rows[M];


    for(i = 0; i < M; i++)
    {
        rows[i]=i;

        pthread_attr_init(&attr_array[i]);    //get default attributes
        error_flag = pthread_create(&threads_array[i],&attr_array[i],calculate_row,&rows[i]); //create the

        if(error_flag!=0)
        {
            printf("error in thread: %d\n",error_flag);
            return -1;
        }
    }

    for(i = 0; i < M; i++)
    {
      int temp =   pthread_join(threads_array[i],NULL);
    }





//Print out the resulting matrix
    for(i = 0; i < M; i++)
    {
        for(j = 0; j < N; j++)
        {
            printf("%d ", matrixC[i][j]);
        }
        printf("\n");
    }


    return 0;

}

//function for calculating the value of element.
void* calculate_row(int* row)
{

    int i,j; //variables used in loops

    int sum=0; //temporary variable to hold the value of the calculated element


    for(i=0; i< matrixB_columns; i++) //loops the columns of matrixB
    {

        for(j=0; j< matrixB_rows; j++) //loops rows of matrixB //loops columns of matrixA for a specific row
        {
            sum = sum + (matrixA[*row][j] * matrixB[j][i]);
        }
        matrixC[*row][i]=sum;
        sum=0;
    }

    pthread_exit(0);

}


