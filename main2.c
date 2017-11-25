#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "readMatrix.h"
#include "element_thread.h"
#include "row_threaded_matrix.h"
#include <time.h>
#define TYPE float
int main (int argc, char ** argv)
{    //if the two file names aren't given return
     if(argc <3)
    {
        puts("Missing parameters");
        return 1;
    }
    clock_t start, end;
    double cpu_time_used1,cpu_time_used2,cpu_time_used3;
    int colsA=0, colsB=0,rowsB=0,rowsA=0;
    int i,count=0;
    //read Matrix A
    TYPE ** matrixA= read_matrix(argv[1],&colsA,&rowsA);
    

    printf("Matrix1 has %d columns and  %d rows \n",colsA,rowsA);
    //read Matrix B
    TYPE ** matrixB= read_matrix(argv[2],&colsB,&rowsB);
    printf("Matrix2 has %d columns and %d rows \n ",colsB,rowsB);
    



if(colsA!=rowsB) {
printf("rows of first matrix doesn't equal columns of second one!\n");
  return -99;}

    //create MatrixC
    TYPE** matrixC = (TYPE**)malloc(rowsA*sizeof(TYPE *));
for(i=0; i<rowsA ;i++)
{
    matrixC[i]=(TYPE*)malloc(colsB*sizeof(TYPE));
}

      //create matrix multiplication by threads
     start = clock();
      calculate_matrix_by_element(matrixA,matrixB,matrixC,rowsA,colsA,rowsB,colsB,&count);
     end= clock();
     cpu_time_used1 = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%d per element threads were created.\n",count);
      ///create matrix multiplication by without threads
     start = clock();
    calculate_matrix_without_thread(matrixA, matrixB, matrixC,rowsA,colsA, colsB);
     end = clock();
    
      cpu_time_used2 = ((double) (end - start)) / CLOCKS_PER_SEC;
      //print resulting matrix C
     // print_resulting_matrix(matrixC,rowsA,colsB);

    start = clock();
      row_threaded_marix_mult( matrixA,matrixB,matrixC,rowsA,colsA,rowsB,colsB,&count);
     end= clock();
     cpu_time_used3 = ((double) (end - start)) / CLOCKS_PER_SEC;
     

    printf("%d per row threads were created.\n",count);

      //print the execution time.
    printf(" row ethreaded time = %lf , element ethreaded time = %lf and non threaded = %lf\n",cpu_time_used3,cpu_time_used1,cpu_time_used2);
    
write_matrix(argv[3],matrixC,rowsA,colsB);

    free(matrixA);
free(matrixB);
free(matrixC);

    return 0;
}
