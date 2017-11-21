
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define M 2
#define K 2
#define N 1

struct element
{ //struct for carrying the data of each element
      int row;
      int column;
      
};

float matrixA[M][K] = {{1, 4}, {1, 1}}; //hardcoded matrices for trail.
float matrixB[K][N] = {{3}, {4}};
float matrixC[M][N];
int matrixB_rows = K;

void *calculate_element(void *element); //prototypes for the used functions.
pthread_t create_thread_per_element(struct element *el);
void calculate_matrix_by_element();
void print_resulting_matrix();
void calculate_matrix_without_thread();
int main()
{

      calculate_matrix_by_element();
      print_resulting_matrix();
      calculate_matrix_without_thread();
      print_resulting_matrix();

      return 0;
}
//printing the resulting matrix C
void print_resulting_matrix()
{
      int i, j;
      for (i = 0; i < M; i++)
      {
            for (j = 0; j < N; j++)
            {
                  printf("%f ", matrixC[i][j]);
            }
            printf("\n");
      }
}
void calculate_matrix_without_thread()
{
      int i, j, p;
      float result = 0;
      for (i = 0; i < M; i++)
      {
            for (j = 0; j < N; j++)
            {
                  result = 0;
                  for (p = 0; p < K; p++)
                  {
                        result = result +(matrixA[i][p]*matrixB[p][j]);
                  }
                  matrixC[i][j] = result;
            }
      }
}
//function for calculating the multiplication of two matrices by creating a thread for each element.
void calculate_matrix_by_element()
{
      int i, j;
      pthread_t threads[100];
      //loop for assigning a thread to each and every element that will be calculated in the new matrix

      for (i = 0; i < M; i++)
      {
            for (j = 0; j < N; j++)
            {
                  struct element *data = (struct element *)malloc(sizeof(struct element));
                  data->row = i;
                  data->column = j;
                  threads[i] = create_thread_per_element(data);
            }
      }
      for (j = 0; j < N; j++)
      {
            pthread_join(threads[j], NULL);
      }
}

//function for calculating the value of element.
void *calculate_element(void *element)
{
      struct element *el = element;
      int i;
      int column_row = matrixB_rows; ///number of rows in the column.
      float sum = 0;                 //variable for storing the value of the specified element in the resulting matrix.
      for (i = 0; i < column_row; i++)
      {
            sum = sum + (matrixA[el->row][i] * matrixB[i][el->column]);
      }
      matrixC[el->row][el->column] = sum;
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
      //pthread_join(tid,NULL); //wait for the thread to end.
}
