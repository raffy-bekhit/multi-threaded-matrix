#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



int error = 0;


int * split_elements(char* buffer,int row_c,int column_num);
int *** read_file(char* location);
int is_number(char* string) ;
int is_empty(char*string);


int is_empty(char*string)
{
    char splitters[] = {'\t','\n',' ','\0'};
    if(!strcmp(strtok(string,splitters)," ")||!strcmp(strtok(string,splitters),"")) return 1;
}

int * split_elements(char* buffer,int row_c,int column_num) //returns number of columns // column_num is number of columns already counted from previous turns
{
    char splitters[]= {'\t','\n',' '}; //used in strtok_r function
    char * token ;
    char * position = buffer;

    int column_c=0; //number of columns present in this turn
    if(row_c>1) column_c=column_num;

    int * temp_row;



    while( token = strtok_r(position,splitters,&position) )
    {

        if(!is_number(token))
            error  =-1;  //-1 indicates that non-digit character is present in matrix
        *temp_row++=atoi(token);
        column_c++;

    }


    if(row_c>1&&(column_c!=column_num))
        error = -2; //indicates that colums aren't equal in the same matrix

    int * row = malloc(sizeof(column_c*sizeof(int))); // allocates memory for the row
    row = temp_row;

    return row;

}


int *** read_file(char* location ) //function to read matrices from given file
{
    FILE* file =  fopen(location,"r");
    char line_buffer[100]; //buffer for reading line
    int temp_row_c=0; // counter that counts the rows
    int temp_column_c=0; //cpunts the columns
    int matrix_c=0; //counts the matrices
    int** matrix1 ;
    int ** matrix2 ;
    int rows1,row2,columns1,columns2; //matrix1 and 2 rows numbers and columns
    int ** temp_matrix;

    do
    {

        fgets(line_buffer,100,file);
        *(temp_matrix+temp_row_c) = split_elements(line_buffer,temp_row_c,temp_column_c);


        temp_row_c++;
        if(is_empty(line_buffer))
        {

            matrix_c++;
            if(matrix_c==1)
            {
                matrix1 = (int**) malloc(sizeof(temp_row_c * sizeof(int*)));

                rows1=temp_row_c;
            }
            else if(matrix_c==2)
            {
                matrix2 = (int**) malloc(sizeof(temp_row_c * sizeof(int*)));
                row2=temp_row_c;
            }
            temp_row_c=0;
            *temp_matrix = NULL;

        }
    }
    while(line_buffer!=EOF||matrix_c<=1);

    fclose(location);



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


int main()
{



    return 0;
}
