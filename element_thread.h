#ifndef ELEMENT_THREAD_H_
#define TYPE float

#define ELEMENT_THREAD_H_
typedef struct Parameters;
struct element;
void *calculate_element(void *element); //prototypes for the used functions.
pthread_t create_thread_per_element(struct element *el);
void print_resulting_matrix(TYPE ** matrixC,int rowsC,int colsC);
void calculate_matrix_by_element(TYPE ** matrixA, TYPE** matrixB, TYPE **matrixC,int rowsA,int colsA,int rowsB, int colsB );
void calculate_matrix_without_thread(TYPE ** matrixA, TYPE** matrixB,TYPE** matrixC,int rowsA,int colsA, int colsB);
#endif