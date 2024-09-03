#include "Matrix.hpp"

Matrix::Matrix()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            matrix[i][j] = 0;
        }
    }

    matrix[0][0] = 2;
}

Matrix::~Matrix()
{
}

int Matrix::getElement(int i, int j)
{
    return matrix[i][j];
}

void Matrix::moveMatrix(char d)
{
    // For right shift move.
    if (d == 'r') {
 
        // for each row from
        // top to bottom
        for (int i = 0; i < 4; i++) {
            std::vector<int> v, w;
            int j;
 
            // for each element of
            // row from right to left
            for (j = 3; j >= 0; j--) {
                // if not 0
                if (matrix[i][j])
                    v.push_back(matrix[i][j]);
            }
 
            // for each temporary array
            for (j = 0; j < v.size(); j++) {
                // if two element have same
                // value at consecutive position.
                if (j < v.size() - 1 && v[j] == v[j + 1]) {
                    // insert only one element
                    // as sum of two same element.
                    w.push_back(2 * v[j]);
                    j++;
                }
                else
                    w.push_back(v[j]);
            }
 
            // filling the each row element to 0.
            for (j = 0; j < 4; j++)
                matrix[i][j] = 0;
 
            j = 3;
 
            // Copying the temporary
            // array to the current row.
            for (auto it = w.begin();
                it != w.end(); it++)
                matrix[i][j--] = *it;
        }
    }
 
    // for left shift move
    else if (d == 'l') {
 
        // for each row
        for (int i = 0; i < 4; i++) {
            std::vector<int> v, w;
            int j;
 
            // for each element of the
            // row from left to right
            for (j = 0; j < 4; j++) {
                // if not 0
                if (matrix[i][j])
                    v.push_back(matrix[i][j]);
            }
 
            // for each temporary array
            for (j = 0; j < v.size(); j++) {
                // if two element have same
                // value at consecutive position.
                if (j < v.size() - 1 && v[j] == v[j + 1]) {
                    // insert only one element
                    // as sum of two same element.
                    w.push_back(2 * v[j]);
                    j++;
                }
                else
                    w.push_back(v[j]);
            }
 
            // filling the each row element to 0.
            for (j = 0; j < 4; j++)
                matrix[i][j] = 0;
 
            j = 0;
 
            for (auto it = w.begin();
                it != w.end(); it++)
                matrix[i][j++] = *it;
        }
    }
 
    // for down shift move.
    else if (d == 'd') {
        // for each column
        for (int i = 0; i < 4; i++) {
            std::vector<int> v, w;
            int j;
 
            // for each element of
            // column from bottom to top
            for (j = 3; j >= 0; j--) {
                // if not 0
                if (matrix[j][i])
                    v.push_back(matrix[j][i]);
            }
 
            // for each temporary array
            for (j = 0; j < v.size(); j++) {
 
                // if two element have same
                // value at consecutive position.
                if (j < v.size() - 1 && v[j] == v[j + 1]) {
                    // insert only one element
                    // as sum of two same element.
                    w.push_back(2 * v[j]);
                    j++;
                }
                else
                    w.push_back(v[j]);
            }
 
            // filling the each column element to 0.
            for (j = 0; j < 4; j++)
                matrix[j][i] = 0;
 
            j = 3;
 
            // Copying the temporary array
            // to the current column
            for (auto it = w.begin();
                it != w.end(); it++)
                matrix[j--][i] = *it;
        }
    }
 
    // for up shift move
    else if (d == 'u') {
        // for each column
        for (int i = 0; i < 4; i++) {
            std::vector<int> v, w;
            int j;
 
            // for each element of column
            // from top to bottom
            for (j = 0; j < 4; j++) {
                // if not 0
                if (matrix[j][i])
                    v.push_back(matrix[j][i]);
            }
 
            // for each temporary array
            for (j = 0; j < v.size(); j++) {
                // if two element have same
                // value at consecutive position.
                if (j < v.size() - 1 && v[j] == v[j + 1]) {
                    // insert only one element
                    // as sum of two same element.
                    w.push_back(2 * v[j]);
                    j++;
                }
                else
                    w.push_back(v[j]);
            }
 
            // filling the each column element to 0.
            for (j = 0; j < 4; j++)
                matrix[j][i] = 0;
 
            j = 0;
 
            // Copying the temporary array
            // to the current column
            for (auto it = w.begin();
                it != w.end(); it++)
                matrix[j++][i] = *it;
        }
    }
}

bool Matrix::addNumber(){
    std::vector<std::tuple<int, int>> emptyCells;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            if (matrix[i][j] == 0){
                emptyCells.push_back(std::make_tuple(i, j));
            }
        }
    }
    if (emptyCells.size() > 0){
        std::tuple<int, int> chosenCell = emptyCells[rand()%emptyCells.size()];
        matrix[std::get<0>(chosenCell)][std::get<1>(chosenCell)] = rand()%10<8 ? 2 : 4;
        return true;
    }
    return false;
}
