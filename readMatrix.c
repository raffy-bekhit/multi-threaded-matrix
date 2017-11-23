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
    free(t);
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
         char * token2 ;     
    char * position = buffer;
    char* position2=buffer;

    int column_c=0; //number of columns present in this turn
    //if(row_c>1) column_c=column_num;

    TYPE * temp_row;
     TYPE * row = malloc(100*sizeof(TYPE)); // allocates memory for the row
int i=0;
 while( token = (char *)strtok_r(position,splitter,&position) )
    {
       // if(!isnumber(token))
        //error  =-1;  //-1 indicates that non-digit character is present in matrix
      //  puts(token);
       // printf("%f\n",*(temp_row+column_c));
       // *(temp_row+column_c)=atof(token);x
        //temp_row++;
        // printf("this is the number of columns %d\n",column_c);

        row[i]=atof(token);
        printf("this is the token %f\n",row[i]);
        i++;
        column_c++;
    }
    column_c ++;


   // if(row_c>1&&(column_c!=column_num))
    //error = -2; //indicates that colums aren't equal in the same matrix

   //TYPE * row = malloc(column_c*sizeof(TYPE)); // allocates memory for the row
  // row = temp_row;

   return row;

}
