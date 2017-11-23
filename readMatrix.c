#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#define TYPE float
int error;
TYPE* split_elements(char* buffer);
int is_number(char* string);
void read_matrix(char*filename){
    int no_of_rows;
   FILE *file;
char *line = NULL;
size_t len = 0;
char read;
file=fopen(filename, "r");
(no_of_rows) =0;
if (file == NULL)
    return 1;

   
    
while ((read = getline(&line, &len, file)) != -1) {
   
   
    int j=0;
    no_of_rows ++;
   



    TYPE*t=split_elements(line);
    
   for(j=0;j<4;j++)
    {
        printf("%f  ",t[j]);
    }
    printf("\n");
   // free(t);
 
}


printf("this is the number of rows  %d",no_of_rows);
if (line)
    free(line);



}
int main(int argc, char** argv)
{
    read_matrix(argv[1]);

return 0;
}
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

TYPE* split_elements(char* buffer) //returns number of columns or error number // column_num is number of columns already counted from previous turns
{      
    char splitter[]={'\t','\n',' '}; //used in strtok_r function
    char * token ;    
    char * position ;
    position=buffer;
  
    
   

    int column_c=0; //number of columns present in this turn
    //if(row_c>1) column_c=column_num;

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
   

   // if(row_c>1&&(column_c!=column_num))
    //error = -2; //indicates that colums aren't equal in the same matrix

   //TYPE * row = malloc(column_c*sizeof(TYPE)); // allocates memory for the row
  // row = temp_row;

   return row;

}
