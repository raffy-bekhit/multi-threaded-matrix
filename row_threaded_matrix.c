	#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define M 2  //rows1
#define K 2  //row2 col1
#define N 1  //col2

#define TYPE float

typedef struct Parameters  //paramters passed to the function
{


    int rowsA,rowsB,colsA,colsB;

    TYPE ** matrixA ;
    TYPE ** matrixB;
    TYPE ** matrixC ;


} Parameters;


typedef struct Argument  //Argument passed to thread function
{

    Parameters * parameters;
    int row; //thread row

} Argument;


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
void create_Argument ( Argument * a , Parameters*p ,int row)
{

    a->parameters=p;
    a->row=row;
    return;

}





void* calculate_row(Argument* );
void row_threaded_marix_mult(TYPE** ,TYPE** ,TYPE**,int ,int ,int , int ) ;  //prototypes for the used functions.


void row_threaded_marix_mult(TYPE** matrixA,TYPE** matrixB,TYPE **matrixC,int rowsA,int colsA,int rowsB, int colsB)
{




printf("%d\n",matrixA[1][1]);
printf("%d\n",(TYPE*)matrixB);


    if(colsA!=rowsB) //checks matrices multiplication condition

    {
        printf("Matrices aren't of the same lengths"); //error to be displyed
        return ; //return NULL pointer in case of error
    }
    Parameters * p = (Parameters*)malloc(sizeof(Parameters)); //allocates memory for Parameters



    create_Parameters(p,matrixA,matrixB,matrixC,rowsA,colsA,rowsB,colsB); //initializes p with parameters given to function

    Argument a[rowsA] ; //Arguments of thread function





    int i,j; //loop for assigning a thread to each and every element that will be calculated in the new matrix
    int error_flag;
    pthread_t threads_array[rowsA]; //array of threads
    pthread_attr_t attr_array[rowsA]; //array of thread attributes
    int thread_row[rowsA];  //array of number of row of matrix A to be given as args to the thread function




    for(i = 0; i < rowsA; i++)
    {

        create_Argument(&a[i],p,i); //thread_args are the number of row of matrix A



        pthread_attr_init(&attr_array[i]);    //get default attributes
        error_flag = pthread_create(&threads_array[i],&attr_array[i],calculate_row,&a[i]); //create the

        if(error_flag!=0)  //checks if thread is created .. if not returns NULL pointer
        {
            printf("error in thread creation: %d\n",error_flag);
            return ;
        }
    }

    for(i = 0; i < rowsA; i++)
    {
        pthread_join(threads_array[i],NULL);
    }



    free(p);
    return;





}


int main()
{


    int i,j;


TYPE ** matrixA = (TYPE**) malloc(2*sizeof(TYPE*));
TYPE ** matrixB = (TYPE**) malloc(2*sizeof(TYPE*));
TYPE ** matrixC = (TYPE**) malloc(2*sizeof(TYPE*));

for(i=0;i<2;i++)
{
matrixA[i] = (TYPE*) malloc(2*sizeof(TYPE));
matrixB[i] = (TYPE*) malloc(2*sizeof(TYPE));
matrixC[i] = (TYPE*) malloc(2*sizeof(TYPE));
for(j=0;j<2;j++){
    matrixA[i][j]=(i*2)+j;

matrixB[i][j]=(i*2)+j;
}
}

    row_threaded_marix_mult(matrixA,matrixB,matrixC,2,2,2,2);

//Print out the resulting matrix
    for(i = 0; i < 2; i++)
    {
        for(j = 0; j< 2; j++)
        {
            printf("%d ", matrixC[i][j]);
        }
        printf("\n");
    }


    return 0;

}

//function for calculating the value of element.
void* calculate_row(Argument * a)
{

    int i,j; //variables used in loops

    TYPE sum=0; //temporary variable to hold the value of the calculated element

    Parameters * p = a->parameters;

  

  

    for(i=0; i< p->colsB ; i++) //loops the columns of matrixB
    {

        for(j=0; j< p->rowsB; j++) //loops rows of matrixB //loops columns of matrixA for a specific row
        {
          
           sum = sum +(p->matrixA[a->row][j]*p->matrixB[j][i]);
        }
        p->matrixC[a->row][i]=sum;
        sum=0;
    }

    pthread_exit(0);

}


