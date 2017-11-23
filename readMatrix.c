#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#define TYPE float
int error;
TYPE* split_elements(char* buffer);
int is_number(char* string);
int main()
{
    int no_of_rows;
   FILE *file;
char *line = NULL;
size_t len = 0;
char read;
file=fopen("Matrix1.txt", "r");
(no_of_rows) =0;
if (file == NULL)
    return 1;

  
    
while ((read = getline(&line, &len, file)) != -1) {
   int j=0;
    no_of_rows ++;
  //  printf("%s", line);
    TYPE*t=split_elements(line);
     
   for(j=0;j<4;j++)
    {
        printf("%f    ",*t);
    }
printf("\n");
}
printf("this is the number of rows \n %d",no_of_rows);
if (line)
    free(line);

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
    char * position = buffer;

    int column_c=0; //number of columns present in this turn
    //if(row_c>1) column_c=column_num;

    TYPE * temp_row;



    while( token = (char *)strtok_r(position,splitter,&position) )
    {
       // if(!isnumber(token))
        //error  =-1;  //-1 indicates that non-digit character is present in matrix
      //  puts(token);
       // printf("%f\n",*(temp_row+column_c));
        *(temp_row+column_c)=atof(token);
        
        //temp_row++;
        column_c++;
    }

   // if(row_c>1&&(column_c!=column_num))
    //error = -2; //indicates that colums aren't equal in the same matrix

   TYPE * row = malloc(column_c*sizeof(TYPE)); // allocates memory for the row
   row = temp_row;

   return row;

}
