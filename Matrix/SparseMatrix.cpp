#ifndef _SPAREMATRIX_CPP
#define _SPAREMATRIX_CPP
#include "SparseMatrix.h"
#include <ostream>
using std::ostream;
using std::endl;


template <class T>
SparseMatrix<T>::SparseMatrix(int row, int col, const T& zero) {
    if(row<0 || col<0) {
        throw "Constructor : Invalid size.";
    }
    this->row = row;
    this->col = col;
    this->zeroElement = zero;
}

template <class T>
SparseMatrix<T>::SparseMatrix(int row, int col) {
    if(row<0 || col<0) {
        throw "Constructor : Invalid size.";
    }
    this->row = row;
    this->col = col;
}

template <class T>
T SparseMatrix<T>::get(int row, int col) const {
    checkIndex(row, col);
    unsigned int i = 0;
    for(; i<elements.size(); i++) {
        if(elements.at(i).row == row) {break;}
    } // 找不到的话，下次循环也不会执行，直接返回zeroElement 
    for(;i<elements.size(); i++) {
        if(elements.at(i).col == col 
        && elements.at(i).row == row) {
            return elements.at(i).val; // 找到了
        }
    }
    return zeroElement;
}

template <class T>
void SparseMatrix<T>::set(int row, int col, const T& theElement) {
    checkIndex(row, col);
    unsigned int i = 0;
    if(elements.empty()) {
        elements.insert(elements.begin(), ArrayElement<T>(row, col, theElement));
        return;
    }
    for(; i<elements.size(); i++) {
        if(elements.at(i).row == row) {break;}  // 找到行了
        if(elements.at(i).row > row) { // 找不到的话，下次循环也不会执行，直接插入
            elements.insert(elements.begin()+i, ArrayElement<T>(row, col, theElement));
            return;
        }
    } 
    for(;i<elements.size(); i++) {
        if(elements.at(i).row > row) {break;}      // 过了这一行的区域
        if(elements.at(i).col < col) {continue;}   // 还没到位置
        if(elements.at(i).col == col) {
            elements.at(i) = ArrayElement<T>(row, col, theElement); // 已存在元素，修改
            return;
        }
        break;
    }
    elements.insert(elements.begin()+i, ArrayElement<T>(row, col, theElement));
}

template <class T>
void SparseMatrix<T>::transpose() {
    for(unsigned int i=0; i<elements.size(); i++) {
        ArrayElement<T>& elem = elements.at(i);
        int row = elem.row;
        elem.row = elem.col;
        elem.col = row;
    }
    // 交换row和col的大小
    int rows = this->row;
    this->row = this->col;
    this->col = rows;

    int* rowSize = new int[row]; 
    int* nextIndex = new int[row]; 
    for(int i=0; i<row; i++) {rowSize[i] = 0; nextIndex[i] = 0;}
    for(unsigned int i=0; i<elements.size(); i++) {
        rowSize[elements.at(i).row] ++;
    }
    for(unsigned int i=1; i<elements.size(); i++) {
        nextIndex[i] = nextIndex[i-1] + rowSize[i-1];
    }
    vector<ArrayElement<T> > newElements;
    newElements.resize(elements.size());
    for(unsigned int i=0; i<elements.size(); i++) {
        ArrayElement<T> theElement = elements.at(i);
        newElements.at(nextIndex[theElement.row] ++) = theElement;
    }
    elements = newElements;
}

template <class T>
void SparseMatrix<T>::checkIndex(int row, int col) const {
    if(row>=this->row || row<0 || col>=this->col || col<0) {
        throw "checkIndex : invalid index";
    }
}

template <class T>
void SparseMatrix<T>::output(ostream& out) const {
    out << endl;
    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            out << this->get(i, j) << "\t";
        }
        out << endl;
    }
}

template <class T>
void SparseMatrix<T>::output_struct(ostream& out) const {
    out << endl;
    for(unsigned int i=0; i<elements.size(); i++) {
        out << elements.at(i);
    }
    out << endl;
}


#endif