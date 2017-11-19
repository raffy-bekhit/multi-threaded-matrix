#include "matrix.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define M 2
#define K 2
#define N 1

struct element{     //struct for carrying the data of each element
int row;
int column;
};
int matrixA[M][K]={{1,4}, {1,1}};   //hardcoded matrices for trail.
int matrixB[K][N]={{3},{4}};
int matrixC[M][N];
int matrixB_rows=K;

void* calculate_element(void* element);                        //prototypes for the used functions.
void create_thread_per_element(struct element * el);


int main(){
int i,j;                                               //loop for assigning a thread to each and every element that will be calculated in the new matrix
for(i = 0; i < M; i++) {
      for(j = 0; j < N; j++) {
struct element *data = (struct element *) malloc(sizeof(struct element));
data->row= i;
data->column=j;
create_thread_per_element(data);
                             }
                        }



 //Print out the resulting matrix
   for(i = 0; i < M; i++) {
      for(j = 0; j < N; j++) {
         printf("%d ", matrixC[i][j]);
      }
      printf("\n");
   }


return 0;

}

//function for calculating the value of element.
void* calculate_element(void* element)
{
struct element *el = element;
int i;                         
int column_row= matrixB_rows; ///number of rows in the column.
int sum=0;                  //variable for storing the value of the specified element in the resulting matrix.
for(i=0;i< column_row;i++)
{
 sum=sum + (matrixA[el->row][i] * matrixB[i][el->column]);
}
matrixC[el->row][el->column]=sum;
pthread_exit(0);

}

//function for creating the thread needed for the element evaluation.
void create_thread_per_element(struct element * el)
{
pthread_t tid;     //thread id
pthread_attr_t attr;
pthread_attr_init(&attr);    //get default attributes
pthread_create(&tid,&attr,calculate_element,el); //create the thread
pthread_join(tid,NULL); //wait for the thread to end.

}
