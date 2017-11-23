#ifndef READMATRIX_H_
#define TYPE float
#define READMATRIX_H_

TYPE* split_elements(char* buffer,int*cols);

int is_number(char* string);

TYPE ** read_matrix(char*filename,int*cols,int*rows);

#endif //READMATRIX_H_
