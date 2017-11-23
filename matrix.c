
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define M 2
#define K 2
#define N 1
#define TYPE int
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



void *calculate_element(void *element); //prototypes for the used functions.
pthread_t create_thread_per_element(struct element *el);
void print_resulting_matrix(TYPE ** matrixC);
void calculate_matrix_by_element(TYPE ** matrixA, TYPE** matrixB, TYPE **matrixC,int rowsA,int colsA,int rowsB, int colsB );

//void calculate_matrix_without_thread();
int main()
{   int i=0;
        int** matrixA = (int**)malloc(M*sizeof(int *));
for(i=0; i<M ;i++)
{
    matrixA[i]=(int *)malloc(K*sizeof(int));
}


        int** matrixB = (int**)malloc(K*sizeof(int *));
for(i=0; i<K ;i++)
{
    matrixB[i]=(int *)malloc(N*sizeof(int));
}

int** matrixC = (int**)malloc(M*sizeof(int *));
for(i=0; i<M ;i++)
{
    matrixC[i]=(int *)malloc(K*sizeof(int));
}
      //TYPE matrixA[M][K] = {{1, 4}, {1, 1}}; //hardcoded matrices for trail.
      //TYPE matrixB[K][N] = {{3}, {4}};
      //TYPE matrixC[M][N];

        matrixA[0][0]=1;
        matrixA[0][1]=4;
        matrixA[1][0]=1;
        matrixA[1][1]=1;

        matrixB[0][0]=3;
        matrixB[1][0]=4;
       
        matrixC[0][0]=0;
        matrixC[1][0]=0;
        
      int matrixB_rows = K;
      calculate_matrix_by_element(matrixA,matrixB,matrixC,M,K,K,N);
      print_resulting_matrix(matrixC);

      //calculate_matrix_without_thread();
      //print_resulting_matrix();

      return 0;
}


//printing the resulting matrix C
void print_resulting_matrix(TYPE ** matrixC)
{     TYPE ** result_matrix=matrixC;
      int i, j;
      for (i = 0; i < M; i++)
      {
            for (j = 0; j < N; j++)
            {
                  printf("%d ", result_matrix[i][j]);
            }
            printf("\n");
      }
}
/*void calculate_matrix_without_thread()
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
*/
//function for calculating the multiplication of two matrices by creating a thread for each element.
void calculate_matrix_by_element(TYPE ** matrixA, TYPE** matrixB, TYPE **matrixC,int rowsA,int colsA,int rowsB, int colsB )
{
      Parameters * p = (Parameters*)malloc(sizeof(Parameters)); //allocates memory for Parameters
      create_Parameters(p,matrixA,matrixB,matrixC,rowsA,colsA,rowsB,colsB); //initializes p with parameters given to function
      int i, j;
      pthread_t threads[100];
      //loop for assigning a thread to each and every element that will be calculated in the new matrix

      for (i = 0; i < p->rowsA; i++)
      {
            for (j = 0; j < p->colsB; j++)
            {
                  struct element *data = (struct element *)malloc(sizeof(struct element));
                  data->row = i;
                  data->column = j;
                  data->par=p;
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
