
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "element_thread.h"
#define TYPE float
typedef struct Parameters  //paramters passed to the function
{


    int rowsA,rowsB,colsA,colsB;

    TYPE ** matrixA ;
    TYPE ** matrixB;
    TYPE ** matrixC ;


} Parameters;

struct element
{ //struct for carrying the data of each element
      int row;
      int column;
      Parameters* par;
      
};

void create_Parameters(Parameters*p , TYPE** matrix1,TYPE** matrix2,TYPE**matrix3,int rows1,int cols1,int rows2, int cols2)
{
    p->matrixA=matrix1;
    p->matrixB=matrix2;
    p->matrixC=matrix3;
    p->rowsA=rows1;
    p->colsA=cols1;
    p->rowsB=rows2;
    p->colsB=cols2;

    return;
}


//printing the resulting matrix C
void print_resulting_matrix(TYPE ** matrixC,int rowsC,int colsC)
{     TYPE ** result_matrix=matrixC;
      int i, j;
      for (i = 0; i < rowsC; i++)
      {
            for (j = 0; j < colsC; j++)
            {
                  printf("%f ", result_matrix[i][j]);
            }
            printf("\n");
      }
}
void calculate_matrix_without_thread(TYPE ** matrixA, TYPE** matrixB,TYPE** matrixC,int rowsA,int colsA, int colsB)
{
      int i, j, p;
      float result = 0;
      for (i = 0; i < rowsA; i++)
      {
            for (j = 0; j < colsB; j++)
            {
                  result = 0;
                  for (p = 0; p < colsA; p++)
                  {
                        result = result +(matrixA[i][p]*matrixB[p][j]);
                  }
                  matrixC[i][j] = result;
            }
      }
}

//function for calculating the multiplication of two matrices by creating a thread for each element.
void calculate_matrix_by_element(TYPE ** matrixA, TYPE** matrixB, TYPE **matrixC,int rowsA,int colsA,int rowsB, int colsB,int *count )
{
      Parameters * p = (Parameters*)malloc(sizeof(Parameters)); //allocates memory for Parameters
      create_Parameters(p,matrixA,matrixB,matrixC,rowsA,colsA,rowsB,colsB); //initializes p with parameters given to function
      int i, j,cnt=0;
      pthread_t threads[1000000];
      //loop for assigning a thread to each and every element that will be calculated in the new matrix
      int k=0;
      for (i = 0; i < p->rowsA; i++)
      {
            for (j = 0; j < p->colsB; j++)
            {
                  struct element *data = (struct element *)malloc(sizeof(struct element));
                  data->row = i;
                  data->column = j;
                  data->par=p;
                  cnt++;
                  threads[k] = create_thread_per_element(data);
                  
                  
            }
      }
      for (j = 0; j < k+1; j++)
      {
            pthread_join(threads[j], NULL);
      }
      free(p);
      *count=cnt;
}

//function for calculating the value of element.
void *calculate_element(void *element)
{    
      struct element *el = element;
      Parameters *parameter= el->par;
      int i;
      
      int column_row = parameter->rowsB;
      ///number of rows in the column.
      float sum = 0;  
      //variable for storing the value of the specified element in the resulting matrix.
      for (i = 0; i < column_row; i++)
      {    
            sum = sum + (parameter->matrixA[el->row][i] * parameter->matrixB[i][el->column]);
      }
      parameter->matrixC[el->row][el->column] = sum;
     
      
      pthread_exit(0);
     
}

//function for creating the thread needed for the element evaluation.
pthread_t create_thread_per_element(struct element *el)
{     
      pthread_t tid; //thread id
      pthread_attr_t attr;
      pthread_attr_init(&attr);                           //get default attributes
      pthread_create(&tid, &attr, calculate_element, el); //create the thread
      return tid;

}
