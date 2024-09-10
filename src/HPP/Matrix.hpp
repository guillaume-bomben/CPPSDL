#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <map>

class Matrix
{
private:
    //int matrix[4][4];
public:
    int matrix[4][4];
    Matrix();
    ~Matrix();
    int getElement(int i, int j);
    void moveMatrix(char d);
    bool addNumber();
    int getScore();
    
};

#endif