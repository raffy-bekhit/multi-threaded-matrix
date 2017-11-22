#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int error = 0;

int *** read_file(char* location,int[2] rows , int[2] columns) //function to read matrices from given file //rows
{
	FILE* file =  fopen(location,"r");
	char buffer[100]; //buffer for reading line
	int temp_row_c=0; // counter that counts the rows
	int temp_column_c=0; //cpunts the columns
	int matrix_c=0; //counts the matrices
    int** matrix1 ;
    int ** matrix2 ;
    int rows1,row2,columns1,columns2; //matrix1 and 2 rows numbers and columns
    int ** temp_matrix;

	do{

        fgets(line_buffer,100,file);
       *(temp_matrix+temp_row_c) = split_elements(buffer,temp_row_c,&temp_column_c); //fills a temporary matrix


        row_c++;
        if(isEmpty(buffer))
        {

            matrix_c++;
            if(matrix_c==1)
             {
             matrix1 = (int**) malloc(sizeof(temp_row_c * sizeof(int*))); //when a line is empty the first matrix is filled and allocated
        matrix1 = temp_matrix;
             rows1=temp_row_c;
             }
            else if(matrix_c==2)
            {
            matrix2 = (int**) malloc(sizeof(temp_row_c * sizeof(int*)));
            matrix2 = temp_matrix;
            row2=temp_row_c;

            }
            temp_row_c=0; //row counter resets for next matrix
            *temp_matrix = NULL; //temp_matrix is set to null for new matrix

        }
	}while(line_buffer!=EOF||matrix_c<=1);

	fclose(filename);

    int *** array_of_matrices = malloc(2*sizeof(int**));

    *array_of_matrices = matrix1;
    *(array_of_matrices+1)=matrix2;
    rows[0]=rows1;
    rows[1]=rows2;
    columns[0]=columns1;
    columns[1]=columns2;
    return array_of_matrices;


}

/*int create_matrices() //function that creates matrices from given file
{


}*/

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

//to do: set column numbers 
int * split_elements(char* buffer,int row_c,int * column_num) //returns number of columns or error number // column_num is number of columns already counted from previous turns
{
    char splitters[]={'\t','\n',' '}; //used in strtok_r function
    char * token ;
    char * position = buffer;

    int column_c=0; //number of columns present in this turn
    if(row_c>1) column_c=column_num;

    int * temp_row;



    while( token = strtok_r(position,splitter,&position) )
    {
        if(!isnumber(token))
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

int main()
{

int rows[2],columns[2];

int*** matrices = read_file("/home/raffy/Desktop/matrices",rows,columns);


    return 0;
}
