#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "readMatrix.h"
#define TYPE float
int main (int argc, char ** argv)
{   int cols=0;
    int rows=0;
    TYPE ** matrixA= read_matrix(argv[1],&cols,&rows);
    printf("%d columns and  %d rows \n",cols,rows);
    
     int cols2=0;
    int rows2=0;
    TYPE ** matrixB= read_matrix(argv[2],&cols2,&rows2);
    printf("%d columns and %d rows ",cols2,rows2);
    return 0;
}
