#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include "readMatrix.h"
#define TYPE float
int error;


int is_number(char* string) //check if string contains an alphabet
{
    int i=0;
    while(i<strlen(string))
    {
        if(!isdigit(string[i++]))
        return 0 ;
    }

    return 1;
}

TYPE* split_elements(char* buffer,int*cols) //returns number of columns or error number // column_num is number of columns already counted from previous turns
{      
    char splitter[]={'\t','\n',' '}; //used in strtok_r function
    char * token ;    
    char * position ;
    position=buffer;
  
    
   

    int column_c=0; //number of columns present in this turn
    
    int size = sizeof(TYPE);
   TYPE* row = (TYPE*) malloc(size);
     // allocates memory for the row

while( token = (char *)strtok_r(position,splitter,&position) )
    {
        row = (TYPE*) realloc(row,size);
    
       row[column_c] = atof(token);
       size+=sizeof(TYPE);
        column_c++;
    }
   *cols=column_c;
   
   return row;

}
TYPE ** read_matrix(char*filename,int*cols,int*rows){
    int no_of_rows;
   FILE *file;
char *line = NULL;
size_t len = 0;
char read;
file=fopen(filename, "r");
(no_of_rows) =0;
if (file == NULL)
    perror("The following error occured");

    int size2 = sizeof(TYPE*);
    int size3= sizeof(TYPE);
    int j;
     TYPE** matrixA=(TYPE **)malloc(sizeof(TYPE*));
while ((read = getline(&line, &len, file)) != -1) {
   
   matrixA=realloc(matrixA,size2);
     matrixA[no_of_rows]=(TYPE*)malloc(size3);
    TYPE*t=split_elements(line,cols);
   for(j=0;j<*cols;j++)
    {
        matrixA[no_of_rows]=(TYPE*)realloc(matrixA[no_of_rows],size3);
        matrixA[no_of_rows][j]=t[j];
  //      printf("%f  ",t[j]);
        size3+=sizeof(TYPE);
    }
    no_of_rows ++;
    size2+=sizeof(TYPE*);
//    printf("\n");
   // free(t);
 
}
*rows=no_of_rows;

if (line)
    free(line);

fclose(file);

return matrixA;

}
void write_matrix(char*location,TYPE**matrix,int rows,int cols)
{
    FILE*file = fopen(location,"w");
    if(file ==NULL) perror("the following error occured");
    for (int row = 0; row < rows; row++)
    {   
        for (int col = 0; col < cols; col++)
        {
      fprintf(file, "%f ",matrix[row][col]);
              
      }
      fprintf(file, "\n");

    }
fclose(file);
}