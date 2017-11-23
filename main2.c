#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "readMatrix.h"
#include "element_thread.h"
#define TYPE float
int main (int argc, char ** argv)
{   int colsA=0;
    int rowsA=0;
    int i;
    TYPE ** matrixA= read_matrix(argv[1],&colsA,&rowsA);
    printf("%d columns and  %d rows \n",colsA,rowsA);
    
     int colsB=0;
    int rowsB=0;
    TYPE ** matrixB= read_matrix(argv[2],&colsB,&rowsB);
    printf("%d columns and %d rows\n ",colsB,rowsB);
    
    //create matrixC
    TYPE** matrixC = (TYPE**)malloc(rowsA*sizeof(TYPE *));
for(i=0; i<rowsA ;i++)
{
    matrixC[i]=(TYPE*)malloc(colsB*sizeof(TYPE));
}
    
    calculate_matrix_by_element(matrixA,matrixB,matrixC,rowsA,colsA,rowsB,colsB);
    print_resulting_matrix(matrixC,rowsA,colsB);
    
    
    return 0;
}
